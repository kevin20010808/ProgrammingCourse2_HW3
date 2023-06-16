#pragma once
#include "../state/state.hpp"


/**
 * @brief Policy class for random policy, 
 * your policy class should have get_move method
 */
class Random2{
public:
  static Move get_move(State *state, int depth);
};

int minimax(State* s, int depth, int player, int alpha, int beta);