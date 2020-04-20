#include "AStar.h"


AStar::AStar(const Grid _grid, const Pos _start, const Pos _goal) {
	grid = _grid;
	start = _start;
	goal = _goal;
	heuristic = manhattan;
	counts = 0;
	assert(grid.isValid(start) && grid.isValid(goal));
}

void AStar::setHeuristic(const function<double(Pos, Pos)> _H) {
	heuristic = _H;
}

void AStar::solve() {
	vector<vector<char>> curGrid(grid.getHeight(), vector<char>(grid.getWidth(), '.'));
	frontier.push(Node{ start, heuristic(start, goal), counts });
	parent[start] = start;
	cost[start] = heuristic(start, goal);
	while (!frontier.empty()) {
		counts++;
		Node cur = frontier.top();
		frontier.pop();
		updateGrid(curGrid, &cur.position, nullptr);
		if (cur.position == goal) break;
		for (Pos next : grid.neighbors(cur.position)) {
			double new_cost = cost[cur.position] + grid.getCost(cur.position, next);
			if (cost.find(next) == cost.end() || new_cost < cost[next]) {
				cost[next] = new_cost;
				frontier.push(Node{ next, new_cost + heuristic(next, goal), counts });
				parent[next] = cur.position;
				updateGrid(curGrid, nullptr, &next);
			}
		}
		gridSeq.push_back(curGrid);
	}
	gridSeq.push_back(curGrid);

	Pos cur(goal);
	while (cur != start) {
		path.push_back(cur);
		cur = parent[cur];
	}
	path.push_back(cur);
	reverse(path.begin(), path.end());
}

void AStar::drawSeq() const {
	if (gridSeq.size() == 0) {
		cout << "No solutions yet.\n";
		return;
	}
	cout << "\n Here comes the solution sequence of A*.\n";
	cout << "\'o\' stands for points marked as frontiers. \'+\' stands for points visited.\n";
	vector<vector<char>> result = grid.getGrid();
	Pos tStart{ result.size() - start.y, start.x - 1 };
	Pos tGoal{ result.size() - goal.y, goal.x - 1 };
	int count = 0;
	for (auto i : gridSeq) {
		count++;
		cout << "The " << count << " step:" << endl;


		for (size_t x = 0; x < i.size(); ++x) {
			for (size_t y = 0; y < i[x].size(); ++y) {
				if (i[x][y] != '.') {
					if(i[x][y] == 'o' && result[x][y] == '.' || i[x][y] == '+' && result[x][y] == 'o')
					result[x][y] = i[x][y];
				}
				if (x == tStart.x && y == tStart.y) {
					result[x][y] = '+';
				}
				if (x == tGoal.x && y == tGoal.y) {
					result[x][y] = '@';
				}
			}
		}
		Grid::draw(result);
	}
}

void AStar::drawPath() const {
	if (path.size() == 0) {
		cout << "No solutions yet.\n";
		return;
	}
	cout << "\n Here comes the final path.\n";
	cout << "\'#\' stands for obstacles. \'*\' stands for rough terrain. "
		<< "\'@\' stands for points on the path.\n";
	vector<vector<char>> result = grid.getGrid();
	for (Pos i : path) {
		int row = result.size() - i.y;
		int col = i.x - 1;
		result[row][col] = '@';
	}
	Grid::draw(result);
}

vector<Pos> AStar::getPath() const {
	return path;
}

int AStar::getCount() const {
	return counts;
}

double AStar::manhattan(Pos _p, Pos _goal) {
	return abs(_p.x - _goal.x) + abs(_p.y - _goal.y);
}

double AStar::euclidean(Pos _p, Pos _goal) {
	return sqrt(pow(_p.x - _goal.x, 2) + pow(_p.y - _goal.y, 2));
}

void AStar::updateGrid(vector<vector<char>>& _grid, const Pos* _cur, const Pos* _neighbors) {
	if (_cur != nullptr) {
		int row = _grid.size() - _cur->y;
		int col = _cur->x - 1;
		_grid[row][col] = '+';
	}
	if (_neighbors != nullptr) {
		int row = _grid.size() - _neighbors->y;
		int col = _neighbors->x - 1;
		_grid[row][col] = 'o';
	}
}

/*
Please pay attention that indices of a point in a graph and indices of a vertex
in a grid are different. For a point, i.e., a variable of Pos, the indices of it
are x and y in a Cartesian coordinate system with the origin located at the bottom-left
corner of the graph.

A Grid is stored in a two-dimensional array of C++ and thus a vertex is accessed by
its row and column in the grid with the origin located at the top-left corner of the grid.

The ranges of x, y and row, column are also different. For a grid with m rows and n columns,
row is from 0 to m-1 and column is from 0 to n-1 whereas x is from 1 to n with y from 1 to m.

In a word, for a point in the grid with its coordinates x and y, the corresponding vertex
in the grid is accessed by x-1 and m-y. As a user, such transformations never bother you cause
the only type of data you can enter and read is Pos. It is defined in a cartesian coordinate system
and thus straightforward for you to understand. I wrote this down in case you would read this cpp
and want to find out what I have done in this program.
*/