#include <iostream>
#include <vector>
#include <map>
#include <random>
#include <cassert>

#define ROW_COL_COUNT 3 //for the 8-puzzle, we are going to have 3 columns and rows, if want to change the puzzle, change this number.

typedef std::vector<int> StateArray;

std::map<int, std::vector<int>> allowedSwaps = { {0, {1, 3}},
                                                 {1, {0, 2, 4}},
                                                 {2, {1, 5}},
                                                 {3, {0, 4, 6}},
                                                 {4, {1, 3, 5, 7}},
                                                 {5, {2, 4, 8}},
                                                 {6, {3, 7}},
                                                 {7, {4, 6, 8}},
                                                 {8, {5, 7}}
                                                };

/*  this class represents the particular puzzle state
*   it holds the 
*/
class State {
    private:
        StateArray currentState;
        int rowCol = ROW_COL_COUNT;
    public:
        State(int rowCol); //default constructor: creates a vector of size rowCol * rowCol -> creates the GOAL STATE
        State(int rowCol, const StateArray& state); //another constructor: creates a State with "state" being in the puzzle -> non-goal state
        State(const State& copy); //copy constructor

        //operators
        State& operator=(const State& assignedTo);
        friend bool operator==(const State& a, const State& b) {return (a.currentState == b.currentState);} 
        friend bool operator!=(const State& a, const State& b) {return (a.currentState != b.currentState);}
        //some helpers, setters, and getters,
        void printCurrentState(); //print current state function
        const StateArray& getArray() const { return currentState;}
        const int getRowCol() const { return rowCol; }
        int getEmptyIndex() const;
        void setArray(const StateArray& array) {currentState = array;}
        void swap(int indexA, int indexB); // the swap can only be performed with empty cell.
};


class Graph {

};