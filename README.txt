In order to compile, place the file with the board in this folder.
In the terminal which is set to this file, use the command "g++ -std=c++17 -Wall *.cpp" to compile
and run a.out or a.exe depending on which operating system you are on.

|********|
|**Note**|
|********|

The Dijkstra algorithm is running the heuristic that was given to us on the
Group_projectS20 file, but when I was making this it wasn't working. I think that 
comes from using the number of the tile as a value. This makes it so the higher 
valued tiles won't be moved because there are only 8 tiles to be displaced.
I included another heuristic measurement that is based on the distance each tile is
away from its goal location. To use it, open PuzzleSolver.cpp, comment out line 49,
comment out lines 337 to 345, and uncomment lines 349 to 366.