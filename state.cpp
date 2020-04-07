#include "state.h"

State::State(int rowCol) {
    currentState.resize(rowCol*rowCol);
    
    currentState[0] = 1;
    currentState[1] = 2;
    currentState[2] = 3;
    currentState[3] = 8;
    currentState[4] = 0;
    currentState[5] = 4;
    currentState[6] = 7;
    currentState[7] = 6;
    currentState[8] = 5;
}//default constructor: creates a vector of size rowCol * rowCol
State::State(int rowCol, const StateArray& state) {
    assert(state.size() == rowCol * rowCol);
    currentState = state;
} //another constructor: creates a State with not ideal state (not the goal state).

State::State(const State& copy) {
    rowCol = copy.rowCol;
    currentState = copy.currentState;
} //copy constructor

void State::printCurrentState() {
    for (int i = 0; i < currentState.size(); i++) {
        if(i % 3 == 0) 
            std::cout << "\n";
            
        std::cout << currentState.at(i) << " ";
    }
}

int State::getEmptyIndex() const{
    for (int i = 0; i < currentState.size(); i++) {
        if(currentState.at(i) == 0) //means it found an empty index
            return i;
    }
    return -1; //if the index was not found, then return -1
}

