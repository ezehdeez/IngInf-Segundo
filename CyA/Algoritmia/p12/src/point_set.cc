/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * 
 * @subject: CyA 25-26
 *           P12 - Divide & Conquer Algorithm. QuickHull
 * 
 * @file point_set.cc
 * @author Ezequiel Hernández Poleo (alu0101735399@ull.edu.es)
 * @date 2025-12-15
 * @brief 
 */

#include "../include/point_set.h"

namespace CyA {

  point_set::point_set(const std::vector<point> &points) : point_vector(points) {
    quickHull();
  }

  void point_set::quickHull(void) {
    hull_.clear();

    point min_x_point; 
    point max_x_point;

    x_bounds(min_x_point, max_x_point);

    quickHull(line(min_x_point, max_x_point), side::LEFT);
    quickHull(line(min_x_point, max_x_point), side::RIGHT);

    // Remove duplicates
    std::sort(hull_.begin(), hull_.end());
    hull_.erase(std::unique(hull_.begin(), hull_.end()), hull_.end());
  }

  void point_set::quickHull(const line &l, int side) {
    point farthest;

    if(farthest_point(l, side, farthest)) {
      quickHull(line(l.first, farthest), -find_side(line(l.first, farthest), l.second));
      quickHull(line(farthest, l.second), -find_side(line(farthest, l.second), l.first));
    } else {
      hull_.push_back(l.first);
      hull_.push_back(l.second);
    }
  }

  bool point_set::farthest_point(const line &l, int side, point &farthest) const {
    farthest = point_vector::at(0);

    double max_dist = 0;

    bool found = false;

    for(const point &p : *this) {
      const double dist = distance(l, p);

      if(find_side(l, p) == side && dist > max_dist) {
        farthest = p;
        max_dist = dist;
        found = true;
      }
    }
    return found;
  }

  double point_set::point_2_line(const line &l, const point &p) const {
    const point &p1 = l.first;
    const point &p2 = l.second;

    return (p.second - p1.second) * (p2.first - p1.first) -
          (p2.second - p1.second) * (p.first - p1.first);
  }

  double point_set::distance(const line &l, const point &p) const {
    return fabs(point_2_line(l, p));
  }

  // IMPLEMENTACIÓN

  int point_set::find_side(const line &l, const point &p) const {
    double val = point_2_line(l, p);
    
    if (val > 0) return side::LEFT;    // -1 según tu enum
    if (val < 0) return side::RIGHT;   //  1 implícito si RIGHT es el 3er valor
    return side::CENTER;
  }

  void point_set::x_bounds(point &min_x, point &max_x) const {
    if (empty()) return;

    min_x = (*this)[0];
    max_x = (*this)[0];

    for (const auto& p : *this) {
      if (p.first < min_x.first) min_x = p;
      else if (p.first == min_x.first && p.second < min_x.second) min_x = p;

      if (p.first > max_x.first) max_x = p;
      else if (p.first == max_x.first && p.second > max_x.second) max_x = p;
    }
  }

  void point_set::write(std::ostream &os) const {
    for(const auto &p : *this) {
        os << "(" << p.first << ", " << p.second << ")\n";
    }
  }

  void point_set::write_hull(std::ostream &os) const {
    os << "Hull size: " << hull_.size() << "\n";
    for(const auto &p : hull_) {
      os << "(" << p.first << ", " << p.second << ")\n";
    }
  }

  void point_set::write_dot(std::ostream &os) const {
    os << "graph quickhull {\n";
    os << "  node [shape=point];\n";
    // 1. Dibujar todos los puntos
    for (size_t i = 0; i < size(); ++i) {
        const point &p = (*this)[i];
        os << "  p" << i << " [pos=\"" << p.first << "," << p.second << "!\"];\n";
    }
    // 2. Para dibujar el Hull como un polígono, necesitamos ordenarlos angularmente.
    // El algoritmo QuickHull nos da los vértices, pero no necesariamente en orden de dibujo
    // tras el sort() y unique() del final (que ordena por coordenada X).
    
    if (hull_.size() > 1) {
        // Copia local para ordenar para el dibujo
        std::vector<point> draw_hull = hull_;

        // Calcular centroide
        double cx = 0, cy = 0;
        for (const auto &p : draw_hull) { cx += p.first; cy += p.second; }
        cx /= draw_hull.size();
        cy /= draw_hull.size();

        // Ordenar angularmente respecto al centroide para poder trazar la línea
        std::sort(draw_hull.begin(), draw_hull.end(), [cx, cy](const point &a, const point &b) {
            return std::atan2(a.second - cy, a.first - cx) < std::atan2(b.second - cy, b.first - cx);
        });

        // Dibujar aristas del Hull
        os << "  edge [color=red, penwidth=2.0];\n"; // Hull en rojo
        for (size_t i = 0; i < draw_hull.size(); ++i) {
            point p1 = draw_hull[i];
            point p2 = draw_hull[(i + 1) % draw_hull.size()];
            
            os << "  \"h" << i << "\" [pos=\"" << p1.first << "," << p1.second << "!\", style=invis];\n";
            os << "  \"h" << (i+1)%draw_hull.size() << "\" [pos=\"" << p2.first << "," << p2.second << "!\", style=invis];\n";
            os << "  \"h" << i << "\" -- \"h" << (i+1)%draw_hull.size() << "\";\n";
        }
    }
    os << "}\n";
  }
}