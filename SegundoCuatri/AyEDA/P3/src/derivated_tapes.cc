/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * 
 * @subject: 
 * 
 * @file derivated_tapes.cc
 * @author Ezequiel Hernández Poleo (alu0101735399@ull.edu.es)
 * @date 2026-03-09
 * @brief 
 */

#include "../include/derivated_tapes.h"

void TapePeriodic::PrintCell(const int x, const int y) {
  std::cout << ColorToCode(grid_[x][y]) << "■" << RESET;
}

void TapePeriodic::CheckMove(Ant* ant) {
  if(ant->GetX() >= static_cast<int>(GetXSize())) {
    ant->SetX(0);
  } else if(ant->GetX() < 0) {
    ant->SetX(GetXSize() - 1);
  }

  if(ant->GetY() >= static_cast<int>(GetYSize())) {
    ant->SetY(0);
  } else if(ant->GetY() < 0) {
    ant->SetY(GetYSize() - 1);
  }
}

void TapeReflective::PrintCell(const int x, const int y) {
  std::cout << ColorToCode(grid_[x][y]) << "■" << RESET;
}

void TapeReflective::CheckMove(Ant* ant) {
  bool out_of_bounds = false;
  if(ant->GetX() >= static_cast<int>(GetXSize())) {
    ant->SetX(GetXSize() - 1);
    out_of_bounds = true;
  } else if (ant->GetX() < 0) {
    ant->SetX(0);
    out_of_bounds = true;
  }
  if(ant->GetY() >= static_cast<int>(GetYSize())) {
    ant->SetY(GetYSize() - 1);
    out_of_bounds = true;
  } else if (ant->GetY() < 0) {
    ant->SetY(0);
    out_of_bounds = true;
  }
  if(out_of_bounds) {
    ant->TurnRight();
    ant->TurnRight();
  }
}

void TapeSliding::PrintCell(const int x, const int y) {
  std::cout << ColorToCode(grid_[x][y]) << "■" << RESET;
}

void TapeSliding::FillVectorAsDefalult(SlidingVector<Color>& vector) {
  for(int i = vector.GetMinValue(); i <= vector.GetMaxValue(); i++) {
    vector[i] = Color::WHITE_CELL;
  }
}

Color TapeSliding::GetCell(int x, int y) const {
  try {
    const SlidingVector<Color>& column = grid_[x];
    try {
      return column[y];    
    } catch (const SVException& e_y) {
      return Color::WHITE_CELL; 
    }
  } catch(const SVException& e_x) {
    return Color::WHITE_CELL;
  }
}

void TapeSliding::DrawCell(int x, int y, const Color& color) {
  bool cell_drawn = false;
  while (!cell_drawn) {
    try {
      SlidingVector<Color>& column = grid_[x];
      try {
        column[y] = color;
        cell_drawn = true; // ¡Si llegamos aquí, se dibujó con éxito y salimos del while!    
      } catch (const SVException& e_y) {      
        if (y < e_y.min()) {
          for (int i = grid_.GetMinValue(); i <= grid_.GetMaxValue(); i++) {
            grid_[i].PushFront(Color::WHITE_CELL);
          }
        } else if (y > e_y.max()) {
          for (int i = grid_.GetMinValue(); i <= grid_.GetMaxValue(); i++) {
            grid_[i].PushBack(Color::WHITE_CELL);
          }
        }
      }
    } catch (const SVException& e_x) {
      int current_min_y = grid_[grid_.GetMinValue()].GetMinValue();
      int current_max_y = grid_[grid_.GetMinValue()].GetMaxValue();
      if (x < e_x.min()) {
        SlidingVector<Color> new_col(current_min_y, current_max_y);
        FillVectorAsDefalult(new_col);
        grid_.PushFront(new_col);
      } else if (x > e_x.max()) {
        SlidingVector<Color> new_col(current_min_y, current_max_y);
        FillVectorAsDefalult(new_col);
        grid_.PushBack(new_col);
      }
    }
  }
}