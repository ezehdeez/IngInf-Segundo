/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * 
 * @subject: SSOO
 * 
 * @file functions.cc
 * @author Ezequiel Hernández Poleo (alu0101735399@ull.edu.es)
 * @date 2025-12-02
 * @brief 
 */
  
#include "../includes/functions.h"
 
std::string get_environment_variable(const std::string& name) {
  char* value = getenv(name.c_str());
  if(value) {
    return std::string(value);
  } else {
    return std::string();
  }
}

std::string get_work_dir_path() {
  return get_environment_variable("BACKUP_WORK_DIR");
}

std::string get_fifo_path() {
  return get_work_dir_path() + "/backup.fifo";
}

std::string get_pid_file_path() {
  return get_work_dir_path() + "/backup-server.pid";
}

std::expected<std::string, std::system_error> get_absolute_path(const std::string& path) {
  char* presolved_path = realpath(path.c_str(), nullptr);
  if(presolved_path == nullptr) {
    int error = errno;
    return std::unexpected(std::system_error(error, std::system_category(),"[ERROR]: La ruta no existe o es inaccesible"));
  }
  std::string absolute_path(presolved_path);
  free(presolved_path);
  return absolute_path;
}

bool file_exists(const std::string& path) {
  if(access(path.c_str(), F_OK) == 0) {
    return true;
  }
  return false;
}

bool is_regular_file(const std::string& path) {
  struct stat file_info;
  if(stat(path.c_str(), &file_info) == -1) {
    std::cerr << "[WARNING]: Error al guardar el stat (is_regular_file())";
    return false;
  }
  if(S_ISREG(file_info.st_mode)) { // COMPROBACIÓN: FICHERO REGULAR
    return true;
  }
  return false;
}

bool is_directory(const std::string& path) {
  struct stat file_info;
  if(stat(path.c_str(), &file_info) == -1) {
    std::cerr << "[WARNING]: Error al guardar el stat (is_directory())" << std::endl;
    return false;
  }
  if(S_ISDIR(file_info.st_mode)) { // COMPROBACIÓN: DIRECTORIO
    return true;
  }
  return false;
}

std::string get_current_dir() {
  char* pcurrent_dir = getcwd(NULL, 0);
  if(pcurrent_dir == NULL) {
    std::cerr << "[WARNING]: Error al leer el directorio actual";
    return "";
  }
  std::string current_dir(pcurrent_dir);
  free(pcurrent_dir);
  return current_dir;
}

std::string get_filename(const std::string& path) {
  size_t posicion = path.find_last_of("/");
  std::string nombre = path.substr(posicion + 1);
  return nombre;
}

std::expected<pid_t, std::system_error> read_server_pid(const std::string& pid_file_path) {
  char buffer[256]; // Tamaño máximo para un PID
  int fd = open(get_pid_file_path().c_str(), O_RDONLY);
  if(fd == -1) {
    int error = errno;
    return std::unexpected(std::system_error(errno, std::system_category(), "[ERROR]: Error al abrir el archivo del PID del servidor"));
  }
  ssize_t bytes_read = read(fd, buffer, sizeof(buffer) - 1);
  if(bytes_read == -1) {
    int error = errno;
    close(fd);
    return std::unexpected(std::system_error(errno, std::system_category(), "[ERROR]: Error al leer el archivo del PID del servidor"));
  }
  buffer[bytes_read] = '\0';
  pid_t pid = std::atoi(buffer);
  close(fd);
  if(pid <= 0) {
    int error = errno;
    return std::unexpected(std::system_error(errno, std::system_category(), "[ERROR]: El PID leído es 0 o no es válido"));
  }
  return pid;
}

bool is_server_running(pid_t pid) {
  if(kill(pid, 0) == -1) {
    if(errno == ESRCH) {
      // El proceso con ese PID no existe
      return false;
    }
    return true;
  } else {
    return true;
  }
}

std::expected<void, std::system_error> copy_file(const std::string& src_path, 
                                                const std::string& dest_path, 
                                                mode_t dst_perms) {
  int input_file = open(src_path.c_str(), O_RDONLY);
  if(input_file == -1) {
    return std::unexpected(std::system_error(errno, std::system_category(), "[ERROR] Copy: Error al abrir el archivo de origen"));
  }
  int output_file = open(dest_path.c_str(), O_WRONLY | O_CREAT | O_TRUNC, dst_perms);
  if (output_file == -1) {
    int error = errno;
    close(input_file);  
    return std::unexpected(std::system_error(error,std::system_category(),"[ERROR] Copy: Error al abrir el archivo de destino"));
  }
  const size_t BUFFER_SIZE = 65536;
  char buffer[BUFFER_SIZE];
  while(true) {
    ssize_t bytes_read = read(input_file, buffer, BUFFER_SIZE);
    if(bytes_read == -1) {
      int error = errno;
      close(input_file);
      close(output_file);
      return std::unexpected(std::system_error(error, std::system_category(),"[ERROR] Copy: Error al leer el archivo de origen"));
    } else if(bytes_read == 0) {
      break;
    }
    ssize_t bytes_written = write(output_file, buffer, bytes_read);
    if (bytes_written == -1) {
      int error = errno;
      close(input_file);
      close(output_file);
      return std::unexpected(std::system_error(error, std::system_category(), "[ERROR] Copy: Error al escribir el archivo de destino"));
    }
    if (bytes_written != bytes_read) {
      close(input_file);
      close(output_file);
      return std::unexpected(std::system_error(EIO, std::system_category(), "[ERROR] Copy: Escritura incompleta"));
    }
  }
  close(input_file);
  close(output_file);
  return {};
}