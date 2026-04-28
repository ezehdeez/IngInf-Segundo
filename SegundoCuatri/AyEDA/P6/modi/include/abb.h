/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * 
 * @subject: AyEDA - P6
 * 
 * @file abb.h 
 * @author Ezequiel Hernández Poleo (alu0101735399@ull.edu.es)
 * @date 2026-04-18
 * @brief 
 */

#pragma once

#include "nodob.h"

template <class Key>
class ABB : public AB<Key> {
 public:
  bool insertar(const Key& k) override;
  bool buscar(const Key& k) const override;
  bool borrar(const Key& k) override;
 private:
  bool InsertarRama(NodoB<Key>*& nodo, const Key& k);
  bool BuscarRama(NodoB<Key>* nodo, const Key& k) const;
};

template <class Key>
bool ABB<Key>::insertar(const Key& k) {
  return InsertarRama(this->root_, k);
}

template <class Key>
bool ABB<Key>::InsertarRama(NodoB<Key>*& nodo, const Key& k) {
  if(nodo == nullptr) {
    nodo = new NodoB<Key>(k);
    return true;
  }
  if(k == nodo->data_) {
    return false;
  }
  if(k < nodo->data_) {
    return InsertarRama(nodo->left_, k); // Si devuelve true/false, lo pasamos hacia arriba
  } else {
    return InsertarRama(nodo->right_, k);
  }
}

template <class Key>
bool ABB<Key>::buscar(const Key& k) const {
  return BuscarRama(this->root_, k);
}

template <class Key>
bool ABB<Key>::BuscarRama(NodoB<Key>* nodo, const Key& k) const {
  if(nodo == nullptr) {
    return false; 
  }
  if(k == nodo->data_) {
    return true; 
  }
  if(k < nodo->data_) {
    return BuscarRama(nodo->left_, k);
  } else {
    return BuscarRama(nodo->right_, k);
  }
}

template <class Key>
bool ABB<Key>::borrar(const Key& k) {
  std::cout << "No es posible borrar la clave " << k << " en un ABB, pruebe a crear un ABE" << std::endl;
  return false;
}