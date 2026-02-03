/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * 
 * @subject: 
 * 
 * @file class.h
 * @author Ezequiel Hernández Poleo (alu0101735399@ull.edu.es)
 * @date 2025-10-08
 * @brief 
 */

#pragma once

#include <string>
#include <iostream>
#include <regex>

class Class{
 public:
  Class(const int start_line, const int end_line, const std::string& name) : 
  start_line_{start_line}, end_line_{end_line}, name_{name} {}

  // Getters
  int getStartLine() const {return start_line_;}
  int getEndLine() const {return end_line_;}
  std::string getName() const {return name_;}

 private:
  int start_line_;
  int end_line_;
  std::string name_;
};

std::ostream& operator<<(std::ostream& out, Class& classes);