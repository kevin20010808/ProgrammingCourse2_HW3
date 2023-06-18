#include <cstdlib>

#include "../state/state.hpp"
#include "./MCTS.hpp"
//#include "../state/MCTS_eval.hpp"
#include "../state/MCTS_eval.cpp"

/**
 * @brief Randomly get a legal action
 * 
 * @param state Now state
 * @param depth You may need this for other policy
 * @return Move 
 */
Move MCTS::get_move(State *state){
    MCTS_node*  root = new MCTS_node(state);
    MCTS_node* selected_node = root->best_act();
    return selected_node->state->move;
    //return actions[(rand()+depth)%actions.size()];
}