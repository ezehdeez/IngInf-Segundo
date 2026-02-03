/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * 
 * @subject: CyA 25-26
 *           P11 - Greedy Algorithm. EMST
 * 
 * @file forest.h
 * @author Ezequiel Hernández Poleo (alu0101735399@ull.edu.es)
 * @date 2025-12-06
 * @brief 
 */

#pragma once

#include "../include/sub_tree.h"

typedef std::vector<EMST::sub_tree> forest;
class point_set : public CyA::point_vector {
 private:
  CyA::tree emst_;
 public:
  point_set(const CyA::point_vector &points) : CyA::point_vector(points) { EMST(); }
  ~point_set(void) {
    this->clear();
    emst_.clear();
  }

  void EMST(void); 

  void write_tree(std::ostream &os) const;
  void write(std::ostream &os) const;
  void write_dot(std::ostream &os) const;

  inline const CyA::tree& get_tree(void) const { return emst_; }
  inline const CyA::point_vector& get_points(void) const { return *this; }
  inline const double get_cost(void) const { return compute_cost(); }

 private:
  void compute_arc_vector(CyA::arc_vector &av) const;
  void find_incident_subtrees(const forest& st, const CyA::arc &a, int& i, int& j) const;
  void merge_subtrees(forest& st, const CyA::arc &a, int i, int j) const;

  double compute_cost(void) const;

  double euclidean_distance(const CyA::arc& a) const;
};