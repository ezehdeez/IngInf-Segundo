/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * 
 * @subject: CyA 25-26
 *           P04 - Expresiones regulares en C++
 * 
 * @file variable.h
 * @author Ezequiel Hernández Poleo (alu0101735399@ull.edu.es)
 * @date 2025-10-05
 * @brief This file contains the Variable class declaration.
 */

#pragma once

#include <string>
#include <iostream>
#include <regex>

class Variable {
 public:

  // Constructors
  Variable() = default;
  Variable(const int line, const std::smatch& content);

  // Getters
  int getLine() const {return line_;}
  std::string getValue() const {return value_;}
  std::string getVarName() const {return var_name_;}
  bool getVariableType() const {return variable_type_;}
  bool getInitialized() const {return initialized_;}
 private:
  int line_;
  std::string value_;
  std::string var_name_;
  bool variable_type_; // 0 -> int, 1 -> double
  bool initialized_;
};

std::ostream& operator<<(std::ostream& out, Variable& variable);