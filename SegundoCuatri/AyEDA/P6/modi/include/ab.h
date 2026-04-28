/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * 
 * @subject: 
 * 
 * @file ab.h
 * @author Ezequiel Hernández Poleo (alu0101735399@ull.edu.es)
 * @date 2026-04-16
 * @brief 
 */

#pragma once

#include "nodob.h"

#include <iostream>
#include <queue>

template <class Key>
class AB {
 public: 
  virtual ~AB() {
    remove(root_);
  }

  virtual bool insertar(const Key& k) = 0;
  virtual bool buscar(const Key& k) const = 0;
  virtual bool borrar(const Key& k) = 0;

  void remove(NodoB<Key>* nodo);

  NodoB<Key>* GetRoot() {return root_;}

  void inorden() const;
  void mostrar_niveles(std::ostream& os) const;
 protected:
  void inorden_recursivo(NodoB<Key>* nodo) const;
  NodoB<Key>* root_;
};

template <class Key>
void AB<Key>::inorden() const {
  std::cout << "Recorrido Inorden:" << std::endl;
  inorden_recursivo(root_);
}

template <class Key>
void AB<Key>::inorden_recursivo(NodoB<Key>* nodo) const {
  if(nodo == NULL) {
    return;
  }
  inorden_recursivo(nodo->GetLeft());
  std::cout << "[" << nodo->GetData() << "] ";
  inorden_recursivo(nodo->GetRight());
}

template <class Key>
void AB<Key>::mostrar_niveles(std::ostream& os) const {
  if(this->root_ == nullptr) {
    os << "Árbol vacío\nNivel 0: [.]\n";
    return;
  }
  std::queue<NodoB<Key>*> cola;
  cola.push(this->root_);
  int nivel = 0;
  while (!cola.empty()) {
    int nodos_en_nivel = cola.size(); 
    os << "Nivel " << nivel << ": ";
    for (int i = 0; i < nodos_en_nivel; i++) {
      NodoB<Key>* nodo_actual = cola.front();
      cola.pop();
      if (nodo_actual != nullptr) {
        os << "[" << nodo_actual->GetData() << "] ";
        cola.push(nodo_actual->GetLeft());
        cola.push(nodo_actual->GetRight());
      } else {
        os << "[.] ";
      }
    }
    os << "\n";
    nivel++;
  }
  os << "\n";
}

template<class Key>
std::ostream& operator<<(std::ostream& os, const AB<Key>& tree) {
  tree.mostrar_niveles(os);
  return os;
}

template <class Key>
void AB<Key>::remove(NodoB<Key>* nodo) {
  if (nodo == nullptr) return;
  remove(nodo->GetLeft());
  remove(nodo->GetRight());
  delete nodo;
}