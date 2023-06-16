#include <cstdlib>
#include <iostream>
#include <fstream>
#include "../state/state.hpp"
#include "./random2.hpp"

#define INT_MAX 2147483647
/**
 * @brief Randomly get a legal action
 * 
 * @param state Now state
 * @param depth You may need this for other policy
 * @return Move 
 */
Move Random2::get_move(State* state, int depth){
  minimax(state, depth, state->player,-INT_MAX, INT_MAX);
  return state->move;
}


int minimax(State* s, int depth, int player, int alpha, int beta){
  if(depth==0){
    return s->evaluate();
  }
  State* next;
  if(player){
    if(!s->legal_actions.size()) s->get_legal_actions();
    auto actions = s->legal_actions;
    for(Move m: actions){
      next = s->next_state(m);
      next->move = m;
      int vt = minimax(next, depth-1, 0, alpha, beta);
      if(vt>alpha){
        alpha = vt;
        if(depth==6)
          s->move = next->move;
      }
      if(alpha >= beta) break;
    }
    return alpha;
  }else{
    if(!s->legal_actions.size()) s->get_legal_actions();
    auto actions = s->legal_actions;
    for(Move m: actions){
      next = s->next_state(m);
      next->move = m;
      int vt = minimax(next, depth-1, 1, alpha, beta);   
      if(vt<beta){
        beta = vt;
        if(depth==6)
          s->move = next->move;
      }
      if(alpha >= beta) break;
    }
    return beta;
  }
}