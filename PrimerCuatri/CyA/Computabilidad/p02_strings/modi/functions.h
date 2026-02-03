/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * 
 * @subject: CyA 25-26
 *           P02 - Cadenas y Lenguajes
 * 
 * @file functions.h
 * @author Ezequiel Hernández Poleo (alu0101735399@ull.edu.es)
 * @date 2025-09-17
 * @brief Functions declarations.
 */

#pragma once

#include <fstream>

void CheckCorrectParameters(int argc, const int kCorrectNumber);
void FileCheck(std::ifstream& input_file, std::ofstream& output_file);
void HelpMessage(char* argv[]);
void OpSelector(std::ifstream& input_file, std::ofstream& output_file, int opcode);