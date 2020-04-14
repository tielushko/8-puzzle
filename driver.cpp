#include <iostream>

#include "state.h"

//using namespace Algorithms;

namespace Algorithms {
    void DFS(State initial, State goal);
    void BFS(State initial, State goal);
    void Dijkstra(State initial, State goal);
}

int main() {
    Graph graph;    
    StateArray array = {1,2,4,0,3,5,6,7,8};
    State state(ROW_COL_COUNT, array);

    std::shared_ptr<Node> node;
    Node()
    /*
    for (int i = 0; i < test.size(); i++) {
        if(i % 3 == 0) 
            std::cout << "\n";
            
        std::cout << test.at(i) << " ";
    }*/

    //using namespace Algorithms;

    //std::cout << Algorithms::a;

    return 0;
}