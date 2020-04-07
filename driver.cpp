#include <iostream>

#include "state.h"

int main() {
    State state(ROW_COL_COUNT);
    
    StateArray test = state.getArray();

    for (int i = 0; i < test.size(); i++) {
        if(i % 3 == 0) 
            std::cout << "\n";
            
        std::cout << test.at(i) << " ";
    }
    return 0;
}