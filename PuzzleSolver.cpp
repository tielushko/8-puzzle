#include "PuzzleSolver.h"


Graph::Graph(){
   cost = 0;
   marker = 0;
}

void Graph::printBoard(step step){
   for(unsigned int i = 0; i<step.board.size();i++){
      cout << step.board.at(i) << " ";
      if(i%3 == 2)
         cout << "\n";
   }
   cout << "\n";
}

bool Graph::isSolved(step step){
   if(step.board == solution)
      return true;
   return false;
}

int Graph::findZero(step step){
   for(unsigned int i = 0; i<step.board.size();i++){
      if(step.board.at(i) == 0)
         return i;
   }
   return -1;
}

void Graph::swapPlaces(vector<int>& board, int empty, int toSwap){
   int temp = board.at(empty);
   board.at(empty) = board.at(toSwap);
   board.at(toSwap) = temp;
}

void Graph::makeMove(step& currStep, int toSwap){
   int emptySpace = findZero(currStep);
   step newStep;
   edge newEdge;
   if(whichAlgo() == 3)
      newEdge.weight = currStep.board.at(toSwap);
   else
      newEdge.weight = 1;       
   newStep.board = currStep.board;
   newStep.marker = ++marker;
   swapPlaces(newStep.board,emptySpace,toSwap);
   steps.push_back(newStep);
   newEdge.connection = make_pair(currStep.marker,newStep.marker);
   connections.push_back(newEdge);
   currStep.adjacency.push_back(make_pair(newStep,newEdge.weight));
   newStep.adjacency.push_back(make_pair(currStep,newEdge.weight));
}

void Graph::moveLeft(step& step, int zeroPos){
   if(zeroPos%3 != 0)
      makeMove(step, zeroPos-1);     
}

void Graph::moveUp(step& step,int zeroPos){
   if(zeroPos>=3)
      makeMove(step, zeroPos-3);  
}

void Graph::moveRight(step& step,int zeroPos){
   if(zeroPos%3 != 2)
      makeMove(step, zeroPos+1);  
}

void Graph::moveDown(step& step,int zeroPos){
   if(zeroPos<=5)
      makeMove(step, zeroPos+3);
}


void Graph::findMoves(step& step){
   int emptySpace = findZero(step);
   moveLeft(step,emptySpace);
   moveUp(step,emptySpace);
   moveRight(step,emptySpace);
   moveDown(step,emptySpace);
}

bool Graph::alreadyGenerated(step currStep){
   if(whichAlgo() == 1)
      for(step s : currPath)//For DFS
         if(s.board == currStep.board && s.marker!=currStep.marker)
            return true;
   else if(whichAlgo() == 2)//For BFS
      for(step s : steps)
         if(s.board == currStep.board && s.marker!=currStep.marker)
            return true;
   else
      return false;
   return false;
}

bool Graph::visited(step curr, vector<step> searched){
   for(step s : searched)
      if(curr.marker == s.marker)
         return true;
   return false;
}

void Graph::setAlgo(int alg){
   whichAlgorithm = alg;
}

void Graph::DFS(vector<int> initBoard){
   setAlgo(1);
   deque <step> deque;
   vector <step> found;
   step init;
   init.board = initBoard;
   init.marker = 0;
   cout << "Puzzle start." << endl;
   printBoard(init);

   if(isSolved(init)){
      cout << "Puzzle is already solved" << endl;
      return;
   }
   found.push_back(init);
   currPath.push_back(init);
   deque.emplace_front(init);
   
   while(!deque.empty()){
      step s = deque.front();
      deque.pop_front();
      while(alreadyGenerated(s)){
         s = deque.front();
         deque.pop_front();
      }
      if(s.marker!=0){
         currPath.push_back(s);
         s.costToHere = currPath.size()-1;
      }
      findMoves(s);
      for(unsigned int i = 0; i<s.adjacency.size();i++){
         if(!visited(s.adjacency.at(i).first,found)){
            deque.emplace_back(s.adjacency.at(i).first);
            found.push_back(s.adjacency.at(i).first);
         }
      }
      if(isSolved(s)){
         tracePath(s);
         cout << "Solved" << endl;
         printBoard(s);
         cout << "TotalCost: " << pathCost(s) << endl;
         break;
      }
   }
}
void Graph::BFS(vector<int> initBoard){}
void Graph::DijkstrasAlg(vector<int> initBoard){}

int Graph::pathCost(step s){
   int totalCost=1;
   edge e;
   for(edge search : connections){
      if(search.connection.second == s.marker)
         e=search;
   }
   while(e.connection.first!=0){
      for(edge search : connections){
         if(search.connection.second == e.connection.first){
            e = search;
            totalCost+=1;
         }
      }
   }
   return totalCost;
}

void Graph::tracePath(step s){
   edge e;
   step out;
   int stepCounter=1;
   vector<step> trPath;
   for(edge search : connections){
      if(search.connection.second == s.marker){
         e=search;
      }
   }
   while(e.connection.first!=0){
      for(edge search : connections){
         if(search.connection.second == e.connection.first){
            trPath.push_back(steps.at(e.connection.first-1));
            e = search; 
         }
      }
   }
   for(int i=trPath.size()-1; i>=0; i--){
      cout << "Step number: " << stepCounter << endl;
      printBoard(trPath.at(i));
      stepCounter++;
   }
}