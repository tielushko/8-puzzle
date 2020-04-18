#include "header.h"

int main(int argc, char* argv[])
{


	Neighbours g;

	State goal(3, std::vector<int>{ 1, 2, 3, 8, 0, 4, 7, 6, 5 });
	//State start(3, std::vector<int>{ 1, 6, 2, 0, 4, 3, 7, 5, 8 });

	State start(3, std::vector<int>{1, 3, 4, 8, 0, 6, 7, 5, 2});

	std::shared_ptr<Node> node;
	Solver solver(start, goal, Solver::DEPTH_FIRST);
	if (!solver.isSolvable())
	{
		std::cout << "Puzzle state is unsolvable..!\n";
		return 0;
	}
	int count = 0;
	while (!solver.isSolved())
	{
		node = solver.GetNextNode();
		solver.ExpandNode(node, g);
		count++;
	}

	// accumulate the nodes for the solution.
	std::vector<NodePtr > solution;
	NodePtr s = node;
	do
	{
		solution.push_back(s);
		s = s->GetParent();
	} while (s != NULL);

	// print the solution.
	std::cout << "The puzle can be solved in " << solution.size() - 1 << " steps. Solution below\n";
	for (int i = (int)solution.size() - 1; i >= 0; i--)
	{
		solution[i]->GetState().print(std::cout, false);
	}
	std::cout << "\n";

	return 0;
}