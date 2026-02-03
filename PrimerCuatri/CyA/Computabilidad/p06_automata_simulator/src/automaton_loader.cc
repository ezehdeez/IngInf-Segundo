/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * 
 * @subject: 
 * 
 * @file automaton_loader.cc
 * @author Ezequiel Hernández Poleo (alu0101735399@ull.edu.es)
 * @date 2025-10-17
 * @brief Automaton Loader inicialization that contains the main method of it,
 *        Loader.
 */

#include <map>
#include <fstream>
#include <string>
#include <sstream>

#include "../lib/automaton_loader.h"
#include "../lib/state.h"

/**
 * @brief This method uses string stream to extract data from the .fa file. In 
 *        the while loop for every iteration it takes the amount of transitions
 *        the line has and make a state for each line.
 * 
 * @param file_name 
 * @return AutomatonLoader::AutomatonData 
 */
AutomatonLoader::AutomatonData AutomatonLoader::Loader(const std::string& file_name) {
  std::ifstream input_file{file_name};
  std::string line;
  std::map<int, State> states;
  // Alphabet made of the first line
  getline(input_file, line);
  Alphabet alphabet(line);
  // num_states taken from the second line
  getline(input_file, line);
  int num_states = stoi(line);
  // starter_state taken from the third line
  getline(input_file, line);
  int starter_state = stoi(line);
  // State maker and insertion
  while(getline(input_file, line)) {
    std::istringstream iss(line);
    int state_name, is_aceptation, num_transitions;
    iss >> state_name >> is_aceptation >> num_transitions;
    State state(state_name, is_aceptation, num_transitions);
    // Transition maker and insertion
    for(int i = 0; i < num_transitions; ++i) {
      char symbol;
      int destination;
      iss >> symbol >> destination;
      state.InsertTransition(symbol, destination);
    }
    states.insert({state_name, state});
  }
  return AutomatonData(states, starter_state, num_states, alphabet);
}