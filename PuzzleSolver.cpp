#include "PuzzleSolver.h"


Graph::Graph(){//default constructor
   cost = 0;
   marker = 0;
}

void Graph::printBoard(step step){//print's board
   for(unsigned int i = 0; i<step.board.size();i++){
      cout << step.board.at(i) << " ";
      if(i%3 == 2)
         cout << "\n";
   }
   cout << "\n";
}

bool Graph::isSolved(step step){//checks if the step is a solution
   if(step.board == solution)
      return true;
   return false;
}

int Graph::findZero(step step){//finds the empty space
   for(unsigned int i = 0; i<step.board.size();i++){
      if(step.board.at(i) == 0)
         return i;
   }
   return -1;
}

void Graph::swapPlaces(vector<int>& board, int empty, int toSwap){//swaps tiles
   int temp = board.at(empty);
   board.at(empty) = board.at(toSwap);
   board.at(toSwap) = temp;
}

void Graph::makeMove(step& currStep, int toSwap){//adds move to graph
   int emptySpace = findZero(currStep);
   step newStep;
   edge newEdge;  
   newEdge.weight=0;   
   newStep.board = currStep.board;
   newStep.marker = ++marker;
   swapPlaces(newStep.board,emptySpace,toSwap);
   if(whichAlgo() == 3){//finds cost of move
      //***************************************//comment out for other heuristic
      newEdge.weight = currStep.board.at(toSwap);
      //***************************************
      newEdge.weight += countDisplaced(newStep, currStep.board.at(toSwap));
      newStep.costToHere = currStep.costToHere + newEdge.weight;
   }else
      newEdge.weight = 1;  
   steps.push_back(newStep);
   newEdge.connection = make_pair(currStep.marker,newStep.marker);
   connections.push_back(newEdge);
   currStep.adjacency.push_back(make_pair(newStep,newEdge.weight));
   newStep.adjacency.push_back(make_pair(currStep,newEdge.weight));
}

void Graph::moveLeft(step& step, int zeroPos){//checks if there is a valid move left
   if(zeroPos%3 != 0)
      makeMove(step, zeroPos-1);     
}

void Graph::moveUp(step& step,int zeroPos){//checks if there is a valid move up
   if(zeroPos>=3)
      makeMove(step, zeroPos-3);  
}

void Graph::moveRight(step& step,int zeroPos){//checks if there is a valid move right
   if(zeroPos%3 != 2)
      makeMove(step, zeroPos+1);  
}

void Graph::moveDown(step& step,int zeroPos){//checks if there is a valid move down
   if(zeroPos<=5)
      makeMove(step, zeroPos+3);
}


void Graph::findMoves(step& step){//checks if each move is valid and executes
   int emptySpace = findZero(step);
   moveLeft(step,emptySpace);
   moveUp(step,emptySpace);
   moveRight(step,emptySpace);
   moveDown(step,emptySpace);
}

bool Graph::alreadyGenerated(step currStep){//Checks if board has been seen before
      for(step s : currPath)
         if(s.board == currStep.board && s.marker!=currStep.marker)
            return true;
   return false;
}

bool Graph::visited(step curr, vector<step> searched){
   if(whichAlgo() == 3){//Checks if board has been visited on path
      for(step s : searched){
         if(curr.board == s.board)
            return true;
      return false;
      }
   }else{
      for(step s : searched)
         if(curr.marker == s.marker)
            return true;
      return false;
   }
}

void Graph::setAlgo(int alg){//set which algorithm is being used
   whichAlgorithm = alg;
}

void Graph::DFS(vector<int> initBoard){//DFS algorithm
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
      findMoves(s);//generates and adds moves to stack and list
      for(unsigned int i = 0; i<s.adjacency.size();i++){
         if(!visited(s.adjacency.at(i).first,found)){
            deque.emplace_front(s.adjacency.at(i).first);
            found.push_back(s.adjacency.at(i).first);
         }
      }
      if(isSolved(s)){//prints out path and cost
         tracePath(s);
         cout << "Solved" << endl;
         printBoard(s);
         cout << "TotalCost: " << pathCost(s) << endl;
         break;
      }
   }
}
void Graph::BFS(vector<int> initBoard){//BFS algorithm
   setAlgo(2);
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
      findMoves(s);//generates and adds moves to stack and list
      for(unsigned int i = 0; i<s.adjacency.size();i++){
         if(!visited(s.adjacency.at(i).first,found)){
            deque.push_front(s.adjacency.at(i).first);
            //deque.emplace_back(s.adjacency.at(i).first);
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
void Graph::BFS(vector<int> initBoard){
   setAlgo(2);
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
      cout << "Iteration" << endl;
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
            //deque.push_front(s.adjacency.at(i).first);
            deque.emplace_back(s.adjacency.at(i).first);
            found.push_back(s.adjacency.at(i).first);
         }
      }
      if(isSolved(s)){//prints out path and cost
         tracePath(s);
         cout << "Solved" << endl;
         printBoard(s);
         cout << "TotalCost: " << pathCost(s) << endl;
         break;
      }
   }

}
void Graph::DijkstrasAlg(vector<int> initBoard){//Dijkstra's Algorithm
   setAlgo(3);
   step init;
   init.board = initBoard;
   int stepCounter = 0;
   step s;
   step lastMove;
   step smallestCost = init;
   vector<step> found;
   vector<step> toExpand;
   s.board=initBoard;
   if(isSolved(s)){
      cout << "Puzzle is already solved" << endl;
      return;
   }
   s.marker=0;
   s.costToHere = 0;
   cout << "Puzzle start." << endl;
   printBoard(s);
   found.push_back(s);
   steps.push_back(s);

   while(!isSolved(s)){
      findMoves(s);
      smallestCost.costToHere=9999999;//set init cost so high any branch can beat it
      for(pair<step,unsigned long> p : s.adjacency){
         step temp = p.first;

         if(temp.board != lastMove.board && !visited(temp,currPath)){
            temp.costToHere = pathCost(temp);

            if(temp.board == solution){
               smallestCost = temp;
               break;
            }

            if(smallestCost.costToHere >= temp.costToHere)
               smallestCost = temp;
         }
      }
      currPath.push_back(smallestCost);
      printBoard(smallestCost);
      stepCounter++;
      cout << "Current Cost: " << smallestCost.costToHere << endl;
      cout << "Current Step: " << stepCounter << endl;
      lastMove = s;
      s = smallestCost;
      cout << "******************************************" << endl << endl;
   }

   cout << "Solved" << endl;
   printBoard(s);
   setAlgo(1);
   cout << "Minimum steps: "<< pathCost(s) << endl;
   cout << "Minimum cost: " << s.costToHere << endl;
}

int Graph::pathCost(step s){//Gets the total cost of the path
   int totalCost=0;
   edge e;
   for(edge search : connections){//find the edge connecting to target step
      if(search.connection.second == s.marker){
         e=search;
         if(whichAlgo()==3)
            totalCost = s.costToHere;
         else{
            totalCost = 1;
         }
      }
   }
   if(whichAlgorithm!=3){//iterates back up to get number of steps
      while(e.connection.first!=0){
         for(edge search : connections){
            if(search.connection.second == e.connection.first){
               e = search;
               totalCost+=1;
            }
         }
      }
   }
   return totalCost;
}

void Graph::tracePath(step s){//Prints the path taken to a step
   edge e;
   step out;
   int stepCounter=1;
   vector<step> trPath;
   for(edge search : connections){//goes tp the end of the path
      if(search.connection.second == s.marker){
         e=search;
      }
   }
   while(e.connection.first!=0){//iterates up and throws it in a vector
      for(edge search : connections){
         if(search.connection.second == e.connection.first){
            if(whichAlgorithm == 3)
               trPath.push_back(currPath.at(e.connection.first-1));
            else
               trPath.push_back(steps.at(e.connection.first-1));
            e = search; 
         }
      }
   }
   for(int i=trPath.size()-1; i>=0; i--){//vector is iterated throguh backwards
      cout << "Step number: " << stepCounter << endl;//printing each board in the path
      printBoard(trPath.at(i));
      stepCounter++;
   }
}

int Graph::countDisplaced(step s, int num){//finds the heuristics for Dijkstra's
   int count = 0;
   int sum = 0;
   int solx;
   int soly;
   int calcx;
   int calcy;
   int solBoard[3][3] {1, 2, 3,
                       8, 0, 4,
                       7, 6, 5};
   int calcBoard[3][3];
   for(int i = 0; i < 3; ++i){
      for(int j = 0; j < 3; ++j){
         calcBoard[i][j] = s.board[count];
         count++;
      }
   }

   //******************************************************************
   count = 0; //comment this out for better heuristic
   for(int i = 0; i < 3; i++){//Counts number of displaced tiles
      for(int j = 0; j < 3; j++){
         if(solBoard[i][j] != calcBoard[i][j])
            if(calcBoard!=0)
               count++;
      }
   }
   sum = count;
   //******************************************************************

   //******************************************************************
   //   for(int i = 0; i < 3; i++){//Uncomment this for a better heuristic
   //     for(int j = 0; j < 3; j++){//uses how far away each displaced
   //       int comp = calcBoard[i][j];//tile is from its goal location
   //       if(comp!=0){
   //          calcx = i;
   //          calcy = j;
   //          for(int k = 0; k < 3; k++){
   //             for(int l = 0; l < 3; l++){
   //                if(solBoard[k][l] == comp){
   //                   solx = k;
   //                   soly = l;
   //                }
   //             }
   //          }
   //       }
   //       sum+=(abs(solx-calcx)+abs(soly-calcy));
   //    }     
   // }
   //*****************************************************************
   return sum;
}