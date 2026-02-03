/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * 
 * @subject: CyA 25-26
 *           P08 - Gramáticas en Forma Normal de Chomsky
 * 
 * @file grammar.cc
 * @author Ezequiel Hernández Poleo (alu0101735399@ull.edu.es)
 * @date 2025-10-30
 * @brief Grammar class declaration
 */

#include <cassert>
#include <stack>
#include <set>

#include "../include/grammar.h"

/**
 * @brief 
 * 
 * @return bool 
 */
bool Grammar::NoEmptyProduction() {
  for(auto production : productions_) {
    if(production.second == "&") return false;
  }
  return true;
}

/**
 * @brief 
 * 
 * @return bool 
 */
bool Grammar::NoUnitProduction() {
  for(auto production : productions_) {
    if(production.second.size() == 1 && !alphabet_.CheckSymbol(production.second[0])) return false;
  }
  return true;
}

/**
 * @brief 
 * 
 * @return bool 
 */
bool Grammar::NoEmptyORUnitProductions() {
  for(auto production : productions_) {
    if((production.second.size() == 1 && !alphabet_.CheckSymbol(production.second[0])) || production.second == "&") return false;
  }
  return true;
}

/**
 * @brief CNF Algorithm implemented and separated in 2 different stages, the first
 *        one which creates a C[] production for every symbol used in the production
 *        and substitute the appearances of those symbols with C[] production.
 *        And the second stage which uses a stack to constantly merge the very 
 *        last 2 non terminal symbols and substitute them with a D[] production.
 *        The stack implementation could not be the best one, but a stack was
 *        the first data structure that came into my head when I saw how the non
 *        terminal symbols were being merged from the right to the left.
 * 
 * @return Grammar 
 */
Grammar Grammar::ChomskyNormalForm() {
  assert(!NoEmptyORUnitProductions());
  Grammar grammar{*this};
  std::set<NTSymbol> cnf_non_terminal_symbols = non_terminal_symbols_;
  std::multimap<NTSymbol, std::string> productions = grammar.getProductions();
  std::multimap<NTSymbol, std::string> cnf_productions = productions;

  // Stage 1
  for(auto production : productions_) {
    if(production.second.size() >= 2) {
      for(char symbol : production.second) {
        if(islower(symbol)) {
          std::string new_nt_symbol = "C" + std::string(1, symbol);
          bool exists = false;
          for(auto production_check : cnf_productions) {
            if(production_check.first == new_nt_symbol) {
              exists = true;
              break;
            }
          }
          if(!exists) {
            cnf_productions.insert({new_nt_symbol, std::string(1, symbol)});
            non_terminal_symbols_.insert(new_nt_symbol);
          }
        }
      }
    }
  }
  // Terminal symbols being replaced with their corresponding non terminal symbol
  for(std::pair<const std::string, std::string>& production : cnf_productions) {
    std::string produced = production.second;
    if(produced.size() >= 2) {
      std::string new_produced;
      for(char symbol : produced) {
        if(islower(symbol)) {
          std::string non_terminal = "C" + std::string(1, symbol);
          new_produced += non_terminal;
        } else {
          new_produced += std::string(1, symbol);
        }
      }
      production.second = new_produced;
    }
  }
  // Stage 2
  std::multimap<NTSymbol, std::string> cnf_productions_copy = cnf_productions;
  cnf_productions.clear();
  int counter = 1;
  for(std::pair<const std::string, std::string>& production : cnf_productions_copy) {
    if(production.second.size() >= 3) {
      std::string new_produced;
      std::stack<std::string> stack;
      for(size_t i = 0; i < production.second.size(); i++) {
        std::string non_terminal_symbol_to_stack;
        if(i + 1 < production.second.size() && islower(production.second[i + 1])) {
            non_terminal_symbol_to_stack = std::string(1, production.second[i]) + std::string(1, production.second[i + 1]);
            i++;
        } else {
          non_terminal_symbol_to_stack = std::string(1, production.second[i]);
        }
        stack.push(non_terminal_symbol_to_stack);
      }
      while(stack.size() > 1) {
        if(stack.size() == 2) {
          std::string last_prod = stack.top();
          stack.pop();
          last_prod = stack.top() + last_prod;
          cnf_productions.insert({production.first, last_prod});
          continue;
        }       
        std::string new_producer = "D" + std::to_string(counter);
        std::string new_produced, aux;
        aux = stack.top();
        stack.pop();
        new_produced = stack.top() + aux;
        stack.pop();
        bool exists = false;
        for(auto production_check : cnf_productions) {
          if(production_check.second == new_produced) {
            exists = true;
            new_producer = production_check.first;
            break;
          }
        }
        if(!exists) {
          counter++;
          cnf_productions.insert({new_producer, new_produced});
          cnf_non_terminal_symbols.insert(new_producer);
        }
        stack.push(new_producer);
      }
    } else {
      cnf_productions.insert(production);
    }
  }
  Grammar cnf_grammar(alphabet_, cnf_non_terminal_symbols, start_symbol_, cnf_productions);
  return cnf_grammar;
}

/**
 * @brief << Operator overloading
 * 
 * @param out 
 * @param grammar 
 * @return std::ostream& 
 */
std::ostream& operator<<(std::ostream& out, const Grammar& grammar) {
  out << "Alphabet: " << grammar.getAlphabet() << std::endl;
  out << "Non terminal symbols: ";
  for(NTSymbol symbol : grammar.getNonTerminalSymbols()) {
    out << symbol << " ";
  }
  out << std::endl;
  out << "Starter symbol: " << grammar.getStartSymbol() << std::endl;
  out << "Productions: " << std::endl;
  for(auto production : grammar.getProductions()) {
    out << "\t" << production.first << " -> " << production.second << std::endl;
  }
  return out;
}

std::set<NTSymbol> Grammar::GeneratingNonTerminal() const {
  std::set<NTSymbol> generating_non_terminal;
  bool changes = true;
  while(changes) {
    changes = false;
    for(auto production : productions_) {
      if(generating_non_terminal.count(production.first) == 0) {
        bool full_non_terminal = true;
        for(char c : production.second) {
          if(islower(c)) {
            continue;
          }
          std::string symbol(1, c);
          if(generating_non_terminal.count(symbol) == 0) {
            full_non_terminal = false;
            break;
          }
        }
        if(full_non_terminal) {
          generating_non_terminal.insert(production.first);
          changes = true;
        } 
      }
    }
  }
  return generating_non_terminal;
}