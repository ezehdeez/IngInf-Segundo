/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * 
 * @subject: AyEDA - P7
 * 
 * @file functions.cc
 * @author Ezequiel Hernández Poleo (alu0101735399@ull.edu.es)
 * @date 2026-04-16
 * @brief Function implementations for argument parsing, tree creation, 
 *        initialization, and user interaction.
 */

#include "../include/functions.h"
#include "../include/nif.h"

#include <fstream>

void PrintUsage(const std::string& program_name) {
  std::cout << "\nUso: " << program_name << " -ab <tipo_arbol> [opciones]\n"
            << "\n"
            << "Descripción:\n"
            << "  Programa para la gestión y visualización de Árboles Binarios.\n"
            << "  Permite la inserción, búsqueda y recorrido (Inorden y por niveles).\n"
            << "\n"
            << "Opciones obligatorias:\n"
            << "  -ab <tipo>    Especifica el tipo de árbol a construir.\n"
            << "                Valores permitidos:\n"
            << "                  abb : Árbol Binario de Búsqueda\n"
            << "                  abe : Árbol Binario Equilibrado\n"
            << "                  avl : Árbol Binario de Búsqueda Balanceado"
            << "\n"
            << "Opciones adicionales (ejemplos comunes):\n"
            << "  -init <modo>  Modo de inicialización inicial del árbol.\n"
            << "                Valores: manual, random, file\n"
            << "  -trace <y/n>  Muestra la traza de balanceo para el caso de avl\n"
            << "  -h            Muestra este manual de uso y finaliza la ejecución.\n"
            << "\n"
            << "Ejemplo de ejecución:\n"
            << "  " << program_name << " -ab avl -init manual -trace y\n\n";
}

ProgramConfig ParseArguments(int argc, char* argv[]) {
  if (argc == 1) {
    PrintUsage(argv[0]);
    std::exit(EXIT_FAILURE);
  }
  ProgramConfig config;
  std::vector<std::string> args(argv + 1, argv + argc);
  for(size_t i = 0; i < args.size(); ++i) {
    if(args[i] == "-h") {
      PrintUsage(argv[0]);
      std::exit(EXIT_SUCCESS);
    }
    if(args[i] == "-ab") {
      if (++i < args.size()) {
        config.tree_type = args[i];
      } else {
        throw std::runtime_error("[ERROR]: Falta el dato para -ab");
      }
    } else if(args[i] == "-init") {
      if(++i < args.size()) {
        config.init_mode = args[i]; // manual, random o file
        if(config.init_mode == "random") {
          if (++i < args.size()) {
            config.element_amount = std::stoi(args[i]);
          } else {
            throw std::runtime_error("[ERROR]: Modo 'random' requiere una cantidad de elementos");
          }
        }
      }
      if(config.init_mode == "file") {
        if(++i < args.size()) {
          config.element_amount = std::stoi(args[i]);
        } else {
          throw std::runtime_error("[ERROR]: Modo 'file' requiere una cantidad de elementos");
        }
        if(++i < args.size()) {
          config.file_name = args[i];
        } else {
          throw std::runtime_error("[ERROR]: Modo 'file' requiere un nombre de fichero");
        }
      }
    } else if(args[i] == "-trace") {
      if(++i < args.size()) {
        if(args[i] == "y") {
          config.trace = true;
        } else if(args[i] == "n") {
          config.trace = false;
        } else {
          throw std::runtime_error("[ERROR]: El parámetro -trace debe ser 'y' o 'n'");
        }
      } else {
        throw std::runtime_error("[ERROR]: El parámetro -trace requiere un <y/n>");
      }
    }
  }
  return config;
}

AB<NIF>* BuildTree(const ProgramConfig& config) {
  if(config.tree_type == "abb") {
    return new ABB<NIF>();
  } else if(config.tree_type == "abe") {
    return new ABE<NIF>();
  } else if(config.tree_type == "avl") {
    return new AVL<NIF>(config.trace);
  }
  throw std::runtime_error("[ERROR]: Tipo de árbol no soportado (" + config.tree_type + "). Usa 'abb', 'abe' o 'avl'.");
}

void InitializeTree(AB<NIF>* arbol, const ProgramConfig& config) {
  if(config.init_mode == "manual") {
    std::cout << "[INFO]: Árbol inicializado vacío.\n";
  } 
  else if(config.init_mode == "random") {
    for(size_t i = 0; i < config.element_amount; i++) {
      NIF valor_aleatorio{rand() % 100000000};
      arbol->insertar(valor_aleatorio);
    }
    std::cout << "[INFO]: Árbol inicializado con " << config.element_amount << " valores aleatorios.\n";
  } 
  else if(config.init_mode == "file") {
    std::ifstream archivo(config.file_name);
    if(!archivo.is_open()) {
      throw std::runtime_error("[ERROR]: No se pudo abrir el fichero " + config.file_name);
    }
    long valor;
    size_t count = 0;
    while(count < config.element_amount && archivo >> valor) {
      arbol->insertar(NIF(valor));
      ++count;
    }
    archivo.close();
    std::cout << "[INFO]: Árbol inicializado desde fichero.\n";
  }
}

void RunMenu(AB<NIF>* arbol) {
  int opcion = -1;
  while (opcion != 0) {
    std::cout << "==============================\n"
              << "[0] Salir\n"
              << "[1] Insertar clave\n"
              << "[2] Buscar clave\n"
              << "[3] Mostrar árbol (Inorden)\n"
              << "==============================\n"
              << "Selecciona una opción: ";
    std::cin >> opcion;
    switch(opcion) {
      case 0:
        std::cout << "Saliendo...\n";
        break;
      case 1: {
        long valor;
        std::cout << "Introduce el valor a insertar: ";
        std::cin >> valor;
        if(arbol->insertar(NIF(valor))) {
          std::cout << "[DONE]: Elemento insertado correctamente.\n";
        } else {
          std::cout << "[WARNING]: La clave ya existe en el árbol.\n";
        }
        std::cout << "\nESTADO ACTUAL DEL ÁRBOL (Niveles):\n";
        std::cout << *arbol; 
        break;
      }
      case 2: {
        long valor;
        std::cout << "Introduce el valor a buscar: ";
        std::cin >> valor;
        if (arbol->buscar(NIF(valor))) {
          std::cout << "[RESULTADO]: La clave " << valor << " se encuentra en el árbol.\n";
        } else {
          std::cout << "[RESULTADO]: La clave " << valor << " NO se encuentra en el árbol.\n";
        }
        break;
      }
      case 3:
        arbol->inorden();
        break;
      default:
        std::cout << "[ERROR]: Opción no válida.\n";
        break;
    }
  }
}