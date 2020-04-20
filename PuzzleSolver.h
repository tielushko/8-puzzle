#ifndef PUZZLE_SOLVER_H
#define PUZZLE_SOLVER_H

#include <vector>
#include <list>
#include <iostream>
#include <stack>
using namespace std;

struct step{
   int costToHere;
   long marker;
   vector<int> board;
   vector<pair<step,unsigned long>>adjacency;
};

struct edge{
   long weight;
   pair<long,long> connection;
};

class Graph{
   private:
      vector<step> steps;
      vector<edge> connections;
      vector<int> solution {1, 2, 3,
                            8, 0, 4,
                            7, 6, 5};
      vector<step> currPath;
      int cost;
      int marker;
      int whichAlgorithm;// 1=DFS 2=BFS 3=Dijkstra's
   public:
      Graph();//default constructor
      void printBoard(step);//Prints the board of inputted step
      bool isSolved(step);//Checks if step's noard matches the solution
      int findZero(step);//Finds the empty space
      void swapPlaces(vector<int>&,int,int);//switched the positions of elements on the board
      void makeMove(step&,int);//takes a move and adds it to the graph
      void moveLeft(step&,int);//checks if moving left is possible
      void moveUp(step&,int);//checks if moving up is possible
      void moveRight(step&,int);//checks if moving right is possible
      void moveDown(step&,int);//checks if moving down is possible
      void findMoves(step&);//finds and executes possible moves
      bool alreadyGenerated(step);//checks if a board is already generated
      bool visited(step,vector<step>);//checks if a board os part of the graph
      void DFS(vector<int>);
      void BFS(vector<int>);
      void DijkstrasAlg(vector<int>);
      int getCost(){return cost;}
      int getMarker(){return marker;}
      int whichAlgo(){return whichAlgorithm;}
      void setAlgo(int);
      int pathCost(step);//follows graph up to root to find cost to the step
      void tracePath(step);//follows graph to root and prints steps our in order
      int countDisplaced(step,int);//makes the heuristic for Dijksra's algorithm
};

#endif