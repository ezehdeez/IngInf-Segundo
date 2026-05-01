/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * 
 * @subject: AyEDA - P7
 * 
 * @file nodob.h
 * @author Ezequiel Hernández Poleo (alu0101735399@ull.edu.es)
 * @date 2026-04-16
 * @brief Generic binary tree node class storing data and child pointers.
 */

#pragma once

template <class Key>
class NodoB { 
 public:
  NodoB(const Key& data, NodoB* left = nullptr, NodoB* right = nullptr) : 
        data_(data), left_(left), right_(right) {}

  virtual ~NodoB() = default;

  Key GetData() {return data_;}
  NodoB* GetLeft() {return left_;}
  NodoB* GetRight() {return right_;}

  Key data_;
  NodoB* left_;
  NodoB* right_;
};