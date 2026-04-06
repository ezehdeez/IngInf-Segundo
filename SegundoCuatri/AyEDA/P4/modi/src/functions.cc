/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * 
 * @subject: AyEDA - P4
 * 
 * @file functions.cc
 * @author Ezequiel Hernández Poleo (alu0101735399@ull.edu.es)
 * @date 2026-03-22
 * @brief Main functions used by main.cc, such us argument parser and the menu
 *        itself.
 */

#include <cstdlib>
#include <iostream>

#include "../include/config.h"
#include "../include/ddispersion_ef.h"
#include "../include/functions.h"
#include "../include/hash_table.h"
#include "../include/lineal_ef.h"
#include "../include/modulo_df.h"
#include "../include/nif.h"
#include "../include/pseudorandom_df.h"
#include "../include/quadratic_ef.h"
#include "../include/redispersion_ef.h"
#include "../include/sequence.h"
#include "../include/sum_df.h"

void PrintUsage() {
  std::cerr << "Uso incorrecto del programa.\n"
            << "Opciones obligatorias:\n"
            << "  -ts <s>         : Tamaño de la tabla (entero)\n"
            << "  -fd <f>         : Función de dispersión (ej: mod, sum, rand)\n"
            << "  -hash <type>    : Técnica de dispersión (open o close)\n"
            << "\nOpciones adicionales (solo si -hash es close):\n"
            << "  -bs <s>         : Tamaño del bloque (entero)\n"
            << "  -fe <f>         : Función de exploración (ej: lin, quad, dob, red)\n";
  std::exit(EXIT_FAILURE);
}

ProgramConfig ParseArguments(int argc, char* argv[]) {
  ProgramConfig config;
  for (int i = 1; i < argc; ++i) {
    std::string arg = argv[i];

    if (arg == "-ts" && i + 1 < argc) {
      config.table_size = std::stoi(argv[++i]);
    } else if (arg == "-fd" && i + 1 < argc) {
      config.disp_func = argv[++i];
    } else if (arg == "-hash" && i + 1 < argc) {
      config.hash_type = argv[++i];
    } else if (arg == "-bs" && i + 1 < argc) {
      config.block_size = std::stoi(argv[++i]);
    } else if (arg == "-fe" && i + 1 < argc) {
      config.exp_func = argv[++i];
    } else {
      PrintUsage();
    }
  }
  if (config.table_size == 0 || config.disp_func.empty() || config.hash_type.empty()) {
    PrintUsage();
  }
  if (config.hash_type == "close") {
    if (config.block_size == 0 || config.exp_func.empty()) {
      std::cerr << "Error: La dispersión cerrada requiere -bs y -fe.\n";
      PrintUsage();
    }
  }
  return config;
}

Sequence<NIF>* CreateTable(const ProgramConfig& config) {
  DispersionFunction<NIF>* fd = nullptr;
  if(config.disp_func == "mod") {
    fd = new ModuloDF<NIF>(config.table_size);
  } else if(config.disp_func == "sum") {
    fd = new SumDF<NIF>(config.table_size);
  } else if(config.disp_func == "ran") {
    fd = new PseudorandomDF<NIF>(config.table_size);
  }
  if(config.hash_type == "open") {
    return new HashTable<NIF, dynamicSequence<NIF>>(config.table_size, *fd);
  } else {
    ExplorationFunction<NIF>* fe = nullptr;
    if(config.exp_func == "lin") {
      fe = new LinearEF<NIF>();
    } else if(config.exp_func == "quad") {
      fe = new QuadraticEF<NIF>();
    } else if(config.exp_func == "dob") {
      DispersionFunction<NIF>* fd_aux = new SumDF<NIF>(config.table_size);
      fe = new DDispersionEF<NIF>(*fd_aux);
    } else if(config.exp_func == "red") {
      fe = new RedispersionEF<NIF>();
    }
    return new HashTable<NIF, staticSequence<NIF>>(config.table_size, *fd, *fe, config.block_size);
  }
}

void RunMenu(Sequence<NIF>& tabla) {
  int option = 0;
  long input_dni;

  while (option != 3) {
    std::cout << "\n=== MENÚ TABLA HASH ===\n"
              << "COMPARATION COUNTER: " << NIF::GetCounter() << "\n"
              << "1. Insertar un NIF\n"
              << "2. Buscar un NIF\n"
              << "3. Salir\n"
              << "Elige una opción: ";      
    std::cin >> option;
    switch(option) {
      case 1: {
        std::cout << "Introduce el DNI a insertar (max 8 dígitos): ";
        std::cin >> input_dni;
        try {
          NIF nuevo_nif(input_dni);
          NIF::ResetCounter();
          if (tabla.insert(nuevo_nif)) {
            std::cout << "[ÉXITO] El NIF " << input_dni << " se ha insertado correctamente.\n";
          } else {
            std::cout << "[FALLO] No se pudo insertar. ¿La tabla está llena o el NIF ya existe?\n";
          }
        } catch (const std::invalid_argument& e) {
          std::cerr << e.what() << "\n";
        }
        break;
      }

      case 2: {
        std::cout << "Introduce el DNI a buscar: ";
        std::cin >> input_dni;
        try {
          NIF nif_buscado(input_dni);
          NIF::ResetCounter();
          if (tabla.search(nif_buscado)) {
            std::cout << "[ENCONTRADO] El NIF " << input_dni << " ESTÁ en la tabla.\n";
          } else {
            std::cout << "[NO ENCONTRADO] El NIF " << input_dni << " NO está en la tabla.\n";
          }
        } catch (const std::invalid_argument& e) {
          std::cerr << "[ERROR DE FORMATO] " << e.what() << "\n";
        }
        break;
      }
      case 3:
        std::cout << "Saliendo del simulador...\n";
        break;
      default:
        std::cout << "Opción incorrecta. Elige 1, 2 o 3.\n";
    }
  }
}