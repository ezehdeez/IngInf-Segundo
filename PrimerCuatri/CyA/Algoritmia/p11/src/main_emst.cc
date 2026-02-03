/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * 
 * @subject: CyA 25-26
 *           P11 - Greedy Algorithm. EMST
 * 
 * @file main_emst.cc
 * @author Ezequiel Hernández Poleo (alu0101735399@ull.edu.es)
 * @date 2025-12-09
 * @brief 
 */

#include <iostream>
#include <vector>
#include <cstring>
#include <fstream>

#include "../include/point_set.h"
#include "../include/point_types.h"

int main(int argc, char* argv[]) {
  bool generate_dot = false;
  std::string dot_filename = "../test/output.dot";
  for (int i = 1; i < argc; ++i) {
        if (std::strcmp(argv[i], "-d") == 0) {
            generate_dot = true;
        }
    }
    CyA::point_vector points;
    std::cin >> points;
    point_set ps(points);
    std::cout << "EMST Cost: " << ps.get_cost() << std::endl;
    ps.write_tree(std::cout);
    if (generate_dot) {
        std::ofstream dot_file(dot_filename);
        if (dot_file.is_open()) {
            ps.write_dot(dot_file);
            std::cout << "Fichero '" << dot_filename << "' generado correctamente." << std::endl;
            std::cout << "Para visualizar, ejecuta: neato " << dot_filename << " -Tpdf -o salida.pdf" << std::endl;
            dot_file.close();
        } else {
            std::cerr << "Error: No se pudo crear el archivo " << dot_filename << std::endl;
        }
    }
  return 0;
}