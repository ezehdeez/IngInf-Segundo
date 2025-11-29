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
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/stat.h>
#include <sys/types.h>

#include "../includes/functions.h"
#include "../includes/copy.h"

const std::string BACKUP_WORK_DIR = GetEnviromentalVariable("BACKUP_WORK_DIR");

std::expected<pid_t, std::system_error> read_server_pid(const std::string& pid_file_path) {
  std::string filename = get_filename(pid_file_path);
  int server = open(filename.c_str(), O_RDONLY);
  if(server == -1) {
    return std::unexpected(std::system_error(errno, std::system_category(), "[ERROR] backup-server: Error al abrir el archibo backup-server.pid"));
  }
  // TODO: REVISAR COMO LEER EL PID
  const size_t BUFFER_SIZE = 65536;
  char buffer[BUFFER_SIZE];
  while(true) {
    ssize_t bytes_read = read(server, buffer, BUFFER_SIZE);
    if(bytes_read == -1) {
      int error = errno;
      close(server);
      return std::unexpected(std::system_error(error, std::system_category(),"[ERROR] Copy: Error al leer el archivo de origen"));
    } else if(bytes_read == 0) {
      break;
    }
  }
  // HASTA AQUI
  close(server);
  return pid_t(buffer);
}

bool is_server_running(pid_t pid) {
  if(kill(pid, 0) == 0) {
    return true;
  } else {
    if(errno == EPERM) {
      return true;
    } else {
      return false;
    }
  }
}

std::expected<void, std::system_error> create_fifo(const std::string& fifo_path) {
  int result = mkfifo(fifo_path.c_str(), 0666);
  if(result == -1) {
    if(errno == EEXIST) {
      unlink(fifo_path.c_str());
      result = mkfifo(fifo_path.c_str(), 0666);
    } else if(errno == EACCES) {
      return std::unexpected(std::system_error(errno, std::system_category(), "[ERROR] backup-server: No hay permisos para crear archivos en el directorio indicado"));
    } else {
      return std::unexpected(std::system_error(errno, std::system_category(), "[ERROR] backup-server: Algún componente de la ruta no existe"));
    }
  }
  return {};
}

std::expected<void, std::system_error> write_pid_file(const std::string& pid_file_path) {
  int server = open(pid_file_path.c_str(), O_WRONLY | O_CREAT | O_TRUNC, 0644);
  if(server == -1) {
    return std::unexpected(std::system_error(errno, std::system_category(), "[ERROR] backup-server: Error al abrir el archivo del pid"));
  }
  ssize_t bytes_written; // TODO: Añadir el write()
}

std::expected<void, std::system_error> setup_signal_handler() {}

std::expected<std::string, std::system_error> read_path_from_fifo(int fifo_fd) {}

void run_server(int fifo_fd, const std::string& backup_dir) {}

int main(int argc, char* argv[]) {
  
}