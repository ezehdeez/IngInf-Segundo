/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * 
 * @subject: SSOO
 * 
 * @file backup.cc
 * @author Ezequiel Hernández Poleo (alu0101735399@ull.edu.es)
 * @date 2025-12-02
 * @brief 
 */

#include "../includes/functions.h"

bool check_args(int argc, char* argv[]) {
  if (argc != 2) {
    std::cerr << "[ERROR]: La forma de uso es ./backup Archivo_a_copiar" << std::endl;
    return false;
  }
  return true;
}

std::expected<void, std::system_error> check_work_dir_exists(const std::string& work_dir) {
  struct stat st;
  if(stat(work_dir.c_str(), &st) == -1) {
    int error = errno;
    return std::unexpected(std::system_error(error, std::system_category(), "[ERROR]: El directorio no existe o no es accesible (stat())"));
  }
  if(S_ISDIR(st.st_mode)) {
    int error = errno;
    return std::unexpected(std::system_error(error, std::system_category(), "[ERROR]: La ruta existe pero no es un directorio"));
  }
  return {};
}

std::expected<int, std::system_error> open_fifo_write(const std::string& fifo_path) {
  int fifo_fd = open(fifo_path.c_str(), O_WRONLY);
  if(fifo_fd == -1) {
    int error = errno;
    return std::unexpected(std::system_error(error, std::system_category(), "[ERROR]: Error al abrir la fifo para escritura"));
  }
  return fifo_fd;
}

std::expected<void, std::system_error> write_path_to_fifo(int fifo_fd, const std::string& file_path) {
  std::string message = file_path + '\n';
  ssize_t bytes_written = write(fifo_fd, message.c_str(), message.size());
  if(bytes_written == -1 || bytes_written != message.size()) {
    int error = (bytes_written == -1) ? errno : EIO;
    return std::unexpected(std::system_error(error, std::system_category(), "[ERROR]: Error al escribir la ruta en la fifo"));
  }
  return {};
}

int main(int argc, char* argv[]) {
  // 1. Valida que la variable BACKUP_WORK_DIR esté definida.
  if(get_work_dir_path().empty()) {
    std::cerr << "[ERROR]: La variable BACKUP_WORK_DIR está vacía" << std::endl;
    return EXIT_FAILURE;
  }

  // 2. Verifica que el archivo existe y es un archivo regular.
  std::string destino = argv[1];
  if(!file_exists(destino)) {
    std::cerr << "[ERROR]: El archivo no existe" << std::endl;
    return EXIT_FAILURE;
  }
  if(!is_regular_file(destino)) {
    std::cerr << "[ERROR]: El archivo no es regular" << std::endl;
    return EXIT_FAILURE;
  }

  // 3. Lee el PID del servidor desde el archivo backup-server.pid y 4. Verifica que el servidor está ejecutándose.
  pid_t pid_server;
  auto read_pid = read_server_pid(get_pid_file_path());
  if(!read_pid.has_value()) {
    std::cerr << "[ERROR]: Error al leer el PID del archivo" << std::endl;
    return EXIT_FAILURE;
  } else {
    pid_server = read_pid.value();
    if(!is_server_running(pid_server)) {
      std::cerr << "[ERROR]: Ya hay un servidor ejecutándose con PID " << pid_server << std::endl;
      return EXIT_FAILURE;
    } else {
      std::cerr << "[WARNING]: Se encontró un archivo PID huérfano, continuando..." << std::endl;
    }
  }

  // 5. Bloquea la señal SIGPIPE.
  sigset_t sigset;
  sigemptyset(&sigset);
  sigaddset(&sigset, SIGPIPE);
  if(sigprocmask(SIG_BLOCK, &sigset, NULL) == -1) {
    std::cerr << "[ERROR]: Error al bloquear la señal SIGPIPE" << std::endl;
    return EXIT_FAILURE;
  }

  // 6. Abre la FIFO para escritura.
  int fifo_fd;
  auto fifo_open = open_fifo_write(get_fifo_path());
  if(!fifo_open.has_value()) {
    std::cerr << "[ERROR]: No se ha podido abrir la fifo para escritura" << std::endl;
    return EXIT_FAILURE;  
  } else {
    fifo_fd = fifo_open.value();
  }

  // 7. Convierte la ruta del archivo a ruta absoluta.
  auto path_result = get_absolute_path(destino);
  if (!path_result.has_value()) {
    std::cerr << "backup: error: fallo al convertir la ruta a absoluta" << std::endl;
    return EXIT_FAILURE;
  }
  std::string ruta_absoluta = path_result.value();

  // 8. Escribe la ruta en la FIFO.
  auto fifo_write = write_path_to_fifo(fifo_fd, ruta_absoluta);
  if(!fifo_write.has_value()) {
    std::cerr << "[ERROR]: Error al escribir la ruta en la fifo" << std::endl;
    return EXIT_FAILURE;
  }

  // 9. Envía la señal SIGUSR1 al servidor.
  if(kill(pid_server, SIGUSR1) == -1) {
    std::cerr << "[ERROR]: Error al mandar la señal SIGUSR1" << std::endl;
    close(fifo_fd);
    return EXIT_FAILURE;
  }

  // 10. Cierra la FIFO.
  close(fifo_fd);

  // 11. Muestra un mensaje de confirmación.
  std::cout << "[DONE]: Solicitud enviada" << std::endl;
  return EXIT_SUCCESS;
}