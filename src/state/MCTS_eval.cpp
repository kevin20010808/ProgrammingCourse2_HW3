
#include <cmath>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <cstdint>
#include "./state.hpp"
#include "../config.hpp"
#include "./MCTS_eval.hpp"


MCTS_node::MCTS_node(State* s){
    state = s;
    parent = nullptr;
    //pa_action; 
    results[1] = 0;
    results[0] = 0;
    results[-1] = 0;
    visit_num = 0;
    untried_acts = this->untried();
}

MCTS_node::MCTS_node(State* s, MCTS_node* pa){
    state = s;
    parent = pa;
        //pa_action = pact;
    results[1] = 0;
    results[0] = 0;
    results[-1] = 0;
    visit_num = 0;
    untried_acts = this->untried();
}

std::vector<Move> MCTS_node::untried(){
    if(!this->state->legal_actions.size()) 
        this->state->get_legal_actions();
    this->untried_acts = this->state->legal_actions;
    return this->untried_acts;
};

double MCTS_node::q(){return 1.5*this->results[1] - this->results[-1];};

double MCTS_node::n(){return this->visit_num;};

MCTS_node* MCTS_node::expand(){
    Move m = this->untried_acts.back();
    this->untried_acts.pop_back();
    State* next = this->state->next_state(m);
    next->move = m;
    MCTS_node* child = new MCTS_node(next, this);
    this->children.push_back(child);
    return child;
};

bool MCTS_node::is_terminal_node(){return this->state->is_game_over();};

double MCTS_node::rollout(int player){
    State* cur_rollout_state = this->state;
    if(!cur_rollout_state->legal_actions.size()) 
        cur_rollout_state->get_legal_actions();
    while(!cur_rollout_state->is_game_over()){
        Move m = this->rollout_policy(cur_rollout_state->legal_actions);
        cur_rollout_state = cur_rollout_state->next_state(m);
        if(!cur_rollout_state->legal_actions.size()) 
            cur_rollout_state->get_legal_actions();
    }
    
    if(cur_rollout_state->player==player){
        if(cur_rollout_state->game_state==WIN) return 1;
        else return 0;
    }
    if(cur_rollout_state->game_state==WIN) return -1;
    else return 0;
};

void MCTS_node::backpropagate(int result){
    this->visit_num++;
    this->results[result]++;
    if(this->parent) this->parent->backpropagate(result);
};

bool MCTS_node::is_fully_expanded(){return untried_acts.size()==0;};

MCTS_node* MCTS_node::best_child(double c_param=1.7){
    std::vector<double> choices_weights;
    for(auto c:this->children){
        double d = (c->q() / c->n()) + c_param * sqrt((log10(this->n()) / c->n()));
        choices_weights.push_back(d);
    }
    int idx = max_element(choices_weights.begin(),choices_weights.end())-choices_weights.begin();
    return this->children[idx];
};

Move MCTS_node::rollout_policy(std::vector<Move> possible_moves){
    return possible_moves[rand()%(possible_moves.size())];
};

MCTS_node* MCTS_node::tree_policy(){
    MCTS_node* cur = this;
    while(!cur->is_terminal_node()){
        if(!cur->is_fully_expanded()){
            return cur->expand();
        }else{
            cur = cur->best_child();
        }
    }
    return cur;
};

MCTS_node* MCTS_node::best_act(int player){
    int depth = 100000;
    while(depth--){
        MCTS_node* v = this->tree_policy();
        double reward = v->rollout(player);
        v->backpropagate(reward);
    }

    return this->best_child(1);
    
};


