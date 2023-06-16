#include <cstdlib>
#include <queue>

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
Move Random2::get_move(State *state, int depth){
  if(!state->legal_actions.size())
    state->get_legal_actions();
  
  auto actions = state->legal_actions;
  Move _move;
  int alpha_score = -INT_MAX;
  //int beta_score = INT_MAX;
  std::queue<Move> q;
  for(Move m: actions) q.push(m);
  
  
  while(!q.empty()){
    Move act  = q.front();
    q.pop();
    State* next = state->next_state(act);
    next->evaluate();
    if(next->score[next->player]>alpha_score){
      alpha_score = next->score[next->player];
      _move = act;
      //next->get_legal_actions();
      //for(Move m: next->legal_actions) q.push(m);
      
    }

  }
  
  return _move;
  
  //int k=depth;
  // for(int i=0;i<depth;i++) k=rand()/k;
  //return actions[k%actions.size()];
  //return actions[(rand()+depth)%actions.size()];
}