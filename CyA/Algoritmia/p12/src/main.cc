/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * 
 * @subject: CyA 25-26
 *           P12 - Divide & Conquer Algorithm. QuickHull
 * 
 * @file main.cc
 * @author Ezequiel Hernández Poleo (alu0101735399@ull.edu.es)
 * @date 2025-12-16
 * @brief 
 */

#include <iostream>
#include <vector>
#include <fstream>
#include <cstring>

#include "../include/point_set.h"

int main(int argc, char* argv[]) {
  bool generate_dot = false;
  std::string dot_filename = "output.dot";

  for (int i = 1; i < argc; ++i) {
    if(std::strcmp(argv[i], "-d") == 0) {
      generate_dot = true;
    }
  }

  int n;
  if (!(std::cin >> n)) return 0;

  std::vector<CyA::point> points;
  points.reserve(n);

  for (int i = 0; i < n; ++i) {
    double x, y;
    std::cin >> x >> y;
    points.emplace_back(x, y);
  }

  CyA::point_set ps(points);

  ps.write_hull(std::cout);

  if (generate_dot) {
    std::ofstream dot_file(dot_filename);
    if (dot_file.is_open()) {
      ps.write_dot(dot_file);
      std::cout << "\nFichero DOT generado: " << dot_filename << std::endl;
      std::cout << "Ejecuta: neato " << dot_filename << " -Tpdf -o hull.pdf" << std::endl;
    } else {
      std::cerr << "Error abriendo archivo " << dot_filename << std::endl;
    }
  }
  return 0;
}