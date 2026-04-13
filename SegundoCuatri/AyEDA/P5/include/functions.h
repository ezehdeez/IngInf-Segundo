/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * 
 * @subject: AyEDA - P5
 * 
 * @file functions.h
 * @author Ezequiel Hernández Poleo (alu0101735399@ull.edu.es)
 * @date 2026-04-12
 * @brief Declares utility functions for argument parsing and usage display, 
 *        along with polymorphic factories for creating sequences and sorting 
 *        methods.
 */

#pragma once

#include "../include/config.h"
#include "../include/nif.h"
#include "../include/static_sequence.h"
#include "../include/sort_method.h"

void PrintUsage(const std::string& program_name);
ProgramConfig ParseArguments(int argc, char* argv[]);
staticSequence<NIF>* BuildSequence(const ProgramConfig& config);
SortMethod<NIF>* BuildSortMethod(const ProgramConfig& config);