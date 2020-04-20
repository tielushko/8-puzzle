#include "PuzzleSolver.h"
#include <fstream>
#include <iomanip>
using namespace std;


int main(){    //0,1,2,4,5,3,8,7,6
   Graph graph;//1,2,3,8,0,4,7,6,5//sol
   step step;  //0,1,3,8,2,4,7,6,5
   vector<int> input;//1,3,4,8,6,2,0,7,5
   string file;
   ifstream inFile;
   int alg;
   cout << "Enter the name of the file to open: ";
   cin >> file;
   inFile.open(file);
   if(!inFile){
      cin.clear();
      cout << "Unable to open file" << endl;
      return 1;
   }
   int x;
   while(!inFile.eof()){
      inFile >> x;
      input.push_back(x);
   }
   step.board = input;//7,2,4,5,0,6,8,3,1
   cout << endl << "Your board:" << endl;
   graph.printBoard(step);
   cin.clear();
   cin.ignore(1000,'\n');
   cout << "Which algorithm?" << endl;
   cout << "1: DFS" << endl << "2: BFS" << endl << "3: Dijkstra's" << endl;
   cin >> alg;
   while(alg != 1 && alg != 2 && alg != 3){
      cin.clear();
      cin.ignore(1000,'\n');
      cout << "Not a valid input";
      cin >> alg;
   }
   if(alg == 1)
      graph.DFS(step.board);
   else if(alg == 2)
      graph.BFS(step.board);
   else if(alg == 3)
      graph.DijkstrasAlg(step.board);
   return 0;
}