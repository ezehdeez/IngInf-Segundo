/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * 
 * @subject: AyEDA - P3
 * 
 * @file tape.cc
 * @author Ezequiel Hernández Poleo (alu0101735399@ull.edu.es)
 * @date 2026-02-09
 * @brief Tape class inicialization
 */

#include "../include/ant.h"
#include "../include/colors.h"
#include "../include/tape.h"

#include <iostream>

std::string Tape::ColorToCode(const Color &color) {
  switch (color) {
    case Color::WHITE_CELL : return WHITE;
    case Color::BLACK_CELL : return BLACK;
    case Color::RED_CELL : return RED;
    case Color::BLUE_CELL : return BLUE;
    case Color::GREEN_CELL : return GREEN;
    case Color::LBLUE_CELL : return LBLUE;
    case Color::LGREEN_CELL : return LGREEN;
    case Color::YELLOW_CELL : return YELLOW;
    case Color::CYAN_CELL : return CYAN;
    case Color::GRAY_CELL : return GRAY;
    case Color::ROSE_CELL : return ROSE;
    case Color::ORANGE_CELL : return ORANGE;
    case Color::MAGENTA_CELL: return MAGENTA;
  }
  return "";
}