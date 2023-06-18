#include <string>
#include <cstdlib>
#include <vector>
#include <utility>
#include <map>
#include "../config.hpp"
#include "./state.hpp"

class MCTS_node{
public:
    State* state; 
    MCTS_node* parent;
    //Move pa_action;
    std::vector<MCTS_node*> children;
    double visit_num = 0;
    std::map<double, double> results;
    std::vector<Move> untried_acts;
    MCTS_node(State* s);
    MCTS_node(State* s, MCTS_node* pa);

    std::vector<Move> untried();
    double q();
    double n();
    MCTS_node* expand();
    bool is_terminal_node();
    double rollout();
    void backpropagate(double result);
    bool is_fully_expanded();
    MCTS_node* best_child(double c_param);
    Move rollout_policy(std::vector<Move> possible_moves);
    MCTS_node* tree_policy();
    MCTS_node* best_act();


};