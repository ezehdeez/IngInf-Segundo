/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * 
 * @subject: CyA 25-26
 *           P11 - Greedy Algorithm. EMST
 * 
 * @file forest.cc
 * @author Ezequiel Hernández Poleo (alu0101735399@ull.edu.es)
 * @date 2025-12-06
 * @brief 
 */

#include "../include/point_set.h"

#include <algorithm>

void point_set::EMST(void) {
  CyA::arc_vector av;
  compute_arc_vector(av);
  forest st;
  for (const CyA::point &p : *this) {
    EMST::sub_tree s;
    s.add_point(p);
    st.push_back(s);
  }
  for (const CyA::weigthed_arc &a : av) {
    int i, j;
    find_incident_subtrees(st, a.second, i, j);
    if (i != j) {
      merge_subtrees(st, a.second, i, j);
    }
  }
  emst_ = st[0].get_arcs();
}

void point_set::compute_arc_vector(CyA::arc_vector &av) const {
  av.clear();
  const int n = size();
  for (int i = 0; i < n - 1; ++i) {
    const CyA::point &p_i = (*this)[i];
    for (int j = i + 1; j < n; ++j) {
      const CyA::point &p_j = (*this)[j];
      const double dist = euclidean_distance(std::make_pair(p_i, p_j));
      av.push_back(std::make_pair(dist, std::make_pair(p_i, p_j)));
    }
  }
  std::sort(av.begin(), av.end());
}

double point_set::euclidean_distance(const CyA::arc& a) const {
  return hypot(a.first.first - a.second.first, a.first.second - a.second.second);
}

void point_set::merge_subtrees(forest& st, const CyA::arc &a, int i, int j) const { 
  // TODO: merge_subtrees
}

void point_set::find_incident_subtrees(const forest& st, const CyA::arc &a, int& i, int& j) const {
  // TODO: find_incident_subtrees
}

double point_set::compute_cost(void) const {
  // TODO compute_cost
}