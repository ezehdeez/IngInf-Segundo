/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * 
 * @subject: CyA 25-26
 *           P04 - Expresiones regulares en C++
 * 
 * @file code_struc.h
 * @author Ezequiel Hernández Poleo (alu0101735399@ull.edu.es)
 * @date 2025-10-06
 * @brief This file contains de CodeStructure class declaration which is used to
 *        store, modify and display the code structure of a given c++ program
 *        with .cc extension.
 */

#pragma once

#include <fstream>
#include <string>
#include "comment.h"
#include "variable.h"
#include "statement.h"
#include "class.h"

class CodeStructure{
 public:
  // Constructor
  CodeStructure() = default;
  CodeStructure(const std::string& input_file) : input_file_{input_file} {};

  // Input file getter
  std::string getInputFile() const {return input_file_;}

  // Variable manipulation
  std::vector<Variable> getVariables() const {return variables_;}
  void AddVariable(const Variable& variable) {variables_.push_back(variable);}

  // Statement manipulation
  std::vector<Statement> getStatements() const {return statements_;}
  void AddStatement(const Statement& statement) {statements_.push_back(statement);}

  // Comment manipulation
  std::vector<Comment> getComments() const {return comments_;}
  void AddComment(const Comment& comment) {comments_.push_back(comment);}

  // Main manipulation
  bool getHasMain() const {return has_main_;}
  void setMain(bool val) {has_main_ = val;}

  // Class manipulation
  std::vector<Class> getClasses() const {return classes_;}
  void AddClass(const Class& classes) {classes_.push_back(classes);}

  // Method to fill the vectors in the atributes
  void FillCodeStructure(std::ifstream& input_file);
  
 private:
  std::string input_file_ = "";
  std::vector<Variable> variables_;
  std::vector<Statement> statements_;
  std::vector<Comment> comments_;
  std::vector<Class> classes_;
  bool has_main_ = false;
};

std::ostream& operator<<(std::ostream& out, const CodeStructure code_structure);