/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * 
 * @subject: AyEDA - P7
 * 
 * @file abe.h
 * @author Ezequiel Hernández Poleo (alu0101735399@ull.edu.es)
 * @date 2026-04-18
 * @brief Balanced binary tree implementation with level-based insertion.
 */

#pragma once

template <class Key>
class ABE : public AB<Key> {
 public:
  bool insertar(const Key& k) override;
  bool buscar(const Key& k) const override;

  int tam_rama(NodoB<Key>* nodo) const;
 private:
  bool insertarRama(NodoB<Key>*& nodo, const Key& k);
  bool buscar_recursivo(NodoB<Key>* nodo, const Key& k) const;
};

template <class Key>
int ABE<Key>::tam_rama(NodoB<Key>* nodo) const {
  if (nodo == nullptr) return 0;
  return 1 + tam_rama(nodo->left_) + tam_rama(nodo->right_); 
}

template<class Key>
bool ABE<Key>::insertar(const Key& k) {
  return insertarRama(this->root_, k);
}

template <class Key>
bool ABE<Key>::insertarRama(NodoB<Key>*& nodo, const Key& k) {
  if(nodo == nullptr) {
    nodo = new NodoB<Key>(k);
    return true; 
  }
  if(k == nodo->data_) {
    return false; 
  }
  if(tam_rama(nodo->left_) <= tam_rama(nodo->right_)) {
    return insertarRama(nodo->left_, k);
  } else {
    return insertarRama(nodo->right_, k);
  }
}

template <class Key>
bool ABE<Key>::buscar(const Key& k) const {
  return buscar_recursivo(this->root_, k);
}

template <class Key>
bool ABE<Key>::buscar_recursivo(NodoB<Key>* nodo, const Key& k) const {
  if(nodo == nullptr) {
    return false; 
  }
  if(k == nodo->data_) {
    return true; 
  }
  return buscar_recursivo(nodo->left_, k) || buscar_recursivo(nodo->right_, k);
}