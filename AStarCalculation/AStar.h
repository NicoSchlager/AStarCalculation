#pragma once

#include "Math.h"
#include "Grid.h"


class AStar {
public:
	AStar() {};
	AStar(const Grid _grid, const Pos _start, const Pos _goal);
	void setHeuristic(const function<double(Pos, Pos)> _H);
	void solve();
	void drawSeq() const;
	void drawPath() const;
	vector<Pos> getPath() const;
	int getCount() const;

private:
	Grid grid;
	Pos start, goal;
	int counts;
	priority_queue<Node, vector<Node>, cmp> frontier;
	vector<Pos> path;
	vector<vector<vector<char>>> gridSeq;
	map<Pos, Pos> parent;
	map<Pos, double> cost;
	function<double(Pos, Pos)> heuristic;
	static double manhattan(Pos _p, Pos _goal);
	static double euclidean(Pos _p, Pos _goal);
	static void updateGrid(vector<vector<char>>& _grid, const Pos* _cur, const Pos* _neighbors);
};

/*
For a grid with m rows and n colums, the indices of a point, i.e., a variable of data type Pos, 
are from 1 to n and from 1 to m resectively.
*/