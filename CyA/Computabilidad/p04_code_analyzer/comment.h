/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * 
 * @subject: CyA 25-26
 *           P04 - Expresiones regulares en C++
 * 
 * @file comment.h
 * @author Ezequiel Hernández Poleo (alu0101735399@ull.edu.es)
 * @date 2025-10-05
 * @brief It contains the Comment class declaration.
 */

#pragma once

#include <regex>

/**
 * @brief Enum class for distinguish multi and single line comments.
 * 
 */
enum class CommentType{
    SINGLE_LINE,
    MULTI_LINE,
}; 

class Comment{
 public:
  // Default constructor
  Comment() = default;
  
  // Constructors, the first from an smatch, and the second from a string
  Comment(const int start_line, const int end_line, const std::smatch& content, 
  bool is_multiline, bool is_description = false) : start_line_{start_line}, 
  end_line_{end_line}, body_{content[0]}, is_description_{is_description} {
    comment_type_ = (is_multiline) ? CommentType::MULTI_LINE : CommentType::SINGLE_LINE;
  }

  Comment(const int start_line, const int end_line, const std::string& body, 
  bool is_multiline, bool is_description = false) : start_line_{start_line}, 
  end_line_{end_line}, body_{body}, is_description_{is_description} {
    comment_type_ = (is_multiline) ? CommentType::MULTI_LINE : CommentType::SINGLE_LINE;
  }
  // ^\/\/[\w\W]*?$      REGEX Single Line Comment

  // Getters
  CommentType getCommentType() const {return comment_type_;}
  int getStartLine() const {return start_line_;}
  int getEndLine() const {return end_line_;}
  std::string getBody() const {return body_;}
  bool GetIsDescription() const {return is_description_;}

 private:
  CommentType comment_type_;
  int start_line_;
  int end_line_;
  std::string body_;
  bool is_description_;
};

std::ostream& operator<<(std::ostream& out, Comment& comment);