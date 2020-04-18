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

State& State::operator=(const State& assignedTo) {
    rowCol = assignedTo.rowCol;
    currentState = assignedTo.currentState;

    return *this;
}

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


//graph class implementation

Graph::Graph() { //valuing the priority in which the left up right bottom is implemented
    graph.insert(std::make_pair(0, std::vector<int>{1,3}));
    graph.insert(std::make_pair(1, std::vector<int>{0,2,4}));
    graph.insert(std::make_pair(2, std::vector<int>{1,5}));
    graph.insert(std::make_pair(3, std::vector<int>{0,4,6}));
    graph.insert(std::make_pair(4, std::vector<int>{3,1,5,7}));
    graph.insert(std::make_pair(5, std::vector<int>{4,2,8}));
    graph.insert(std::make_pair(6, std::vector<int>{3,7}));
    graph.insert(std::make_pair(7, std::vector<int>{6,4,8}));
    graph.insert(std::make_pair(8, std::vector<int>{7,5}));
}

const std::vector<int>& Graph::getNeighbors(int index) const {
    if (index < ((ROW_COL_COUNT/ROW_COL_COUNT) - 1) || index > ((ROW_COL_COUNT*ROW_COL_COUNT)-1)) //out of bounds.
        throw "Incorrect index chosen for neighbors";
    
    Map::const_iterator iter = graph.find(index);

    return iter->second;
}

bool inClosedList(State& toCheck, std::vector<std::shared_ptr<Node>>& closedList) {
    for (int i = 0; i < closedList.size(); i++) {
        if (toCheck == closedList.at(i)->getState())
            return true;
    }
    return false;
}



