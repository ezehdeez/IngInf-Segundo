/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * 
 * @subject: SSOO
 * 
 * @file functions.h
 * @author Ezequiel Hernández Poleo (alu0101735399@ull.edu.es)
 * @date 2025-11-26
 * @brief 
 */

#include <iostream>
#include <string>
#include <expected>

std::string GetEnviromentalVariable(const std::string& name);
std::string get_work_dir_path();
std::string get_fifo_path();
std::expected<std::string, std::system_error> get_absolute_path(const std::string& path);
bool file_exists(const std::string& path);
bool is_regular_file(const std::string& path);
std::string get_current_dir();
