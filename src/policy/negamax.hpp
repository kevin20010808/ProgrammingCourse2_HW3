#pragma once
#include "../state/state.hpp"


/**
 * @brief Policy class for random policy, 
 * your policy class should have get_move method
 */
class Negamax{
public:
  static Move get_move(State *state, int depth);
};

int minimax(State* s, int depth, bool turn, int alpha, int beta, int player);