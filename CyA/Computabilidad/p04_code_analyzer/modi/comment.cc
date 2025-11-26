/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * 
 * @subject: CyA 25-26
 *           P04 - Expresiones regulares en C++
 * 
 * @file comment.cc
 * @author Ezequiel Hernández Poleo (alu0101735399@ull.edu.es)
 * @date 2025-10-05
 * @brief This file contains the Comment class initialization, specifically the
 *        operator overloading.
 */

#include "comment.h"

/**
 * @brief Used to display comments, it distingish between multi line, single line
 *        and even description comment at the momment of displaying.
 * 
 * @param out 
 * @param comment 
 * @return std::ostream& 
 */
std::ostream& operator<<(std::ostream& out, Comment& comment) {
  if(comment.getCommentType() == CommentType::SINGLE_LINE) {
    out << "[Line " << comment.getStartLine() << "] " << comment.getBody();
  } else if(comment.getCommentType() == CommentType::MULTI_LINE) {
    if(comment.GetIsDescription()) {
      out << "[Line " << comment.getStartLine() << "-" << comment.getEndLine() << "] DESCRIPTION";
    } else {
      out << "[Line " << comment.getStartLine() << "-" << comment.getEndLine() << "]\n" << comment.getBody();
    }
  }
  return out;
}