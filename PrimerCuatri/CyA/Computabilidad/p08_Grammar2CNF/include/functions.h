/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * 
 * @subject: CyA 25-26
 *           P08 - Gramáticas en Forma Normal de Chomsky
 * 
 * @file functions.h
 * @author Ezequiel Hernández Poleo (alu0101735399@ull.edu.es)
 * @date 2025-10-29
 * @brief Functions declarations.
 */

#pragma once

#include <fstream>

void CheckCorrectParameters(int argc, const int kCorrectNumber);
void FileCheck(const std::string& input_file_name, const std::string& input_fa_name);
void HelpMessage(char* argv[]);