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
Move Alphabeta::get_move(State* state, int depth){
  minimax(state, depth, true, -INT_MAX, INT_MAX, state->player);
  //negamax(state, depth, -INT_MAX);
  //alphabeta(state, depth, -INT_MAX, INT_MAX, true);
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
        if(depth==3) s->move = next->move;
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
        if(depth==3) s->move = next->move;
      }
      if(alpha >= beta) break;
    }
    return beta;
  }
}

int alphabeta(State *state, int depth, int alpha, int beta, bool self){

    if(depth==0){
        if(self) return state->evaluate(state->player);
        else return state->evaluate(1-state->player);
    }
    State *curS = state;
    Move nxtMove;
    // Maximizing
    if(self){
        if(!state->legal_actions.size()) state->get_legal_actions();
        for(auto it: state->legal_actions){
            int val = alphabeta(curS->next_state(it), depth-1, alpha, beta, false);
            if(val>alpha){
                alpha = val;
                nxtMove = it;
            }
            state->move = nxtMove;
            if(alpha>=beta) break;
        }
        return alpha;       
    }
    // Minimizing
    else{
        if(!state->legal_actions.size()) state->get_legal_actions();
        for(auto it: state->legal_actions){
            int val = alphabeta(curS->next_state(it), depth-1, alpha, beta, true);
            if(val<beta){
                beta = val;
                nxtMove = it;
            }
            state->move = nxtMove;
            if(alpha>=beta) break;
        }
        return beta; 
    }
}

int negamax(State* s, int depth, int gamma){
  if(depth==0||s->game_state==WIN||s->game_state==DRAW){
    return s->evaluate(s->player);
  }
  if(!s->legal_actions.size()) s->get_legal_actions();
  auto actions = s->legal_actions;
  Move nxtMove;
  for(Move m: actions){
    nxtMove = m;
    int vt = -negamax(s->next_state(m), depth-1, gamma);
    if(vt>gamma){
       gamma = vt;
       nxtMove = m;
    }
    s->move = nxtMove;
  }
  return gamma;
}