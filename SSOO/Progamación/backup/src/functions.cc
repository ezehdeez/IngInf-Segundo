/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * 
 * @subject: SSOO
 * 
 * @file functions.cc
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

std::string GetEnviromentalVariable(const std::string& name) {
  char* value = getenv(name.c_str());
  if(value) {
  return std::string(value);
  } else {
  return std::string();
  }
}

  bool is_directory(const std::string& path) {
    struct stat camino;
    if(stat(path.c_str(), &camino) == -1) {
      std::cerr << "error al guardar el stat en el metodo is_directory" << std::endl;
      return false;
    } else {
      if (S_ISDIR(camino.st_mode)) {
        return true;
      } else {
        return false;
      }
    }
  }

  std::string get_current_dir() {
    char* cwd_ptr = getcwd(NULL, 0);
    if (cwd_ptr == NULL) {
      return ""; 
    }
    std::string current_dir(cwd_ptr);
    std::free(cwd_ptr);
    return current_dir;
  }

  std::string get_work_dir_path() {
    return GetEnviromentalVariable("BACKUP_WORK_DIR");
  }

  std::string get_pid_file_path() {
    return std::string(get_work_dir_path()+"/backup-server.pid");
  }

  std::string get_fifo_path() {
    return std::string(get_work_dir_path()+"/backup.fifo");
  }

  std::expected<std::string, std::system_error> get_absolute_path(const std::string& path) {
    char* resolved_path_ptr = realpath(path.c_str(), nullptr);
    if (resolved_path_ptr == nullptr) {
      int error_code = errno;
      return std::unexpected(std::system_error(error_code, std::system_category(),"Error: La ruta no existe o es inaccesible"));
    }
    std::string absolute_path(resolved_path_ptr);
    std::free(resolved_path_ptr);
    return absolute_path;
  }

  bool file_exists(const std::string& path) {
    if (access(path.c_str(), F_OK) == 0) {
      return true;
    }
    return false;
  }

  bool is_regular_file(const std ::string& path) {
    struct stat file_info; 
    if (stat(path.c_str(), &file_info) == -1) {
      return false;
    } 
    if (S_ISREG(file_info.st_mode)) { // Comprueba si es un fichero regular
      return true;
    }
    return false;
  }

  std::string get_filename(const std::string& path) {
    size_t posicion = path.find_last_of("/");
    std::string nombre = path.substr(posicion + 1);
    return nombre;
  }

  std::expected<pid_t, std::system_error> read_server_pid(const std::string& pid_file_path) {
    char buffer[256]; // longitud máxima esperada para leer del fichero pid
    int fd = open(pid_file_path.c_str(), O_RDONLY);
    if(fd == -1) {
      return std::unexpected(std::system_error(errno, std::system_category(), "error al abrir el archivo de pid"));
    }
    ssize_t bytes_read = read(fd, buffer, sizeof(buffer) - 1);
    if(bytes_read == -1) {
      int error = errno;
      close(fd);
      return std::unexpected(std::system_error(error,std::system_category(),"error al leer el archivo de pid"));
    }
    buffer[bytes_read] = '\0';
    pid_t pid = std::atoi(buffer);
    close(fd);
    if(pid <= 0) {
      // caso de que el archivo exista pero contenga basura o '0'.
      int error = errno;
      return std::unexpected(std::system_error(error, std::system_category(),"read_server_pid: PID leído no es válido o es 0"));
    }
    return pid;
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