/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * 
 * @subject: SSOO
 * 
 * @file backup-server.cc
 * @author Ezequiel Hernández Poleo (alu0101735399@ull.edu.es)
 * @date 2025-11-26
 * @brief 
 */

#include <string>
#include <iostream>
#include <expected>
#include <atomic>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <limits.h>
#include <sys/stat.h>
#include <sys/types.h>

#include "../includes/functions.h"
#include "../includes/copy.h"

const std::string BACKUP_WORK_DIR = GetEnviromentalVariable("BACKUP_WORK_DIR");

std::expected<pid_t, std::system_error> read_server_pid(const std::string& pid_file_path) {
  int server = open(pid_file_path.c_str(), O_RDONLY);
  if(server == -1) {
    return std::unexpected(std::system_error(errno, std::system_category(), "[ERROR] backup-server: Error al abrir el archivo backup-server.pid"));
  }
  char buffer[256];
  ssize_t bytes_read = read(server, buffer, sizeof(buffer) - 1);
  if(bytes_read == -1) {
    int error = errno;
    close(server);
    return std::unexpected(std::system_error(error, std::system_category(), "[ERROR] backup-server: Error al leer del archivo PID."));
  }
  buffer[bytes_read] = '\0';
  pid_t pid = std::atoi(buffer);
  close(server);
  if(pid <= 0) {
    int error = errno;
    return std::unexpected(std::system_error(error, std::system_category(), "[ERROR] backup-server: PID leído no es válido o es 0"));
  }
  return pid;
}

std::expected<void, std::system_error> create_fifo(const std::string& fifo_path) {
  int result = mkfifo(fifo_path.c_str(), 0666);
  if(result == -1) {
    if(errno == EEXIST) {
      if(unlink(fifo_path.c_str()) == -1) {
        return std::unexpected(std::system_error(errno, std::system_category(), "[ERROR] backup-server: Fallo al eliminar la FIFO"));
      }
      result = mkfifo(fifo_path.c_str(), 0666);
    } else if(errno == EACCES) {
      return std::unexpected(std::system_error(errno, std::system_category(), "[ERROR] backup-server: No hay permisos para crear archivos en el directorio indicado"));
    } else {
      return std::unexpected(std::system_error(errno, std::system_category(), "[ERROR] backup-server: Algún componente de la ruta no existe"));
    }
  }
}

std::expected<void, std::system_error> write_pid_file(const std::string& pid_file_path) {
  std::string pid_string = std::to_string(getpid()) + '\n';
  int server = open(pid_file_path.c_str(), O_WRONLY | O_CREAT | O_TRUNC, 0644);
  if(server == -1) {
    return std::unexpected(std::system_error(errno, std::system_category(), "[ERROR] backup-server: Error al abrir el archivo del pid"));
  }
  ssize_t bytes_written = write(server, pid_string.c_str(), pid_string.size() - 1);
  if (bytes_written == -1) {
    int error = errno;
    close(server);
    return std::unexpected(std::system_error(error, std::system_category(), "[ERROR] backup-server: Error al escribir el archivo de PID"));
  }
  close(server);
}

std::expected<void, std::system_error> setup_signal_handler() {
  sigset_t signal_set;
  struct sigaction sa;
  if (sigemptyset(&signal_set) == -1) {
    return std::unexpected(std::system_error(errno, std::system_category(), "setup: error al inicializar conjunto de señales"));
  }
  if (sigaddset(&signal_set, SIGUSR1) == -1) {
    return std::unexpected(std::system_error(errno, std::system_category(), "setup: error al añadir SIGUSR1"));
  }
  if (sigprocmask(SIG_BLOCK, &signal_set, NULL) == -1) {
    return std::unexpected(std::system_error(errno, std::system_category(), "setup: error al bloquear SIGUSR1"));
  }
  sa.sa_handler = termination_handler;
  if (sigemptyset(&sa.sa_mask) == -1) { // No bloqueamos ninguna señal extra en el manejador 
    return std::unexpected(std::system_error(errno, std::system_category(), "setup: error en sigemptyset para sa_mask"));
  }
  sa.sa_flags = 0; // Sin flags especiales
  if (sigaction(SIGTERM, &sa, NULL) == -1 ||
    sigaction(SIGINT, &sa, NULL) == -1 || // Ctrl+C 
    sigaction(SIGHUP, &sa, NULL) == -1 || // Cierre de terminal
    sigaction(SIGQUIT, &sa, NULL) == -1)  // Ctrl+'\'
  {
    return std::unexpected(std::system_error(errno, std::system_category(), "setup: error al instalar manejadores de terminación"));
  }
  return {};
}

std::atomic<bool> quit_requested{false};

std::expected<int, std::system_error> open_fifo_read(const std::string& fifo_path) {
  int fd = open(fifo_path.c_str(), O_RDONLY);
  if (fd == -1) {
    return std::unexpected(std::system_error(errno, std::system_category(), "error: al abrir FIFO para lectura"));
  }
  return fd;
}

std::expected<std::string, std::system_error> read_path_from_fifo(int fifo_fd) {
  std::string path_buffer;
  char c;
  ssize_t bytes_read;  
  while (path_buffer.length() < PATH_MAX) {
    bytes_read = read(fifo_fd, &c, 1);
    if (bytes_read == 1) {
      if (c == '\n') {
        break; // FIN del mensaje
      }
      path_buffer += c;  
    } else if (bytes_read == 0) {
      // EOF (Escritor cerró antes de enviar \n)
      break; 
    } else { // bytes_read == -1 (Error)
      if (errno == EINTR) {
        continue; // Reintentar si fue interrumpido por señal
      }
      return std::unexpected(std::system_error(errno, std::system_category(), "read_path_from_fifo: error de lectura"));
    }
  }  
  return path_buffer;
}

std::expected<void, std::system_error> run_server(int fifo_fd, const std::string& backup_dir) {
  sigset_t signal_set;
  siginfo_t sig_info;
  // conjunto de señales para sigwaitinfo (solo SIGUSR1).
  if (sigemptyset(&signal_set) == -1 || sigaddset(&signal_set, SIGUSR1) == -1) {
    return std::unexpected(std::system_error(errno, std::system_category(), "run_server: error al configurar conjunto SIGUSR1"));
  }
  // Bucle principal
  while (!quit_requested) {
    // Esperar la señal SIGUSR1 (se queda bloqueado aquí)
    int signo = sigwaitinfo(&signal_set, &sig_info);
    if (signo == -1) {
      if (errno == EINTR) {
        // Interrumpido por una señal de terminación asíncrona (SIGTERM/SIGINT).
        // El bucle verificará 'quit_requested' y saldrá.
        continue; 
      }
      // Error fatal de sigwaitinfo.
      return std::unexpected(std::system_error(errno, std::system_category(), "run_server: error en sigwaitinfo"));
    }
    // El servidor recibió SIGUSR1 
    if (signo == SIGUSR1) {
      auto path_result = read_path_from_fifo(fifo_fd);
      if (!path_result.has_value()) {
        std::cerr << "backup-server: error: Fallo al leer la ruta desde la FIFO." << std::endl;
        continue;
      }
      std::string ruta_origen = path_result.value();
      if (ruta_origen.empty()) {
        std::cerr << "backup-server: error: La ruta leída está vacía." << std::endl;
        continue;
      }
      std::string nombre_archivo = get_filename(ruta_origen);
      std::string ruta_destino = backup_dir + "/" + nombre_archivo;
      auto copy_result = copy_file(ruta_origen, ruta_destino, 0644);
      if (!copy_result.has_value()) {
        const std::system_error& error = copy_result.error();
        std::cerr << "backup-server: error al hacer backup de " << ruta_origen << ": " << error.what() << std::endl;
      } else {
        std::cout << "backup-server: backup completado: " << ruta_origen << " -> " << ruta_destino << std::endl;
      }
    }
  }
  return {};
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

int main(int argc, char* argv[]) {
  if (get_work_dir_path() == "") {
    std::cerr << "backup-server: error: la variable global WORK_BACKUP_DIR no esta definida" << std::endl;
    return EXIT_FAILURE;
  }
  std::string Destino;
  if (argc > 1) {
    Destino = argv[1]; 
  } else {
    Destino = get_current_dir();
  }
  if (!is_directory(Destino)) {
    std::cerr << "backup-server: error: el directorio de destino no es un destino valido" << std::endl;
    return EXIT_FAILURE;
  }
  auto pid_server = read_server_pid(get_pid_file_path());
  if(!pid_server.has_value()) {
    const std::system_error& error = pid_server.error();
  } else {
    pid_t pid_real = pid_server.value();
    if(is_server_running(pid_real)) {
      std::cerr << "backup-server: error: ya hay un servidor ejecutándose (PID " << pid_real << ")" << std::endl;
      return EXIT_FAILURE;
    } else {
      std::cerr << "backup-server: aviso: se encontró un archivo PID huérfano, continuando..." << std::endl;
    }
  }
  int fifo_fd = -1;
  if (!setup_signal_handler().has_value()) {
    std::cerr << "backup-server: error: fallo al configurar manejador de señales." << std::endl;
    return EXIT_FAILURE;
  }
  if (!create_fifo(get_fifo_path()).has_value()) {
    std::cerr << "backup-server: error: fallo al crear la FIFO." << std::endl;
    return EXIT_FAILURE;
  }
  if (!write_pid_file(get_pid_file_path()).has_value()) {
    std::cerr << "backup-server: error: fallo al escribir el archivo PID." << std::endl;
    cleanup_resources(get_work_dir_path());
    return EXIT_FAILURE;
  }
  auto fd_result = open_fifo_read(get_fifo_path());
  if (!fd_result.has_value()) {
    std::cerr << "backup-server: error: fallo al abrir la FIFO para lectura." << std::endl;
    cleanup_resources(get_work_dir_path());
    return EXIT_FAILURE;
  }
  fifo_fd = fd_result.value();
  std::cout << "backup-server: esperando solicitudes de backup en " << Destino << std::endl;
  run_server(fifo_fd, Destino);
  close(fifo_fd);
  if (!cleanup_resources(get_work_dir_path()).has_value()) {
    std::cerr << "backup-server: aviso: fallo al limpiar recursos." << std::endl;
  }
  return EXIT_SUCCESS;
}