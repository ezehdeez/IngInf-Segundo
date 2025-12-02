/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * 
 * @subject: SSOO
 * 
 * @file backup.cc
 * @author Ezequiel Hernández Poleo (alu0101735399@ull.edu.es)
 * @date 2025-11-26
 * @brief 
 */

#include <string>
#include <iostream>
#include <expected>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/stat.h>
#include <sys/types.h>

#include "../includes/functions.h"

bool check_args(int argc, char* argv[]) {
  if (argc != 2) {
    std::cerr << "backup: error: la forma de uso es ./backup Archivo_a_copiar" << std::endl;
    return false;
  }
  return true;
}

std::expected<void, std::system_error> check_work_dir_exists(const std::string& work_dir) {
  struct stat stats;
  if (stat(work_dir.c_str(), &stats) == -1) {
    return std::unexpected(std::system_error(errno, std::system_category(), "check_work_dir_exists: El directorio no existe o no es accesible"));
  }
  if (!S_ISDIR(stats.st_mode)) {
    return std::unexpected(std::system_error(ENOTDIR, std::system_category(), "check_work_dir_exists: La ruta existe pero no es un directorio"));
  }
  return {};
}

std::expected<int, std::system_error> open_fifo_write(const std::string& fifo_path) {
  int fd = open(fifo_path.c_str(), O_WRONLY); 
  if (fd == -1) {
    return std::unexpected(std::system_error(errno, std::system_category(), "error al abrir la FIFO para escritura"));
  }
  return fd;
}

std::expected<void, std::system_error> write_path_to_fifo(int fifo_fd, const std::string& file_path) {
  std::string message = file_path + "\n";
  size_t bytes_to_write = message.size();
  ssize_t bytes_written = write(fifo_fd, message.c_str(), bytes_to_write);
  if (bytes_written == -1 || (size_t)bytes_written != bytes_to_write) {
    int error = (bytes_written == -1) ? errno : EIO;
    return std::unexpected(std::system_error(error, std::system_category(), "error al escribir la ruta en la FIFO"));
  }
  return {};
}

int main(int argc, char* argv[]) {
  if (!check_args(argc,argv)) {
    return EXIT_FAILURE;
  }

  // 1. Valida que la variable BACKUP_WORK_DIR esté definida
  if (get_work_dir_path().empty()) {
    std::cerr << "backup: error: la variable global WORK_BACKUP_DIR no esta definida" << std::endl;
    return EXIT_FAILURE;
  }

  // 2. Verifica que el archivo existe y es un archivo regular.
  std::string archivo = argv[1];
  if ( !file_exists(archivo)) {
    std::cerr << "backup: error: el archivo no existe"  << std::endl;
    return EXIT_FAILURE;
  }
  if (!is_regular_file(archivo)) {
    std::cerr << "backup: error: el archivo no es regular"  << std::endl;
    return EXIT_FAILURE;
  }

  auto work_dir_exist = check_work_dir_exists(get_work_dir_path());
  if (!work_dir_exist.has_value()) {
    std::cerr << "backup: error: " << work_dir_exist.error().what() << std::endl;
    return EXIT_FAILURE;
  }

  // 3. Lee el PID del servidor desde el archivo backup-server.pid. y 4. Verifica que el servidor está ejecutándose.
  pid_t pid_server;
  auto pid_servidor = read_server_pid(get_pid_file_path());
  if(!pid_servidor.has_value()) {
    std::cerr << "backup: error: el servidor no está ejecutándose" << std::endl;
    return EXIT_FAILURE;
  } else {
    pid_server = pid_servidor.value();
    if(is_server_running(pid_server)) {
      std::cerr << "backup-server: error: ya hay un servidor ejecutándose (PID " << pid_server << ")" << std::endl;
      return EXIT_FAILURE;
    } else {
      std::cerr << "backup-server: aviso: se encontró un archivo PID huérfano, continuando..." << std::endl;
    }
  }

  // 7. Convierte la ruta del archivo a ruta absoluta
  auto path_result = get_absolute_path(archivo);
  if (!path_result.has_value()) {
    std::cerr << "backup: error: fallo al convertir la ruta a absoluta" << std::endl;
    return EXIT_FAILURE;
  }
  std::string ruta_absoluta = path_result.value();

  // 5. Bloquea la señal SIGPIPE.
  sigset_t sigset;
  sigemptyset(&sigset);
  sigaddset(&sigset, SIGPIPE);
  if (sigprocmask(SIG_BLOCK, &sigset, NULL) == -1) {
    std::cerr << "backup: error al bloquear el SIGPIPE" << std::endl;
    return EXIT_FAILURE;
  }

  //  6. Abre la FIFO para escritura.
  std::string path_fifo = get_fifo_path();
  int fd = open(path_fifo.c_str(), O_WRONLY);
  if (fd == -1) {
    std::cerr << "backup: error: No se ha podido abrir el fifo para escribir" << std::endl;
    return EXIT_FAILURE;
  }

  // 8. Escribir la ruta en la FIFO
  auto write_path_result = write_path_to_fifo(fd, ruta_absoluta);
  if (!write_path_result.has_value()) {
    std::cerr << "backup: error: " << write_path_result.error().what() << std::endl;
    close(fd);
    return EXIT_FAILURE;
  }

  // 9. Enviar la señal SIGUSR1 al servidor
  if (kill(pid_server, SIGUSR1) == -1) {
    std::cerr << "backup: error: no se ha podido enviar la señal SIGUSR1" << std::endl;
    close(fd);
    return EXIT_FAILURE;
  }

  // 10. Cerrar la FIFO
  close(fd);

  // 11. Mensaje de confirmación
  std::cout << "solicitud enviada" << std::endl;
  return EXIT_SUCCESS;
}