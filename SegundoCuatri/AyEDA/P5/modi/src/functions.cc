/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * 
 * @subject: AyEDA - P5
 * 
 * @file function.cc
 * @author Ezequiel Hernández Poleo (alu0101735399@ull.edu.es)
 * @date 2026-04-12
 * @brief Implements helper functions for command-line parsing, help menu 
 *        display, and the instantiation of sequence and sorting strategy 
 *        objects.
 */

#include "../include/derivated_sort_methods.h"
#include "../include/functions.h"
#include "../include/nif.h"
#include "../include/sort_method.h"

#include <fstream>
#include <iostream>
#include <vector>

void PrintUsage(const std::string& program_name) {
  std::cout << "Uso: " << program_name << " -size <s> -ord <m> -init <i> [f] [-trace y/n]\n\n"
            << "Opciones y argumentos:\n"
            << "  -h            Muestra este mensaje de ayuda y termina la ejecución.\n"
            << "  -size <s>     Tamaño de la secuencia a ordenar (debe ser mayor que 0).\n"
            << "  -ord <m>      Método de ordenación a ejecutar. Valores permitidos:\n"
            << "                  a : Selección\n"
            << "                  b : Burbuja\n"
            << "                  c : MergeSort\n"
            << "                  d : HeapSort\n"
            << "                  e : Por Incrementos Decrecientes\n"
            << "                  e : InsertionSort + SelectionSort + Merge both halfs\n"
            << "  -init <i> [f] Modo de inicialización de la secuencia:\n"
            << "                  manual : El usuario introduce los NIFs por teclado.\n"
            << "                  random : Generación aleatoria de los NIFs.\n"
            << "                  file   : Lectura desde fichero (requiere poner el nombre [f] a continuación).\n"
            << "  -trace <y/n>  Indica si se muestra la secuencia tras cada iteración (y = sí, n = no).\n"
            << "\nEjemplo de uso:\n"
            << "  " << program_name << " -size 10 -ord b -init random -trace y\n"
            << "  " << program_name << " -size 50 -ord a -init file datos.txt -trace n\n";
}

ProgramConfig ParseArguments(int argc, char* argv[]) {
  ProgramConfig config;
  std::vector<std::string> args(argv + 1, argv + argc);
  for(size_t i = 0; i < args.size(); ++i) {
    if(args[i] == "-h") {
      PrintUsage(argv[0]);
    }
    if(args[i] == "-size") {
      if (++i < args.size()) {
        config.sequence_size = std::stoul(args[i]);
      } else {
        throw std::runtime_error("[ERROR]: Falta el valor para -size");
      }
    } else if(args[i] == "-ord") {
      if(++i < args.size()) {
        config.sort_method = args[i][0];
      } else {
        throw std::runtime_error("[ERROR]: Falta el código del método para -ord");
      }
    } else if(args[i] == "-init") {
      if(++i < args.size()) {
        config.init_mode = args[i]; // manual, random o file
        if (config.init_mode == "file") {
          if (++i < args.size()) {
            config.filename = args[i];
          } else {
            throw std::runtime_error("[ERROR]: Modo 'file' requiere un nombre de fichero");
          }
        }
      } else {
        throw std::runtime_error("[ERROR]: Falta el modo para -init");
      }
    } else if(args[i] == "-trace") {
      if(++i < args.size()) {
        config.dotrace = (args[i] == "y");
      } else {
        throw std::runtime_error("[ERROR]: Falta el valor (y/n) para -trace");
      }
    } else {
      throw std::runtime_error("[ERROR]: Argumento desconocido: " + args[i]);
    }
  }

  if(config.sequence_size == 0) {
    throw std::runtime_error("[ERROR]: El tamaño de la secuencia (-size) debe ser mayor que 0.");
  }
  if(config.sort_method == ' ') {
    throw std::runtime_error("[ERROR]: Debe especificar un método de ordenación con -ord.");
  }
  if(config.init_mode.empty()) {
    throw std::runtime_error("[ERROR]: Debe especificar un modo de inicialización con -init.");
  }
  return config;
}

staticSequence<NIF>* BuildSequence(const ProgramConfig& config) {
  staticSequence<NIF>* sequence = new staticSequence<NIF>(config.sequence_size);
  if(config.init_mode == "manual") {
    std::cout << "Introduce the sequence elements (0 to 8 numeric characters): " << std::endl;
    for(size_t i = 0; i < config.sequence_size; i++) {
      long nif;
      std::cin >> nif;
      sequence->insert(nif);
      std::cout << config.sequence_size - i + 1 << " NIFs remain to be added." << std::endl;
    }
  } else if(config.init_mode == "random") {
    for(size_t i = 0; i < config.sequence_size; i++) {
      long nif = rand() % 100000000;
      sequence->insert(nif);
    }
    std::cout << "[INFO]: Random sequence succesfully built." << std::endl;
  } else if(config.init_mode == "file") {
    std::ifstream input_file{config.filename};
    long nif;
    while(input_file >> nif) {
      sequence->insert(nif);
    }
  } else {
    throw std::runtime_error("[ERROR]: Initialization option unrecognized.");
  }
  return sequence;
}

SortMethod<NIF>* BuildSortMethod(const ProgramConfig& config) {
  SortMethod<NIF>* sort_method = nullptr;
  staticSequence<NIF>* sequence = BuildSequence(config);
  switch(config.sort_method) {
    case 'a':
      sort_method = new SelectionSort<NIF>(*sequence, config.dotrace);
      break;
    case 'b':
      sort_method = new BubbleSort<NIF>(*sequence, config.dotrace);
      break;
    case 'c':
      sort_method = new MergeSort<NIF>(*sequence, config.dotrace);
      break;
    case 'd':
      sort_method = new HeapSort<NIF>(*sequence, config.dotrace);
      break;
    case 'e':
      sort_method = new DeltaSort<NIF>(*sequence, config.dotrace);
      break;
    case 'f':
      sort_method = new ModiSort<NIF>(*sequence, config.dotrace);
      break;
    default:
      throw std::runtime_error("[ERROR]: Sort method option unrecognized.");
      break;
  }
  return sort_method;
}