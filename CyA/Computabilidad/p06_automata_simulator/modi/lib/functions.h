/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * 
 * @subject: CyA 25-26
 *           P06 - Diseño e implemetación de un simulador de autómatas finitos
 * 
 * @file functions.h
 * @author Ezequiel Hernández Poleo (alu0101735399@ull.edu.es)
 * @date 2025-10-16
 * @brief Functions declarations.
 */

#pragma once

#include <fstream>

#include "../lib/automaton.h"

void CheckCorrectParameters(int argc, const int kCorrectNumber);
void FileCheck(const std::string& input_file_name, const std::string& input_fa_name);
void HelpMessage(char* argv[]);
void PrintStringBelongsToFA(const std::string& input_file_name, Automaton& automaton);