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

#include <string>
#include <vector>
#include <iostream>
#include <expected>
#include <atomic>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <limits.h>
#include <sys/stat.h>
#include <sys/types.h>

std::string get_work_dir_path();
std::string get_fifo_path();
std::string get_pid_file_path();
std::expected<std::string, std::system_error> get_absolute_path(const std::string& path);
bool file_exists(const std::string& path);
bool is_regular_file(const std::string& path);
bool is_directory(const std::string& path);
std::string get_current_dir();
std::string get_filename(const std::string& path);
std::expected<pid_t, std::system_error> read_server_pid(const std::string& pid_file_path);
bool is_server_running(pid_t pid);
std::expected<void, std::system_error> copy_file(const std::string& src_path, 
                                                const std::string& dest_path, 
                                                mode_t dst_perms = 0644);
