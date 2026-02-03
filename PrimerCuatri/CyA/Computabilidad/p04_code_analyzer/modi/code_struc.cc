/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * 
 * @subject: CyA 25-26
 *           P04 - Expresiones regulares en C++
 * 
 * @file code_struc.cc
 * @author Ezequiel Hernández Poleo (alu0101735399@ull.edu.es)
 * @date 2025-10-06
 * @brief This file contains the CodeStructure class inicilization, specifically
 *        the operator overloading. 
 */

#include <regex>
#include "code_struc.h"

// Regex used by FillCodeStructure()
const std::regex variable_regex(R"(^\s*(int|double)\s+(\w+)\s?((=)\s?(\d+(.\d+)?))?;$)");
const std::regex statement_regex(R"(^\s*(while|for)[\s\S]*$)");
const std::regex single_line_regex(R"(^\/\/[\w\W]*?$)");
const std::regex multi_start_regex(R"(^\/\*[\w\W]*$)");
const std::regex multi_end_regex(R"(^[\w\W]*\*\/$)");
const std::regex main_regex(R"(^int main([\s\S]*)\W*\{$)");
const std::regex class_start_regex(R"(^\s*class\s+([a-zA-Z]+)\s*\{?$)");
const std::regex class_end_regex(R"(^\s*\};$)");

/**
 * @brief Main function of this program, used to fill the code structure with
 *        regex and going through the file.
 * 
 * @param input_file 
 */
void CodeStructure::FillCodeStructure(std::ifstream& input_file) {
  std::string line;
  int line_counter = 0;
  bool first_comment = true;
  while(std::getline(input_file, line)) {
    line_counter++;
    std::smatch matches;
    if(std::regex_search(line, matches, variable_regex)) {
      AddVariable(Variable (line_counter, matches));
    } else if(std::regex_search(line, matches, statement_regex)) {
      AddStatement(Statement (line_counter, matches));
    } else if(std::regex_search(line, matches, single_line_regex)) {
      AddComment(Comment (line_counter, line_counter, matches, false));
    } else if(std::regex_search(line, matches, multi_start_regex)) {
      int start = line_counter;
      std::string comment_content = line;
      while(std::getline(input_file, line)) {
        line_counter++;
        comment_content += "\n" + line;
        if(std::regex_search(line, matches, multi_end_regex)) {
          break;
        }
      }
      AddComment(Comment (start, line_counter, comment_content, true, first_comment));
      first_comment = false;
    } else if(std::regex_search(line, matches, main_regex)) {
      setMain(true);
    } else if(std::regex_search(line, matches, class_start_regex)) {
      int start = line_counter;
      std::string class_name = matches[1];
      while(std::getline(input_file, line)) {
        line_counter++;
        if(std::regex_search(line, matches, class_end_regex)) {
          break;
        }
      }
      AddClass(Class (start, line_counter, class_name));
    }
  }
}

/**
 * @brief Used to display code info, such as comments, statements and variables.
 * 
 * @param out 
 * @param code_structure 
 * @return std::ostream& 
 */
std::ostream& operator<<(std::ostream& out, const CodeStructure code_structure) {
  out << "PROGRAM: " << code_structure.getInputFile() << std::endl;
  out << "DESCRIPTION: " << std::endl;
  if(code_structure.getComments()[0].GetIsDescription() == true) {
    out << code_structure.getComments()[0].getBody();
  }
  out << "\n\n";
  out << "VARIABLES: \n";
  for(size_t i = 0; i < code_structure.getVariables().size(); i++) {
    out << code_structure.getVariables()[i] << std::endl;
  }
  out << "\n";
  out << "STATEMENTS: \n";
  for(size_t i = 0; i < code_structure.getStatements().size(); i++) {
    out << code_structure.getStatements()[i] << std::endl;
  }
  out << "\n";
  out << "CLASSES: \n";
  for(size_t i = 0; i < code_structure.getClasses().size(); i++) {
    out << code_structure.getClasses()[i] << std::endl;
  }
  out << "\n";
  out << "MAIN: \n";
  out << ((code_structure.getHasMain()) ? "True" : "False") << std::endl;
  out << "\n";
  out << "COMMENTS: \n";
  for(size_t i = 0; i < code_structure.getComments().size(); i++) {
    out << code_structure.getComments()[i] << std::endl;
  }
  return out;
}