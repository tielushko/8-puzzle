#include <vector>
#include <random>
#include <map>
#include <iostream>
#include <cassert>
#include <memory>
#include <algorithm>

//! A typedef of a normal integer array using std::vector for convenience
typedef std::vector<int> IntArray;

///class State
///A class to hold the state of the puzzle. 
///The state is represented by a simple one dimensional array of integers.
///The value of o represents empty slot.
class State
{
private:
	IntArray _state;
	unsigned int _rows_or_cols;

public:
	///
	explicit State(unsigned int rows_or_cols)
		: _rows_or_cols(rows_or_cols)
	{
		_state.resize(_rows_or_cols*_rows_or_cols);
		for (unsigned int i = 0; i < _state.size(); ++i)
		{
			_state[i] = i;
		}
	}

	State(unsigned int rows_or_cols, const IntArray& arr)
		: _rows_or_cols(rows_or_cols)
	{
		assert(arr.size() == _rows_or_cols * _rows_or_cols);
		_state = arr;
	}

	///copy constructor
	State(const State& other)
	{
		_rows_or_cols = other._rows_or_cols;
		_state = other._state;
	}

	///assignment operator
	State& operator = (const State& other)
	{
		if (this != &other)
		{
			_rows_or_cols = other._rows_or_cols;
			_state = other._state;
		}
		return *this;
	}

	///equal to operator. This will check item by item.
	friend bool operator == (const State& a, const State& b)
	{
		return (a._state == b._state);
	}

	///not equal to operator. This will check item by item.
	friend bool operator != (const State& a, const State& b)
	{
		return (a._state != b._state);
	}

	/// find the index of the empty slot
	inline int FindEmptyTileIndex() const
	{
		for (int i = 0; i < _state.size(); ++i)
			if (_state[i] == 0) return i;

		return (int)_state.size();
	}
	/// Randomize teh state. 
	///NOTE: Not all Randomized states are solvable. 
	///Need to implement a method to find whether a state is solvable or not.
	/*inline void Randomize()
	{
		std::random_shuffle(_state.begin(), _state.end());
	}*/

	///swap the values of the indices
	inline void SwapWithEmpty(int i0, int i1)
	{
		int tmp = _state[i1];
		_state[i1] = _state[i0];
		_state[i0] = tmp;
	}

	inline const IntArray& GetArray() const
	{
		return _state;
	}

	void SetArray(const IntArray& arr)
	{
		_state = arr;;
	}

	inline unsigned int GetNumRowsOrCols() const
	{
		return _rows_or_cols;
	}

	void print(std::ostream& str, bool flat = false) const
	{
		for (unsigned int i = 0; i < _rows_or_cols; ++i)
		{
			for (unsigned int j = 0; j < _rows_or_cols; ++j)
			{
				unsigned int index = i * _rows_or_cols + j;
				if (flat)
				{
					str << _state[index];
				}
				else
				{
					str << _state[index] << " ";
				}
			}
			if (!flat)
			{
				str << "\n";
			}
		}
		str << "\n";
	}
};

class Neighbours
{
public:
	typedef std::map<int, std::vector<int> > IndexNeighbourMap;
	IndexNeighbourMap _edges;

	Neighbours()
	{
		CreateGraphFor8Puzzle();
	}

	const std::vector<int>& GetNeighbours(int id) const
	{
		IndexNeighbourMap::const_iterator itr(_edges.find(id));
		if (itr != _edges.end()) return itr->second;
		static std::vector<int> s;
		return s;
	}

private:
	void CreateGraphFor8Puzzle()
	{
		_edges.insert(std::make_pair(0, std::vector<int>{1, 3}));
		_edges.insert(std::make_pair(1, std::vector<int>{0, 2, 4}));
		_edges.insert(std::make_pair(2, std::vector<int>{1, 5}));
		_edges.insert(std::make_pair(3, std::vector<int>{4, 0, 6}));
		_edges.insert(std::make_pair(4, std::vector<int>{3, 5, 1, 7}));
		_edges.insert(std::make_pair(5, std::vector<int>{4, 2, 8}));
		_edges.insert(std::make_pair(6, std::vector<int>{7, 3}));
		_edges.insert(std::make_pair(7, std::vector<int>{6, 8, 4}));
		_edges.insert(std::make_pair(8, std::vector<int>{7, 5}));
	}
};

class Node
{
private:
	State _state;
	std::shared_ptr<Node> _parent;
	int _depth;

public:
	Node(const State& state, std::shared_ptr<Node> parent, int depth = 0)
		: _state(state)
		, _depth(depth)
	{
		_parent = parent;
	}

	void SetParent(Node* node)
	{
		_parent.reset(node);
	}

	void SetParent(std::shared_ptr<Node> node)
	{
		_parent = node;
	}

	std::shared_ptr<Node> GetParent()
	{
		return _parent;
	}

	const std::shared_ptr<Node> GetParent() const
	{
		return _parent;
	}

	const State& GetState() const
	{
		return _state;
	}

	int GetDepth() const
	{
		return _depth;
	}

	void print(std::ostream& out, int lineNum) const
	{
		out << lineNum << " - Node { ";
		for (unsigned int i = 0; i < _state.GetArray().size(); ++i)
		{
			out << _state.GetArray()[i];
		}
		out << " | D: " << _depth;
		out << " }" << "\n";
	}
};

typedef std::shared_ptr<Node> NodePtr;

inline int GetHammingCost(const State& st)
{
	int cost = 0;
	const IntArray& state = st.GetArray();
	for (unsigned int i = 0; i < state.size(); ++i)
	{
		if (state[i] == 0) continue;
		if (state[i] != i + 1) cost += 1;
	}
	return cost;
}

inline int GetManhattanCost(const State& st)
{
	int cost = 0;
	const IntArray& state = st.GetArray();
	unsigned int rows_or_cols = st.GetNumRowsOrCols();
	for (unsigned int i = 0; i < state.size(); ++i)
	{
		int v = state[i];
		if (v == 0) continue;

		// actual index of v should be v-1
		v = v - 1;
		int gx = v % rows_or_cols;
		int gy = v / rows_or_cols;

		int x = i % rows_or_cols;
		int y = i / rows_or_cols;

		int mancost = abs(x - gx) + abs(y - gy);
		cost += mancost;

		int z = 0;
	}
	return cost;
}

class CompareFunctorForGreedyBestFirst
{
public:
	bool operator()(
		const std::shared_ptr<Node>& n1,
		const std::shared_ptr<Node>& n2) const
	{
		const State& state1 = n1->GetState();
		int cost1 = GetManhattanCost(state1) + GetHammingCost(state1);
		const State& state2 = n2->GetState();
		int cost2 = GetManhattanCost(state2) + GetHammingCost(state2);

		return cost1 < cost2;
	}
};

class CompareFunctorForAStar
{
public:
	bool operator()(
		const std::shared_ptr<Node>& n1,
		const std::shared_ptr<Node>& n2) const
	{
		const State& state1 = n1->GetState();
		int cost1 = GetManhattanCost(state1) + GetHammingCost(state1) + n1->GetDepth();
		const State& state2 = n2->GetState();
		int cost2 = GetManhattanCost(state2) + GetHammingCost(state2) + n2->GetDepth();

		return cost1 < cost2;
	}
};

inline bool isInArray(const State& state, const std::vector<std::shared_ptr<Node> >& values)
{
	unsigned int i = 0;
	for (; i < values.size(); ++i)
	{
		if (state == values[i]->GetState())
			return true;
	}
	return false;
}

class Solver
{
public:
	enum Type
	{
		DEPTH_FIRST = 0,
		BREADTH_FIRST,
		GREEDY_BEST_FIRST,
		ASTAR,
	};

	Solver(const State& start, const State& goal, Type type = Type::ASTAR)
		: _goal(goal)
		, _solved(false)
		, _type(type)
	{
		NodePtr root(new Node(start, 0, 0));
		_openlist.push_back(root);
	}

	virtual ~Solver()
	{
	}

	inline bool isSolved() const
	{
		return _solved;
	}

	inline bool isSolvable() const
	{
		///TODO
		return true;
	}

	///Returns next node in the search.
	//template<class Compare> osg::ref_ptr<Node> GetNextNode(Compare cmp)
	NodePtr GetNextNode() //or maybe this one is not good for the DFS either.
	{
		if (_openlist.empty()) return 0;
		NodePtr current;

		switch (_type)
		{
		case ASTAR:
		{
			NodeList::iterator current_itr(std::min_element(
				_openlist.begin(), 
				_openlist.end(), 
				CompareFunctorForAStar()));

			if (current_itr == _openlist.end()) return 0;

			//copy the value first to a shared pointer and then erase from the open list.
			current = *current_itr;

			// now erase from the open list.
			_openlist.erase(current_itr);
			_closedlist.push_back(current);

			break;
		}
		case GREEDY_BEST_FIRST:
		{
			NodeList::iterator current_itr(std::min_element(
				_openlist.begin(), 
				_openlist.end(),
				CompareFunctorForGreedyBestFirst()));

			if (current_itr == _openlist.end()) return 0;

			//copy the value first to a shared pointer and then erase from the open list.
			current = *current_itr;

			// now erase from the open list.
			_openlist.erase(current_itr);
			_closedlist.push_back(current);

			break;
		}
		case BREADTH_FIRST:
		{
			current = _openlist[0];
			_openlist.erase(_openlist.begin());
			_closedlist.push_back(current);

			break;
		}
		case DEPTH_FIRST:
			//current = _openlist[0];
			NodeList::iterator current_itr(_openlist.begin());
			if (current_itr == _openlist.end()) return 0;

			//copy the value first to a shared pointer and then erase from the open list.
			current = *current_itr;

			// now erase from the open list.
			_openlist.erase(current_itr);
			_closedlist.push_back(current);

			break;
		}
		return current;
	}

	// expand the graph by looking into the neighbours for the given node.
	void ExpandNode(NodePtr current, const Neighbours& graph) //good for BFS, need to think something different for DFS this expands all of the nodes, but for DFS we need left, up, right, bottom //or maybe it is good for everybody as we need all expansions. but we need queue for DFS or change the map to represent left up right bottom way of traversal
	{
		if (current->GetState() == _goal)
		{
			_solved = true;
			return;
		}

		int zero = current->GetState().FindEmptyTileIndex();
		const IntArray& neighbours = graph.GetNeighbours(zero);

		for (int next : neighbours)
		{
			State state = current->GetState();
			state.SwapWithEmpty(zero, next);

			if (!isInArray(state, _closedlist))
			{
				NodePtr n(new Node(state, current, current->GetDepth() + 1));
				_openlist.push_back(n);
				static int s_lineNum = 1;
				n->print(std::cout, s_lineNum++);
				//_closedlist.push_back(n);
			}
		}
	}

private:
	typedef std::vector<NodePtr> NodeList;
	NodeList _openlist;
	NodeList _closedlist;
	const State& _goal;
	bool _solved;
	Type _type;
};