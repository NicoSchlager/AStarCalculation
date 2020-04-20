#pragma once

#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <queue>
#include <stack>
#include <functional>
#include <cmath>
#include <assert.h>
using namespace std;

struct Pos {
	int x, y;
	Pos operator + (const Pos p) const { return Pos{ x + p.x, y + p.y }; }
	bool operator == (const Pos p) const { return p.x == x && p.y == y; }
	bool operator != (const Pos p) const { return !(*this == p); }
	bool operator < (const Pos p) const { return tie(x, y) < tie(p.x, p.y); }
};

struct Node {
	Pos position;
	double priority;
	int moves;
};

struct cmp {
	bool operator()(Node a, Node b) {
		if (a.priority > b.priority) return true;
		if (a.priority == b.priority && a.moves < b.moves) return true;
		return false;
	}
};