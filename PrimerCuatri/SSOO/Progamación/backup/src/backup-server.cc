/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * 
 * @subject: SSOO
 * 
 * @file backup-server.cc
 * @author Ezequiel Hernández Poleo (alu0101735399@ull.edu.es)
 * @date 2025-12-02
 * @brief 
 */
// modificacion: si backup-server recibe la señal SIGUSR2, cancelara la copia que se este llevando a cabo en ese momento.

#include "../includes/functions.h"

struct ServerOptions {
  enum class CompressionType {
    NONE,
    GZIP,
    BZIP2,
    XZ
  };
  CompressionType compression = CompressionType::NONE;
  std::string backup_dir;
  bool show_help = false;
  bool has_compression_type = false;
};

enum class ParseArgsErrors {
  unknown_option,
  multiple_compression_options,
  too_many_arguments,
};

enum class CopyFileCompressedError {
  command_access_denied, // Exit code 126
  command_execution_failed, // Other non-zero
  command_not_found, // Exit code 127
  output_access_denied, // Exit code 128
  process_creation_failed,
  pipe_creation_failed,
  unknown_error
};

std::atomic<bool> quit_requested{false};

std::expected<void, std::system_error> create_fifo(const std::string& fifo_path) {
  int fd = mkfifo(fifo_path.c_str(), 0666);
  if(fd == -1) {
    if(errno == EEXIST) {
      if(unlink(fifo_path.c_str()) == -1) {
        int error = errno;
        return std::unexpected(std::system_error(error, std::system_category(), "[ERROR]: Error al desvincular la FIFO que ya estaba creada"));
      }
      fd = mkfifo(get_fifo_path().c_str(), 0666);
    } else {
      int error = errno;
      return std::unexpected(std::system_error(error, std::system_category(), "[ERROR]: Error al crear la FIFO"));
    }
  }
  return {};
}

std::expected<void, std::system_error> write_pid_file(const std::string& pid_file_path) {
  int fd = open(pid_file_path.c_str(), O_WRONLY | O_CREAT | O_TRUNC, 0664);
  if(fd == -1) {
    int error = errno;
    return std::unexpected(std::system_error(error, std::system_category(), "[ERROR]: Error al abrir el archivo del PID"));
  }
  std::string pid = std::to_string(getpid()) + '\n';
  ssize_t bytes_written = write(fd, pid.data(), pid.size());
  if(bytes_written == -1) {
    int error = errno;
    close(fd);
    return std::unexpected(std::system_error(error, std::system_category(), "[ERROR]: Error al escribir el PID"));
  }
  close(fd);
  return {};
}

void termination_handler(int signum) {
  const char msg[] = "backup-server: Señal de terminación recibida, cerrando...\n";
  write(STDERR_FILENO, msg, sizeof(msg) - 1); 
  quit_requested = true;
}

std::expected<void, std::system_error> setup_signal_handler() {
  // 1. Manejo Síncrono (SIGUSR1): Bloquearla para usar sigwaitinfo
  sigset_t signal_set;
  struct sigaction sa;
  if(sigemptyset(&signal_set) == -1) {
    int error = errno;
    return std::unexpected(std::system_error(error, std::system_category(), "[ERROR]: Error al vaciar el SignalSet"));
  }
  if(sigaddset(&signal_set, SIGUSR1) == -1) {
    int error = errno;
    return std::unexpected(std::system_error(error, std::system_category(), "[ERROR]: Error al añadir al SignalSet SIGUSR1"));
  }
  if(sigprocmask(SIG_BLOCK, &signal_set, NULL) == -1) {
    int error = errno;
    return std::unexpected(std::system_error(error, std::system_category(), "[ERROR]: Error al bloquear el SignalSet"));
  }
  // 2. Manejo Asíncrono (SIGTERM, INT, etc.): Instalar manejador
  sa.sa_handler = termination_handler;
  if (sigemptyset(&sa.sa_mask) == -1) { // No bloqueamos ninguna señal extra en el manejador 
    int error = errno;
    return std::unexpected(std::system_error(error, std::system_category(), "[ERROR]: Error en sigemptyset para sa_mask"));
  }
  sa.sa_flags = 0;
  if(sigaction(SIGTERM, &sa, NULL) ||
     sigaction(SIGHUP, &sa, NULL) ||
     sigaction(SIGQUIT, &sa, NULL) ||
     sigaction(SIGINT, &sa, NULL)) {
    int error = errno;
    return std::unexpected(std::system_error(error, std::system_category(), "[ERROR]: Error en al asignacion de comportamiento (sigaction()) de las señales"));
  }
  return {};
}

std::expected<std::string, std::system_error> read_path_from_fifo(int fifo_fd) {
  std::string path_buffer;
  char c;
  ssize_t bytes_read;
  while(path_buffer.size() < PATH_MAX) {
    bytes_read = read(fifo_fd, &c, 1);
    if(bytes_read == 1) {
      if(c == '\n') {
        break; // FIN del mensaje
      }
      path_buffer += c;
    } else if(bytes_read == 0) {
      break; // EOF
    } else {
      if (errno == EINTR) {
        continue; // Reintentar si fue interrumpido por señal
      }
      return std::unexpected(std::system_error(errno, std::system_category(), "[ERROR]: Error de lectura en read_path_from_fifo"));
    }
  }
  return path_buffer;
}

std::expected<void, std::system_error> cleanup_resources(const std::string& work_dir) {  
  std::string fifo_path = get_fifo_path();
  std::string pid_path = get_pid_file_path();
  // Eliminar archivo FIFO
  if (unlink(fifo_path.c_str()) == -1 && errno != ENOENT) {
    return std::unexpected(std::system_error(errno, std::system_category(), "cleanup: error al eliminar FIFO"));
  }
  // Eliminar archivo PID
  if (unlink(pid_path.c_str()) == -1 && errno != ENOENT) {
    return std::unexpected(std::system_error(errno, std::system_category(), "cleanup: error al eliminar archivo PID"));
  }
  return {};
}

std::expected<ServerOptions, ParseArgsErrors> parse_arguments(int argc, char* argv[]) {
  ServerOptions options;
  // La cadena de opciones "zjx" indica que -z, -j, y -x son opciones sin argumento.
  // opterr = 0 desactiva los mensajes de error automáticos de getopt()[cite: 625, 668].
  opterr = 0; 
  // Reiniciar optind (necesario si getopt() se ha llamado antes)
  optind = 1; 
  for(int opt; (opt = getopt(argc, argv, "zjx")) != -1;) {
    switch (opt) {
      case 'z':
        // Verificar exclusión mutua
        if (options.compression != ServerOptions::CompressionType::NONE) {
          return std::unexpected(ParseArgsErrors::multiple_compression_options);
        }
        options.compression = ServerOptions::CompressionType::GZIP;
        break;
      case 'j':
        // Verificar exclusión mutua
        if (options.compression != ServerOptions::CompressionType::NONE) {
          return std::unexpected(ParseArgsErrors::multiple_compression_options);
        }
        options.compression = ServerOptions::CompressionType::BZIP2;
        break;
      case 'x':
        // Verificar exclusión mutua
        if (options.compression != ServerOptions::CompressionType::NONE) {
          return std::unexpected(ParseArgsErrors::multiple_compression_options);
        }
        options.compression = ServerOptions::CompressionType::XZ;
        break;
      case '?':
        // Se retorna '?' si la opción es desconocida
        return std::unexpected(ParseArgsErrors::unknown_option);
      default:
        // Manejar cualquier otro caso inesperado
          return std::unexpected(ParseArgsErrors::unknown_option);
    }
  }
  // Procesamiento de argumentos adicionales (DIRECTORIO_DESTINO)
  // optind apunta al primer argumento que no es una opción
  if(optind < argc) {
    // Se encontró al menos un argumento posicional
    options.backup_dir = argv[optind];
    optind++; // Avanzar para verificar si hay más argumentos
    // Comprobar si hay más argumentos no-opción (Error: demasiados argumentos)
    if (optind < argc) {
      return std::unexpected(ParseArgsErrors::too_many_arguments);
    }
  } 
    // Si optind == argc, no se proporcionó DIRECTORIO_DESTINO, por lo que se usará el directorio actual[cite: 38]. 
    
    // Si la compresión está activada, es útil mostrar el tipo de compresión[cite: 73, 78].
    // Esta parte puede ir en main, pero la muestro aquí por completitud lógica.
    /*
    if (options.compression != CompressionType::NONE) {
        // ... (Mostrar mensaje de compresión activa)
    }
    */

    return options; // Retorna la estructura ServerOptions
}

std::string get_compression_command(ServerOptions::CompressionType compression) {
  std::string command = "";
  switch(compression) {
    case ServerOptions::CompressionType::GZIP:
      command = "gzip";
      break;
    case ServerOptions::CompressionType::BZIP2:
      command = "bzip2";
      break;
    case ServerOptions::CompressionType::XZ:
      command = "xy";
      break;
    default:
      break;
  }
  return command;
}

std::string get_compression_extension(ServerOptions::CompressionType compression) {
  std::string extension = "";
  switch(compression) {
    case ServerOptions::CompressionType::GZIP:
      extension = ".gz";
      break;
    case ServerOptions::CompressionType::BZIP2:
      extension = ".bz2";
      break;
    case ServerOptions::CompressionType::XZ:
      extension = ".xy";
      break;
    default:
      break;
  }
  return extension;
}

bool is_command_available(const std::string& command) {
  std::string list_of_path = get_environment_variable("PATH");
  size_t start = 0;
  size_t end = list_of_path.find(':');
  while(true) {
    std::string current_dir;
    if(end == std::string::npos) {
      current_dir = list_of_path.substr(start);
    } else {
      current_dir = list_of_path.substr(start, end - start);
    }
    current_dir += "/" + command;
    if(access(current_dir.c_str(), X_OK) == 0) {
      return true;
    }
    if(end == std::string::npos) {
      break;
    }
    start = end + 1;
    end = list_of_path.find(':', start);
  }
  return false;
}

std::expected<void, CopyFileCompressedError> copy_file_compressed(const std::string& src_path, const std::string& dest_path, const std::string& compression_command) {
  int pipefd[2];
  if(pipe(pipefd) == -1) {
    return std::unexpected(CopyFileCompressedError::pipe_creation_failed);
  }
  pid_t pid = fork();
  if(pid == -1) {
    return std::unexpected(CopyFileCompressedError::process_creation_failed);
  } else if(pid == 0) {
    // HIJO
    dup2(pipefd[0], STDIN_FILENO);
    close(pipefd[0]);
    int fd = open(dest_path.c_str(), O_WRONLY | O_CREAT | O_TRUNC, 0644);
    dup2(fd, STDOUT_FILENO);
    close(pipefd[1]);
    char* args[] = {const_cast<char*>(compression_command.c_str()), nullptr};
    execvp(compression_command.c_str(), args);
    std::exit(127);
  } else {
    // PADRE
    sigset_t sigset;
    sigemptyset(&sigset);
    sigaddset(&sigset, SIGPIPE);
    if(sigprocmask(SIG_BLOCK, &sigset, NULL) == -1) {
      // RELLENAR CON ERROR
    }
    close(pipefd[0]);
    int src_fd = open(src_path.c_str(), O_RDONLY);
    if(src_fd == -1) {
      // Error abrir src
    }
    const size_t BUFFER_SIZE = 65536;
    char buffer[BUFFER_SIZE];
    while(true) {
      ssize_t bytes_read = read(src_fd, buffer, BUFFER_SIZE);
      if(bytes_read == -1) {
        close(src_fd);
        close(pipefd[1]);
        // RELLENAR CON ERROR
        return std::unexpected(CopyFileCompressedError::unknown_error);
      } else if(bytes_read == 0) {
        break;
      }
      ssize_t bytes_written = write(pipefd[1], buffer, bytes_read);
      if(bytes_written == -1) {
        close(src_fd);
        close(pipefd[1]);
        // RELLENAR CON ERROR
      }
    }
    close(src_fd);
    close(pipefd[1]);
    int status;
      if(waitpid(pid, &status, 0) == -1) {
        return std::unexpected(CopyFileCompressedError::unknown_error);
      }
      if(WIFEXITED(status)) {
        int exit_code = WEXITSTATUS(status);
        if(exit_code == 127) return std::unexpected(CopyFileCompressedError::command_not_found);
        if(exit_code == 126) return std::unexpected(CopyFileCompressedError::command_access_denied);
        if(exit_code != 0) return std::unexpected(CopyFileCompressedError::command_execution_failed);
      } else {
        return std::unexpected(CopyFileCompressedError::command_execution_failed);
      }
  }
  return {};
}

std::expected<void, std::system_error> run_server(int fifo_fd, const std::string& backup_dir, const ServerOptions& config) {
  sigset_t sigset;
  siginfo_t siginfo;
  if((sigemptyset(&sigset) || sigaddset(&sigset, SIGUSR1)) == -1) {
    int error = errno;
    return std::unexpected(std::system_error(error, std::system_category(), "[ERROR]: Error en la configuración del sigset de SIGUSR1"));
  }
  while(!quit_requested) {
    int sign = sigwaitinfo(&sigset, &siginfo);
    if(sign == -1) {
      int error = errno;
      if(error == EINTR) {
        continue; // Interrumpido por señal asíncrona, hacemos continue para revisar quit_requested
      }
      return std::unexpected(std::system_error(error, std::system_category(), "[ERROR]: Error en la espera de SIGUSR1"));
    }
    if(sign == SIGUSR1) {
      auto path_result = read_path_from_fifo(fifo_fd);
      if (!path_result.has_value()) {
        std::cerr << "[WARNING]: Fallo al leer la ruta desde la FIFO." << std::endl;
        continue;
      }
      std::string src_path = path_result.value();
      if (src_path.empty()) {
        std::cerr << "[WARNING]: La ruta leída está vacía." << std::endl;
        continue;
      }
      std::string final_path = backup_dir + '/' + get_filename(src_path);
      if(config.compression == ServerOptions::CompressionType::NONE) {  
        auto copy_result = copy_file(src_path, final_path, 0644);
        if(!copy_result.has_value()) {
          const std::system_error& error = copy_result.error();
          std::cerr << "[WARNING]: Error al hacer backup de " << src_path << ": " << error.what() << std::endl;
        } else {
          std::cout << "[DONE] Backup completado: " << src_path << " -> " << final_path << std::endl;
        }
      } else {
        std::string extension = get_compression_extension(config.compression);
        final_path += extension;
        std::string command = get_compression_command(config.compression);
        auto copy_file = copy_file_compressed(src_path, final_path, command);
        if(!copy_file.has_value()) {
          // SWITCH PARA ERRORES AQUI
        } else {
          std::cout << "[DONE] Backup completado (compressed): " << src_path << " -> " << final_path << std::endl;
        }
      }
    }
  }
  return {};
}

int main(int argc, char* argv[]) {
  auto args = parse_arguments(argc, argv);
  if(!args.has_value()) {
    ParseArgsErrors err = args.error();
    switch(err) {
      case ParseArgsErrors::unknown_option:
        std::cerr << "[ERROR]: Los argumentos pasados no se reconocen" << std::endl;
        break;
      case ParseArgsErrors::multiple_compression_options:
        std::cerr << "[ERROR]: Se ha pasado más de un método de compresión como argumento" << std::endl;
        break;
      case ParseArgsErrors::too_many_arguments:
        std::cerr << "[ERROR]: Se han pasado demasiados argumentos" << std::endl;
        break;
      default:
        break;
    }
  }
  ServerOptions config = args.value();
  if (config.compression != ServerOptions::CompressionType::NONE) {
      std::string cmd = get_compression_command(config.compression);
      std::cout << "[INFO]: Compresión -> " << cmd << std::endl;
      if (!is_command_available(cmd)) {
          std::cerr << "[ERROR]: " << cmd << " no está instalado" << std::endl;
          return EXIT_FAILURE;
      }
  }
  // 1. Valida que la variable BACKUP_WORK_DIR esté definida.
  if(get_work_dir_path().empty()) {
    std::cerr << "[ERROR]: La variable BACKUP_WORK_DIR está vacía" << std::endl;
    return EXIT_FAILURE;
  }

  // 2. Verifica que el directorio de destino existe y es accesible.
  std::string destino;
  if (!config.backup_dir.empty()) {
    destino = config.backup_dir;
  } else {
    destino = get_current_dir();
  }
  if(!is_directory(destino)) {
    std::cerr << "[ERROR]: La ruta pasada no corresponde con un directorio" << std::endl;
    return EXIT_FAILURE;
  }

  // 3. Comprueba que no haya otro servidor ejecutándose.
  auto pid_server = read_server_pid(get_pid_file_path());
  if(!pid_server.has_value()) {
    const std::system_error& error = pid_server.error();
  } else {
    pid_t pid_real = pid_server.value();
    if(is_server_running(pid_real)) {
      std::cerr << "[ERROR]: El servidor ya se está ejecutando con PID: " << pid_real << std::endl;
      return EXIT_FAILURE;
    } else {
      std::cerr << "[WARNING]: Se encontró un archivo PID huérfano, continuando..." << std::endl;
    }
  }

  // 4. Crea la tubería con nombre (FIFO).
  
  if (!create_fifo(get_fifo_path()).has_value()) {
    std::cerr << "[ERROR]: Fallo al crear la fifo" << std::endl;
    return EXIT_FAILURE;
  }
  
  // 5. Escribe su PID en el archivo backup-server.pid.
  if (!write_pid_file(get_pid_file_path()).has_value()) {
    std::cerr << "[ERROR]: Error al escribir el archivo PID" << std::endl;
    cleanup_resources(get_work_dir_path());
    return EXIT_FAILURE;
  }

  // 6. Configura el manejo de señales para bloquear SIGUSR1.
  if (!setup_signal_handler().has_value()) {
    std::cerr << "[ERROR]: Fallo al configurar manejador de señales." << std::endl;
    return EXIT_FAILURE;
  }

  // 7. Abre la FIFO para lectura.
  int fifo_fd = open(get_fifo_path().c_str(), O_RDONLY);
  if(fifo_fd == -1) {
    std::cerr << "[ERROR]: Error al abrir la fifo para lectura" << std::endl;
    cleanup_resources(get_work_dir_path());
    return EXIT_FAILURE;
  }

  // 8. Muestra un mensaje indicando que está listo.
  std::cout << "[BACKUP-SERVER]: Esperando solicitudes de backup en " << destino << std::endl;

  // 9. Entra en un bucle infinito esperando señales.
  run_server(fifo_fd, config.backup_dir, config);
  close(fifo_fd);
  if(!cleanup_resources(get_work_dir_path()).has_value()) {
    std::cerr << "[ERROR]: Error al limpiar recursos" << std::endl;
  }
  return EXIT_SUCCESS;
}
