/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * 
 * @subject: AyEDA - P7
 * 
 * @file functions.h
 * @author Ezequiel Hernández Poleo (alu0101735399@ull.edu.es)
 * @date 2026-04-16
 * @brief Function declarations for argument parsing, tree initialization, and menu handling.
 */

#pragma once

#include "ab.h"
#include "abb.h"
#include "abe.h"
#include "avl.h"
#include "config.h"
#include "nif.h"
#include "nodob.h"

#include <iostream>
#include <string>
#include <vector>

void PrintUsage(const std::string& program_name);
ProgramConfig ParseArguments(int argc, char* argv[]);
AB<NIF>* BuildTree(const ProgramConfig& config);
void InitializeTree(AB<NIF>* arbol, const ProgramConfig& config);
void RunMenu(AB<NIF>* arbol);
