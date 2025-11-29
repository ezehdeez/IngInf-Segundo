#include <iostream>
#include <string>
#include <vector>
#include <unistd.h>
// Stat
#include <sys/types.h>
#include <sys/stat.h>
// Basename
#include <libgen.h>
// Expected
#include <expected>
// Errores
#include <cerrno>
#include <fcntl.h>

#include "../includes/copy.h"

bool check_args(int argc, char* argv[]) {
  if(argc != 3) {
    std::cerr << "[ERROR] Copy: Se deben indicar los archivos ORIGEN y DESTINO" << std::endl;
    return false;
  }
  struct stat st1, st2;
  int res_file1 = stat(argv[1], &st1);
  int res_file2 = stat(argv[2], &st2);      
  if (res_file1 == 0 && res_file2 == 0) {
    if (st1.st_dev == st2.st_dev && st1.st_ino == st2.st_ino) {
      std::cerr << "copy: el archivo ORIGEN y DESTINO no pueden ser el mismo" << std::endl;
      return false;
    }
  }
  return true;
}

bool is_directory(const std::string& path) {
  struct stat st;
  if(stat(path.c_str(), &st) == -1) {
    std::cerr << "[ERROR] Copy: Al guardar el stat en el metodo is_directory" << std::endl;
    return false;
  } else {
    return S_ISDIR(st.st_mode);
  }
}

std::string get_filename(const std::string& path) {
  std::vector<char> buffer(path.length() + 1);
  path.copy(buffer.data(), path.length());
  buffer[path.length()] = '\0';
  char* filename = basename(buffer.data());
  return std::string(filename);
}

std::expected<void, std::system_error> copy_file(const std::string& src_path, 
                                                const std::string& dest_path, 
                                                mode_t dst_perms = 0) {
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

int main(int argc, char* argv[]) {
  if(!check_args(argc, argv)) {
      return EXIT_FAILURE;
  }
  std::string source = argv[1];
  std::string destination = argv[2];
  if(is_directory(destination)) {
    std::string file_name = get_filename(source);
    destination = destination + '/' + file_name;
  }
  std::expected<void, std::system_error> resultado = copy_file(source, destination);
  if (!resultado.has_value()) {
      std::cerr << "copy: " << resultado.error().what() << std::endl;
      return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}