/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * 
 * @subject: SSOO
 * 
 * @file copy.h
 * @author Ezequiel Hernández Poleo (alu0101735399@ull.edu.es)
 * @date 2025-11-26
 * @brief 
 */

#include <iostream>
#include <string>
#include <expected>

std::expected<void, std::system_error> copy_file(const std::string& src_path, 
                                                const std::string& dest_path, 
                                                mode_t dst_perms = 0);
std::string get_filename(const std::string& path);
bool is_directory(const std::string& path);