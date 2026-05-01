/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * 
 * @subject: AyEDA - P7
 * 
 * @file avl.h
 * @author Ezequiel Hernández Poleo (alu0101735399@ull.edu.es)
 * @date 2026-04-29
 * @brief AVL tree implementation with self-balancing rotations and optional trace mode.
 */

#include "abe.h"
#include "nodoavl.h"

#include <iostream>

template <class Key>
class AVL : public ABE<Key> {
 public:
  AVL(bool trace = false) : trace_(trace) {}

  bool insertar(const Key& k) override;

  void PrintNode(std::ostream& os, NodoB<Key>* nodo) const override;
 private:
  bool trace_;

  NodoAVL<Key>* ToAVL(NodoB<Key>* nodo) const {return reinterpret_cast<NodoAVL<Key>*>(nodo);}
  void PrintTraceBeforeRotation(const std::string& rotation, NodoAVL<Key>* nodo) const;
  void PrintTraceAfterRotation() const;

  bool insertar_bal(NodoB<Key>*& nodo, const Key& k, bool& crece);
  void insert_re_balancea_izda(NodoB<Key>*& nodo, bool& crece);
  void insert_re_balancea_dcha(NodoB<Key>*& nodo, bool& crece);

  void rotacion_II(NodoB<Key>*& nodo);
  void rotacion_DD(NodoB<Key>*& nodo);
  void rotacion_ID(NodoB<Key>*& nodo);
  void rotacion_DI(NodoB<Key>*& nodo);
};

template <class Key>
bool AVL<Key>::insertar(const Key& k) {
  bool crece = false;
  return insertar_bal(this->root_, k, crece);
}

template <class Key>
bool AVL<Key>::insertar_bal(NodoB<Key>*& nodo, const Key& k, bool& crece) {
  if(nodo == nullptr) {
    nodo = new NodoAVL<Key>(k);
    crece = true;
    return true;
  }
  NodoAVL<Key>* nodo_avl = reinterpret_cast<NodoAVL<Key>*>(nodo);
  if(k == nodo_avl->data_) {
    crece = false;
    return false;
  }
  if(k < nodo_avl->data_) {
    bool insertado = insertar_bal(nodo_avl->left_, k, crece);
    if(crece) {
      insert_re_balancea_izda(nodo, crece);
    }
    return insertado;
  }
  bool insertado = insertar_bal(nodo_avl->right_, k, crece);
  if(crece) insert_re_balancea_dcha(nodo, crece);
  return insertado;
}

template <class Key>
void AVL<Key>::insert_re_balancea_izda(NodoB<Key>*& nodo, bool& crece) {
  NodoAVL<Key>* nodo_avl = ToAVL(nodo);
  switch(nodo_avl->GetBal()) {
    case -1:
      nodo_avl->SetBal(0);
      crece = false;
      break;
    case 0:
      nodo_avl->SetBal(1);
      break;
    case 1: {
      nodo_avl->SetBal(2);
      NodoAVL<Key>* nodo_izq = ToAVL(nodo_avl->left_);
      if(nodo_izq->GetBal() == 1) {
        PrintTraceBeforeRotation("II", nodo_avl);
        rotacion_II(nodo);
        PrintTraceAfterRotation();
      } else {
        PrintTraceBeforeRotation("ID", nodo_avl);
        rotacion_ID(nodo);
        PrintTraceAfterRotation();
      }
      crece = false;
      break;
    }
  }
}

template <class Key>
void AVL<Key>::insert_re_balancea_dcha(NodoB<Key>*& nodo, bool& crece) {
  NodoAVL<Key>* nodo_avl = ToAVL(nodo);
  switch(nodo_avl->GetBal()) {
    case 1:
      nodo_avl->SetBal(0);
      crece = false;
      break;
    case 0:
      nodo_avl->SetBal(-1);
      break;
    case -1: {
      nodo_avl->SetBal(-2);
      NodoAVL<Key>* nodo_der = ToAVL(nodo_avl->right_);
      if(nodo_der->GetBal() == -1) {
        PrintTraceBeforeRotation("DD", nodo_avl);
        rotacion_DD(nodo);
        PrintTraceAfterRotation();
      } else {
        PrintTraceBeforeRotation("DI", nodo_avl);
        rotacion_DI(nodo);
        PrintTraceAfterRotation();
      }
      crece = false;
      break;
    }
  }
}

template <class Key>
void AVL<Key>::rotacion_II(NodoB<Key>*& nodo) {
  NodoAVL<Key>* nodo_avl = ToAVL(nodo);
  NodoAVL<Key>* nodo1 = ToAVL(nodo_avl->left_);
  nodo_avl->left_ = nodo1->right_;
  nodo1->right_ = nodo_avl;
  if(nodo1->GetBal() == 1) {
    nodo_avl->SetBal(0);
    nodo1->SetBal(0);
  } else {
    nodo_avl->SetBal(1);
    nodo1->SetBal(-1);
  }
  nodo = nodo1;
}

template <class Key>
void AVL<Key>::rotacion_DD(NodoB<Key>*& nodo) {
  NodoAVL<Key>* nodo_avl = ToAVL(nodo);
  NodoAVL<Key>* nodo1 = ToAVL(nodo_avl->right_);
  nodo_avl->right_ = nodo1->left_;
  nodo1->left_ = nodo_avl;
  if(nodo1->GetBal() == -1) {
    nodo_avl->SetBal(0);
    nodo1->SetBal(0);
  } else {
    nodo_avl->SetBal(-1);
    nodo1->SetBal(1);
  }
  nodo = nodo1;
}

template <class Key>
void AVL<Key>::rotacion_ID(NodoB<Key>*& nodo) {
  NodoAVL<Key>* nodo_avl = ToAVL(nodo);
  NodoAVL<Key>* nodo1 = ToAVL(nodo_avl->left_);
  NodoAVL<Key>* nodo2 = ToAVL(nodo1->right_);
  nodo1->right_ = nodo2->left_;
  nodo_avl->left_ = nodo2->right_;
  nodo2->left_ = nodo1;
  nodo2->right_ = nodo_avl;
  if(nodo2->GetBal() == -1) {
    nodo1->SetBal(1);
  } else {
    nodo1->SetBal(0);
  }
  if(nodo2->GetBal() == 1) {
    nodo_avl->SetBal(-1);
  } else {
    nodo_avl->SetBal(0);
  }
  nodo2->SetBal(0);
  nodo = nodo2;
}

template <class Key>
void AVL<Key>::rotacion_DI(NodoB<Key>*& nodo) {
  NodoAVL<Key>* nodo_avl = ToAVL(nodo);
  NodoAVL<Key>* nodo1 = ToAVL(nodo_avl->right_);
  NodoAVL<Key>* nodo2 = ToAVL(nodo1->left_);
  nodo_avl->right_ = nodo2->left_;
  nodo1->left_ = nodo2->right_;
  nodo2->left_ = nodo_avl;
  nodo2->right_ = nodo1;
  if(nodo2->GetBal() == 1) {
    nodo1->SetBal(-1);
  } else {
    nodo1->SetBal(0);
  }
  if(nodo2->GetBal() == -1) {
    nodo_avl->SetBal(1);
  } else {
    nodo_avl->SetBal(0);
  }
  nodo2->SetBal(0);
  nodo = nodo2;
}

template <class Key>
void AVL<Key>::PrintTraceBeforeRotation(const std::string& rotation, NodoAVL<Key>* nodo) const {
  if(!trace_) return;
  std::cout << "Desbalanceo:\n";
  std::cout << *this;
  std::cout << "Rotación " << rotation << " en [" << nodo->GetData() << "(" << nodo->GetBal() << ")]:\n";
}

template <class Key>
void AVL<Key>::PrintTraceAfterRotation() const {
  if(!trace_) return;
  std::cout << *this;
}

template <class Key>
void AVL<Key>::PrintNode(std::ostream& os, NodoB<Key>* nodo) const {
  if(nodo == nullptr) {
    os << "[.]";
  } else {
    NodoAVL<Key>* nodo_avl = reinterpret_cast<NodoAVL<Key>*>(nodo);

    if (trace_) {
      os << "[" << nodo_avl->GetData() << "(" << nodo_avl->GetBal() << ")]";
    } else {
      os << "[" << nodo_avl->GetData() << "]";
    }
  }
}