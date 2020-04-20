#include "AStar.h"
#include "Grid.h"

int main() {
	Grid grid(20,20);
	grid.setObstacle({ 3,5 }, { 6,3 });
	grid.setRoughTerrain({ 9,12 }, { 11,4 });
	grid.enableDiagMove(true);
	//grid.setRoughTerrainCost(2);
	grid.draw();

	Pos start{ 6, 6 }, goal{ 14,8 };
	AStar aStar(grid, start, goal);
	aStar.solve();
	aStar.drawSeq();
	aStar.drawPath();
	int i;
	std::cin >> i;
	return 0;
}