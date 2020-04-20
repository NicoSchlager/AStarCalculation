#pragma once
#include "Math.h"
class Grid {
public:
	Grid();
	Grid(int _h, int _w, double _roughTerrainCost = 5, double _diagCost = 1.4);
	void setObstacle(const Pos _tl, const Pos _br);
	void clearObstacle();
	void setRoughTerrain(const Pos _tl, const Pos _br);
	void clearRoughTerrain();
	void setRoughTerrainCost(const double _cost);
	void setDiagCost(const double _cost);
	void enableDiagMove(const bool _flag);
	int getHeight() const;
	int getWidth() const;
	vector<Pos> neighbors(const Pos _p) const;
	vector<vector<char>> getGrid() const;
	double getCost(const Pos _from, const Pos _to) const;
	bool isValid(const Pos _p) const;
	void draw() const;
	static void draw(const vector<vector<char>>& _grid);

private:
	int height, width;
	double roughTerrainCost;
	double diagCost;
	set<Pos> obstacle;
	set<Pos> roughTerrain;
	int dir;
	static vector<Pos> DIRS;
};