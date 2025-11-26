/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * 
 * @subject: CyA 25-26
 *           P04 - Expresiones regulares en C++
 * 
 * @file loop.h
 * @author Ezequiel Hernández Poleo (alu0101735399@ull.edu.es)
 * @date 2025-10-05
 * @brief This file contains the Statement class declaration
 */

#pragma once

#include <regex>
#include <iostream>

class Statement{
 public:

  // Constructors
  Statement() = default;
  Statement(const int line, const std::smatch& content) : line_{line}, 
  statement_type_{content[1]} {};
  /**
   *      ^\s*(while|for)[\s\S]*$   REGEX
   * content[1] -> loop type (for|while)
   */

   // Getters
  int getLine() {return line_;}
  std::string getTypeStr() {return statement_type_;}
 private:
  int line_;
  std::string statement_type_;
};

std::ostream& operator<<(std::ostream& out, Statement& statement);