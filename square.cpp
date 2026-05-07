#include"square.h"
#include<allegro5/allegro_primitives.h>

square::square() {
	x = 0;
	y = 0;
	landed = false;
}

square::square(int xpos, int ypos) {
	x = xpos;
	y = ypos;
	landed = false;
}

void square::draw(int map[10][16]) {
	map[x / 50][y / 50] = 1;
	map[(x + 50) / 50][y / 50] = 1;
	map[x / 50][(y + 50) / 50] = 1;
	map[(x + 50) / 50][(y + 50) / 50] = 1;
}


void square::land(int map[10][16]) {
	landed = true;
	map[x / 50][y / 50] = 10;
	map[(x + 50) / 50][y / 50] = 10;
	map[x / 50][(y + 50) / 50] = 10;
	map[(x + 50) / 50][(y + 50) / 50] = 10;
}


void square::MoveSideways(char dir, int grid[10][16]) {
	if (dir == 'r' && x < 500 - 100 &&
		(grid[(x + 100) / 50][y / 50] != 10) &&
		(grid[(x + 100) / 50][(y + 50) / 50] != 10) &&
		(grid[(x + 100) / 50][(y + 100) / 50] != 10))
		x += 50;

	else if (dir == 'l' && x > 0 &&
		(grid[(x - 50) / 50][y / 50] != 10) &&
		(grid[(x - 50) / 50][(y + 50) / 50] != 10) &&
		(grid[(x - 50) / 50][(y + 100) / 50] != 10))
		x -= 50;

	else if (dir == 'd' && y < 800 - 100)
		y += 50;
}

bool square::checkCollision(int grid[10][16]) {
	if ((grid[x / 50][(y + 100) / 50] == 10) || (grid[(x + 50) / 50][(y + 100) / 50] == 10))
		return true;
		
	if (y + 100 > 800)
		return true;
	else
		return false;
}
