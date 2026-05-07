#pragma once
#include"piece.h"

class zblock : public piece {
private:
public:
	zblock();
	zblock(int xpos, int ypos);

	void MoveSideways(char dir, int grid[10][16]);
	int turn(char dir);

	void draw(int map[10][16]);

	void land(int map[10][16]);
	bool checkCollision(int grid[10][16]);
};
