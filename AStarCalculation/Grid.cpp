#include "Grid.h"

vector<Pos> Grid::DIRS = { Pos{1,0}, Pos{-1,0}, Pos{0,1}, Pos{0,-1},
						Pos{1,1}, Pos{1,-1}, Pos{-1,-1}, Pos{-1,1} };

Grid::Grid() {
	height = 15, width = 15;
	roughTerrainCost = 5, diagCost = 1.4;
	dir = 4;
	setObstacle({ 3,5 }, { 6,3 });
	setRoughTerrain({ 9,12 }, { 11,4 });
}

Grid::Grid(int _h, int _w, double _roughTerrainCost, double _diagCost) {
	height = _h, width = _w;
	roughTerrainCost = _roughTerrainCost;
	diagCost = _diagCost;
	dir = 4;
}

void Grid::setObstacle(const Pos _tl, const Pos _br) {
	for (int i = _tl.x; i <= _br.x; ++i)
		for (int j = _br.y; j <= _tl.y; ++j) {
			obstacle.emplace(Pos{ i, j });
		}
}

void Grid::clearObstacle() {
	obstacle.clear();
}

void Grid::setRoughTerrain(const Pos _tl, const Pos _br) {
	for (int i = _tl.x; i <= _br.x; ++i)
		for (int j = _br.y; j <= _tl.y; ++j) {
			roughTerrain.emplace(Pos{ i, j });
		}
}

void Grid::clearRoughTerrain() {
	roughTerrain.clear();
}

void Grid::setRoughTerrainCost(const double _cost) {
	roughTerrainCost = _cost;
}

void Grid::setDiagCost(const double _cost) {
	diagCost = _cost;
}

void Grid::enableDiagMove(const bool _flag) {
	if (_flag) dir = 8;
	else dir = 4;
}

int Grid::getHeight() const {
	return height;
}

int Grid::getWidth() const {
	return width;
}

vector<Pos> Grid::neighbors(const Pos _p) const {
	vector<Pos> result;
	for (int i = 0; i < dir; ++i) {
		Pos p = _p + DIRS[i];
		if (isValid(p)) result.push_back(p);
	}
	return result;
}

vector<vector<char>> Grid::getGrid() const {
	int x, y;
	vector<vector<char>> result(height, vector<char>(width));
	for (int i = 0; i < height; ++i)
		for (int j = 0; j < width; ++j) {
			x = j + 1;
			y = height - i;
			Pos p{ x,y };
			if (obstacle.find(p) != obstacle.end()) result[i][j] = '#';
			else if (roughTerrain.find(p) != roughTerrain.end()) result[i][j] = '*';
			else result[i][j] = '.';
		}
	return result;
}

double Grid::getCost(const Pos _from, const Pos _to) const {
	if (roughTerrain.count(_from) != 0 || roughTerrain.count(_to) != 0)
		return roughTerrainCost;
	return 1.0;
}

bool Grid::isValid(const Pos _p) const {
	if (_p.x <= 0 || _p.x > width || _p.y <= 0 || _p.y > height || obstacle.count(_p) != 0)
		return false;
	return true;
}

void Grid::draw() const {
	cout << "\n This is the original grid. \n";
	cout << "\'#\' stands for obstacles. \'*\' stands for rough terrain. "
		<< "\'.\' stands for flat terrain. \n";
	draw(getGrid());
}

void Grid::draw(const vector<vector<char>>& _grid) {

	if (_grid.size() == 0 || _grid[0].size() == 0) return;
	int height = _grid.size(), width = _grid[0].size();
	for (int i = 0; i < height; ++i) {
		cout << endl << "\t";
		for (int j = 0; j < width; ++j) cout << _grid[i][j] << " ";
	}
	cout << endl << endl;
}