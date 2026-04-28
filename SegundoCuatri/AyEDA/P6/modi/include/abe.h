/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * 
 * @subject: AyEDA - P6
 * 
 * @file abe.h
 * @author Ezequiel Hernández Poleo (alu0101735399@ull.edu.es)
 * @date 2026-04-18
 * @brief 
 */

#pragma once

template <class Key>
class ABE : public AB<Key> {
 public:
  bool insertar(const Key& k) override;
  bool buscar(const Key& k) const override;
  bool borrar(const Key& k) override;

  int tam_rama(NodoB<Key>* nodo) const;
 private:
  Key extraer_hoja(NodoB<Key>*& nodo);
  void rebalancear(NodoB<Key>*& nodo);
  bool insertarRama(NodoB<Key>*& nodo, const Key& k);
  bool buscar_recursivo(NodoB<Key>* nodo, const Key& k) const;
  bool borrar_recursivo(NodoB<Key>*& nodo, const Key& k);
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
bool ABE<Key>::borrar(const Key& k) {
  return borrar_recursivo(this->root_, k);
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

template <class Key>
void ABE<Key>::rebalancear(NodoB<Key>*& nodo) {
  if (nodo == nullptr) return;
  int tam_izq = this->tam_rama(nodo->GetLeft());
  int tam_der = this->tam_rama(nodo->GetRight());
  if(tam_izq - tam_der > 1) {
    Key hoja_robada = extraer_hoja(nodo->left_);
    this->insertarRama(nodo->right_, hoja_robada);
  } else if (tam_der - tam_izq > 1) {
    Key hoja_robada = extraer_hoja(nodo->right_);
    this->insertarRama(nodo->left_, hoja_robada);
  }
}

template <class Key>
Key ABE<Key>::extraer_hoja(NodoB<Key>*& nodo) {
  if(nodo->GetLeft() == nullptr && nodo->GetRight() == nullptr) {
    Key valor = nodo->GetData();
    delete nodo;
    nodo = nullptr;
    return valor;
  }
  Key valor_extraido;
  if (this->tam_rama(nodo->GetLeft()) >= this->tam_rama(nodo->GetRight())) {
    valor_extraido = extraer_hoja(nodo->left_); 
  } else {
    valor_extraido = extraer_hoja(nodo->right_);
  }
  rebalancear(nodo); 
  return valor_extraido;
}

template <class Key>
bool ABE<Key>::borrar_recursivo(NodoB<Key>*& nodo, const Key& k) {
  if(nodo == nullptr) return false;
  bool borrado = false;
  if(nodo->GetData() == k) {
    if (nodo->GetLeft() == nullptr && nodo->GetRight() == nullptr) {
      delete nodo;
      nodo = nullptr;
      return true; 
    } else {
      Key valor_sustituto;
      if (this->tam_rama(nodo->GetLeft()) >= this->tam_rama(nodo->GetRight())) {
        valor_sustituto = extraer_hoja(nodo->left_);
      } else {
        valor_sustituto = extraer_hoja(nodo->right_);
      }
      nodo->SetData(valor_sustituto); 
      borrado = true;
    }
  } else {
    borrado = borrar_recursivo(nodo->left_, k) || borrar_recursivo(nodo->right_, k);
  }
  if (borrado && nodo != nullptr) {
    rebalancear(nodo); 
  }
  return borrado;
}