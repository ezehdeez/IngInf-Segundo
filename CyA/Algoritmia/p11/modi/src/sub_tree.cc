/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * 
 * @subject: CyA 25-26
 *           P11 - Greedy Algorithm. EMST
 * 
 * @file sub_tree.cc
 * @author Ezequiel Hernández Poleo (alu0101735399@ull.edu.es)
 * @date 2025-12-06
 * @brief 
 */

#include "../include/sub_tree.h"

#include <iomanip>
#include <cmath>

#include <algorithm>
#include <utility>

namespace EMST {
  sub_tree::sub_tree(void) : arcs_(), points_(), cost_(0) {}
  sub_tree::~sub_tree(void) {}

  void sub_tree::add_arc(const CyA::arc &a) {
    arcs_.push_back(a);
    points_.insert(a.first);
    points_.insert(a.second);
  }

  void sub_tree::add_point(const CyA::point &p) {
    points_.insert(p);
  }

  bool sub_tree::contains(const CyA::point &p) const {
    return points_.find(p) != points_.end();
  }

  void sub_tree::merge(const sub_tree &st, const CyA::weigthed_arc &a) {
    arcs_.insert(arcs_.end(), st.arcs_.begin(), st.arcs_.end());
    arcs_.push_back(a.second);
    points_.insert(st.points_.begin(), st.points_.end());
    cost_ += a.first + st.get_cost();
  }
}