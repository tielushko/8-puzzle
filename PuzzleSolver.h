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
   vector<pair<step,long>>adjacency;
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
      Graph();
      void printBoard(step);//done
      bool isSolved(step);//done
      int findZero(step);//done
      void swapPlaces(vector<int>&,int,int);//done
      void makeMove(step&,int);//done
      void moveLeft(step&,int);//done
      void moveUp(step&,int);//done
      void moveRight(step&,int);//done
      void moveDown(step&,int);//done
      void findMoves(step&);//done
      bool alreadyGenerated(step);//done? not tested but should work
      bool visited(step,vector<step>);//done? also not tested yet
      void DFS(vector<int>);
      void BFS(vector<int>);
      void DijkstrasAlg(vector<int>);
      int getCost(){return cost;}//done
      int getMarker(){return marker;}//done
      int whichAlgo(){return whichAlgorithm;}
      void setAlgo(int);
      int pathCost(step);
      void tracePath(step);
};

#endif