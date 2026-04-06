/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 *  
 * @subject: AyEDA - P3
 * 
 * @file functions.h
 * @author Ezequiel Hernández Poleo (alu0101735399@ull.edu.es)
 * @date 2026-03-22
 * @brief Declaration of auxiliary program functions: argument parsing,
 * factory function to initialize the table, and interactive menu.
 */

#pragma once

#include "../include/config.h"
#include "../include/nif.h"
#include "../include/sequence.h"

ProgramConfig ParseArguments(int argc, char* argv[]);
void RunMenu(Sequence<NIF>& tabla);
Sequence<NIF>* CreateTable(const ProgramConfig& config);