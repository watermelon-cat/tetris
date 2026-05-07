#include"sblock.h"
#include<allegro5/allegro_primitives.h>

sblock::sblock() {
	x = 0;
	y = 0;
	landed = false;
	spin = 1;
}

sblock::sblock(int xpos, int ypos) {
	x = xpos;
	y = ypos;
	landed = false;
	spin = 1;
}
int sblock::turn(char dir) {
	if (spin == -1) {
		spin *= -1;
		return 1;
	}
	//dont spin if too close to the right edge
	if (spin == 1 && (x < (9 * 50)))
		spin *= -1;
	return 1;
}
void sblock::draw(int map[10][16]) {
	if (spin == 1) {
		map[x / 50][y / 50] = 1;
		map[x / 50][(y + 50) / 50] = 1;
		map[(x+50) / 50][y / 50] = 1;
		map[(x-50) / 50][(y + 50) / 50] = 1;
	}
	else if (spin == -1) {
		map[x / 50][y / 50] = 1;
		map[(x + 50) / 50][y / 50] = 1;
		map[x / 50][(y-50) / 50] = 1;
		map[(x + 50) / 50][(y+50) / 50] = 1;
	}
}

void sblock::land(int map[10][16]) {
	landed = true;
	if (spin == 1) {
		map[x / 50][y / 50] = 10;
		map[x / 50][(y + 50) / 50] = 10;
		map[(x + 50) / 50][y / 50] = 10;
		map[(x - 50) / 50][(y + 50) / 50] = 10;
	}
	else if (spin == -1) {
		map[x / 50][y / 50] = 10;
		map[(x + 50) / 50][y / 50] = 10;
		map[x / 50][(y - 50) / 50] = 10;
		map[(x + 50) / 50][(y + 50) / 50] = 10;
	}
}

void sblock::MoveSideways(char dir, int grid[10][16]) {
	if (spin == 1) {
		if ((dir == 'r') && (x < 500 - 100) &&
			(grid[(x + 100) / 50][y / 50] != 10) &&
			(grid[(x + 50) / 50][(y + 50) / 50] != 10))
			x += 50;
		else if ((dir == 'l') && (x > 50) &&
			(grid[(x - 100) / 50][(y + 50) / 50] != 10) &&
			(grid[(x - 50) / 50][y / 50] != 10))
			x -= 50;
		else if ((dir == 'd') && (y < 800 - 100))
			y += 50;
	}
	else if (spin == -1) {
		if ((dir == 'r') && (spin == -1) && (x < 500 - 50) &&
			(grid[(x + 100) / 50][y / 50] != 10) &&
			(grid[(x + 50) / 50][(y - 50) / 50] != 10) &&
			(grid[(x + 50) / 50][(y + 50) / 50] != 10))
			x += 50;
		else if ((dir == 'l') && (spin == -1) && (x > 0) &&
			(grid[(x - 50) / 50][(y - 50) / 50] != 10) &&
			(grid[(x - 50) / 50][y / 50] != 10) &&
			(grid[x / 50][(y + 50) / 50] != 10))
			x -= 50;
		else if ((dir == 'd') && (y < 800 - 150))
			y += 50;
	}
}
bool sblock::checkCollision(int grid[10][16]) {
	if (spin == 1) {
		if ((grid[x / 50][(y + 100) / 50] == 10) ||
			(grid[(x + 50) / 50][(y + 50) / 50] == 10) ||
			(grid[(x - 50) / 50][(y + 100) / 50] == 10))
			return true;
		if (y + 100 > 800)
			return true;
		else 
			return false;
	}
	else if (spin == -1) {
		if ((grid[x / 50][(y + 50) / 50] == 10) ||
			(grid[(x + 50) / 50][(y + 100) / 50] == 10))
			return true;
		if (y + 100 > 800)
			return true;
		else 
			return false;
	}
	return false;
}
