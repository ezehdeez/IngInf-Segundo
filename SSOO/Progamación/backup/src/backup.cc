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
#include <sys/stat.h>
#include <sys/types.h>

bool check_args(int argc, char* argv[]) {}

std::expected<void, std::system_error> check_work_dir_exists(const std::string& work_dir) {}

std::expected<int, std::system_error> open_fifo_write(const std::string& fifo_path) {}

std::expected<void, std::system_error> write_path_to_fifo(int fifo_fd, const std::string& file_path) {}

int main(int argc, char* argv[]) {
  
}