#include <cstdlib>
#include <iostream>
#include <fstream>
#include "../state/state.hpp"
#include "./alphabeta.hpp"

#define INT_MAX 2147483647
/**
 * @brief Randomly get a legal action
 * 
 * @param state Now state
 * @param depth You may need this for other policy
 * @return Move 
 */
Move Random2::get_move(State* state, int depth){
  minimax(state, depth, true, -INT_MAX, INT_MAX, state->player);
  return state->move;
}


int minimax(State* s, int depth, bool turn, int alpha, int beta, int player){
  State* next;
  if(depth==0||s->game_state==WIN||s->game_state==DRAW){
    return s->evaluate(player);
  }
  if(!s->legal_actions.size()) s->get_legal_actions();
  auto actions = s->legal_actions;
  if(turn){
    for(Move m: actions){
      next = s->next_state(m);
      next->move = m;
      int vt = minimax(next, depth-1, false, alpha, beta, player);
      if(vt>alpha){
        alpha = vt;
        if(depth==5) s->move = next->move;
      }
      if(alpha >= beta) break;
    }
    return alpha;
  }else{
    for(Move m: actions){
      next = s->next_state(m);
      next->move = m;
      int vt = minimax(next, depth-1, true, alpha, beta, player);   
      if(vt<beta){
        beta = vt;
        if(depth==5) s->move = next->move;
      }
      if(alpha >= beta) break;
    }
    return beta;
  }
}