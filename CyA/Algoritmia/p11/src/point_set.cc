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
#include <iomanip>
#include <map>

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
  // Creamos el arco ponderado necesario para el método merge de sub_tree
  double cost = euclidean_distance(a);
  CyA::weigthed_arc weighted_a = std::make_pair(cost, a);

  // Fusionamos el árbol j dentro del árbol i
  st[i].merge(st[j], weighted_a);

  // Eliminamos el árbol j del bosque, ya que ahora es parte de i.
  // Es importante usar iteradores para borrar del vector.
  st.erase(st.begin() + j);
}

void point_set::find_incident_subtrees(const forest& st, const CyA::arc &a, int& i, int& j) const {
  i = -1; 
  j = -1;

  // Recorremos todos los subárboles del bosque
  for (int k = 0; k < st.size(); ++k) {
    // Si el punto 'first' del arco está en el subárbol k
    if (st[k].contains(a.first)) {
      i = k;
    }
    // Si el punto 'second' del arco está en el subárbol k
    if (st[k].contains(a.second)) {
      j = k;
    }
    
    // Optimización: Si ya encontramos ambos, podemos salir (opcional pero eficiente)
    if (i != -1 && j != -1) break;
  }
}

double point_set::compute_cost(void) const {
  double total_cost = 0.0;
  for (const auto& arc : emst_) {
    total_cost += euclidean_distance(arc);
  }
  return total_cost;
}

// Métodos de escritura (declarados en .h pero faltaban en tu .cc original o no los copiaste)
// Si ya los tienes implementados en otro lado, ignora esto.
void point_set::write_tree(std::ostream &os) const {
  for (const auto &arc : emst_) {
    os << "(" << arc.first.first << ", " << arc.first.second << ") -> " << "(" << arc.second.first << ", " << arc.second.second << ")" << std::endl;
  }
}

void point_set::write(std::ostream &os) const {
  // Implementación genérica de escritura
  os << *this; 
}

void point_set::write_dot(std::ostream &os) const {
  os << "graph {" << std::endl;
  os << "  // Configuración global" << std::endl;
  os << "  node [shape=circle, fixedsize=true, width=0.3, style=filled, fillcolor=lightblue];" << std::endl;
  os << "  edge [color=black, penwidth=2];" << std::endl;

  // Mapa para recordar qué índice (0, 1, 2...) tiene cada punto (coordenadas)
  // Esto es necesario para escribir las conexiones como "0 -- 1"
  std::map<CyA::point, int> point_to_id;

  // 1. Escribir los nodos (Puntos)
  for (size_t i = 0; i < size(); ++i) {
    const CyA::point& p = (*this)[i];
    point_to_id[p] = i; // Guardamos su ID

    // Formato: 0 [pos="x,y!"] label="0"];
    // La '!' al final de las coordenadas fuerza a neato a respetar la posición exacta
    os << "  " << i << " [pos=\"" 
       << std::fixed << std::setprecision(2) << p.first << "," 
       << std::fixed << std::setprecision(2) << p.second << "!\""
       << ", label=\"" << i << "\"];" << std::endl;
  }

  // 2. Escribir las aristas (El árbol EMST)
  for (const CyA::arc &a : emst_) {
    // Buscamos los IDs de los puntos extremos del arco
    int id1 = point_to_id[a.first];
    int id2 = point_to_id[a.second];

    os << "  " << id1 << " -- " << id2 << ";" << std::endl;
  }

  os << "}" << std::endl;
}