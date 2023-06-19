#pragma once
#include "../state/state.hpp"


/**
 * @brief Policy class for random policy, 
 * your policy class should have get_move method
 */
class Alphabeta{
public:
  static Move get_move(State *state, int depth);
};

int minimax(State* s, int depth, bool turn, int alpha, int beta, int player);
int alphabeta(State *state, int depth, int alpha, int beta, bool self);
int negamax(State* s, int depth, int gamma, int player);