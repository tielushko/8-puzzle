#include "PuzzleSolver.h"
using namespace std;

int main(){
   Graph graph;
   step step;
   step.board = {1,2,3,4,5,6,7,8,0};
   graph.BFS(step.board);
   return 0;
}