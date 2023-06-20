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
  alphabeta(state, depth, true, -INT_MAX, INT_MAX, state->player);
  //negamax(state, depth, -INT_MAX,state->player);
  //minimax(state, depth, true, state->player);
  return state->move;
}


int alphabeta(State* s, int depth, bool turn, int alpha, int beta, int player){
  State* next;
  if(s->game_state==WIN&&turn) return INT_MAX;
  if(s->game_state==WIN&&!turn) return -INT_MAX;

  if(!s->legal_actions.size()) s->get_legal_actions();

  //if(depth==0||s->game_state==WIN||s->game_state==DRAW){
  if(depth==0||!s->legal_actions.size()){
    return s->evaluate(player);
  }
  
  auto actions = s->legal_actions;
  if(turn){
    for(Move m: actions){
      next = s->next_state(m);
      next->move = m;
      int vt = alphabeta(next, depth-1, false, alpha, beta, player);
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
      int vt = alphabeta(next, depth-1, true, alpha, beta, player);   
      if(vt<beta){
        beta = vt;
        if(depth==5) s->move = next->move;
      }
      if(alpha >= beta) break;
    }
    return beta;
  }
}


int minimax(State* s, int depth, bool turn, int player){
  State* next;
  if(s->game_state==WIN&&turn) return INT_MAX;
  if(s->game_state==WIN&&!turn) return -INT_MAX;

  if(!s->legal_actions.size()) s->get_legal_actions();

  if(depth==0||s->game_state==WIN||s->game_state==DRAW){
  //if(!s->legal_actions.size()){
    return s->evaluate(player);
  }
  
  auto actions = s->legal_actions;
  if(turn){
    int val = -INT_MAX;
    for(Move m: actions){
      next = s->next_state(m);
      next->move = m;
      int vt = minimax(next, depth-1, false, player);
      if(vt>val){
        val = vt;
        if(depth==3) s->move = next->move;
      }
    }
    return val;
  }else{
    int val = INT_MAX;
    for(Move m: actions){
      next = s->next_state(m);
      next->move = m;
      int vt = minimax(next, depth-1, true, player);   
      if(vt<val){
        val = vt;
        if(depth==3) s->move = next->move;
      }
    }
    return val;
  }
}



int negamax(State* s, int depth, int gamma,int player){
  if(s->game_state==WIN&&s->player==player) return INT_MAX;
  if(s->game_state==WIN&&s->player!=player) return -INT_MAX;
  if(depth==0||s->game_state==WIN||s->game_state==DRAW){
    return s->evaluate(s->player);
  }
  if(!s->legal_actions.size()) s->get_legal_actions();
  auto actions = s->legal_actions;
  Move nxtMove;
  for(Move m: actions){
    nxtMove = m;
    int vt = -negamax(s->next_state(m), depth-1, gamma,player);
    if(vt>gamma){
       gamma = vt;
       nxtMove = m;
    }
    s->move = nxtMove;
  }
  return gamma;
}