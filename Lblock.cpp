#include"Lblock.h"
#include<allegro5/allegro_primitives.h>

Lblock::Lblock() {
	x = 0;
	y = 0;
	spin = 1;
	landed = false;
}

Lblock::Lblock(int xpos, int ypos) {
	x = xpos;
	y = ypos;
	landed = false;
	spin = 1;
}

int Lblock::turn(char dir) {
	if (spin == 4) {
		spin = 1;
		return 1;
	}
	//dont spin if too close to the right edge
	if (spin < 4 && (x < (9 * 50)))
		spin += 1;
	return 1;
}

void Lblock::draw(int map[10][16]) {
	if (spin == 1) {
		map[x / 50][y / 50] = 6;
		map[(x - 50) / 50][y / 50] = 6;
		map[(x + 50) / 50][y / 50] = 6;
		map[(x + 50) / 50][(y - 50) / 50] = 6;
	}
	else if (spin == 2) {
		map[x / 50][y / 50] = 6;
		map[x / 50][(y + 50) / 50] = 6;
		map[x / 50][(y - 50) / 50] = 6;
		map[(x + 50) / 50][(y + 50) / 50] = 6;
	}
	else if (spin == 3) {
		map[x / 50][y / 50] = 6;
		map[(x-50) / 50][(y + 50) / 50] = 6;
		map[(x - 50) / 50][y / 50] = 6;
		map[(x + 50) / 50][y / 50] = 6;
	}
	else if (spin == 4) {
		map[x / 50][y / 50] = 6;
		map[x / 50][(y + 50) / 50] = 6;
		map[(x - 50) / 50][(y - 50) / 50] = 6;
		map[x / 50][(y - 50) / 50] = 6;
	}
}

void Lblock::land(int map[10][16]) {
	landed = true;
	if (spin == 1) {
		map[x / 50][y / 50] = 60;
		map[(x - 50) / 50][y / 50] = 60;
		map[(x + 50) / 50][y / 50] = 60;
		map[(x + 50) / 50][(y - 50) / 50] = 60;
	}
	else if (spin == 2) {
		map[x / 50][y / 50] = 60;
		map[x / 50][(y + 50) / 50] = 60;
		map[x / 50][(y - 50) / 50] = 60;
		map[(x + 50) / 50][(y + 50) / 50] = 60;
	}
	else if (spin == 3) {
		map[x / 50][y / 50] = 60;
		map[(x - 50) / 50][(y + 50) / 50] = 60;
		map[(x - 50) / 50][y / 50] = 60;
		map[(x + 50) / 50][y / 50] = 60;
	}
	else if (spin == 4) {
		map[x / 50][y / 50] = 60;
		map[x / 50][(y + 50) / 50] = 60;
		map[(x - 50) / 50][(y - 50) / 50] = 60;
		map[x / 50][(y - 50) / 50] = 60;
	}
}
//moves the piece based on keyboard input
void Lblock::MoveSideways(char dir, int grid[10][16]) {

	if (dir == 'r' && spin == 1 && x < 500 - 100 &&
		(grid[(x + 100) / 50][(y - 50) / 50] < 10))
		x += 50;
	else if ((dir == 'r') && (spin == 2) && x < 500 - 100 &&
		(x + 50 < 500) && (grid[(x + 50) / 50][y / 50] < 10)
		&& (grid[(x + 100) / 50][(y+50) / 50] < 10)
		&& (grid[(x + 50) / 50][(y - 50) / 50] < 10))
		x += 50;
	else if ((dir == 'r') && (spin == 3) && x < 500 - 100 &&
		(grid[(x + 100) / 50][y / 50] < 10) &&
		(grid[x / 50][(y + 50) / 50] < 10))
		x += 50;
	else if ((dir == 'r') && (spin == 4) && x < 500 &&
		(grid[(x + 50) / 50][y / 50] < 10) &&
		(grid[(x + 50) / 50][(y + 50) / 50] < 10) &&
		(grid[(x + 50) / 50][(y - 50) / 50] < 10))
		x += 50;


	else if (dir == 'l' && (spin == 1) && x > 50 &&
		(grid[x / 50][(y - 50) / 50] < 10) &&
		(grid[(x - 100) / 50][y / 50] < 10))
		x -= 50;
	else if (dir == 'l' && (spin == 2) && x > 0 &&
		(grid[(x - 50) / 50][y / 50] < 10) &&
		(grid[(x - 50) / 50][(y + 50) / 50] < 10) &&
		(grid[(x - 50) / 50][(y - 50) / 50] < 10))
		x -= 50;
	else if (dir == 'l' && (spin == 3) && x > 50 &&
		(grid[(x - 100) / 50][y / 50] < 10) &&
		(grid[(x - 100) / 50][(y + 50) / 50] < 10))
		x -= 50;
	else if (dir == 'l' && (spin == 4) && x > 50 &&
		(grid[(x - 50) / 50][y / 50] < 10) &&
		(grid[(x - 100) / 50][(y - 50) / 50] < 10) &&
		(grid[(x - 50) / 50][(y + 50) / 50] < 10))
		x -= 50;
	else if (dir == 'd' && y < 800 - 100)
		y += 50;

}

bool Lblock::checkCollision(int grid[10][16]) {

	if (spin == 1) {
		if ((grid[x / 50][(y + 50) / 50] >= 10) ||
			(grid[(x + 50) / 50][(y + 50) / 50] >= 10) ||
			(grid[(x - 50) / 50][(y + 50) / 50] >= 10))
			return true;
		if (y + 50 > 800)
			return true;
		else
			return false;
	}
	else if (spin == 2) {
		if ((grid[x / 50][(y + 100) / 50] >= 10) ||
			(grid[(x + 50) / 50][(y + 100) / 50] >= 10))
			return true;
		if (y + 100 > 800)
			return true;
		else
			return false;
	}
	else if (spin == 3) {
		if ((grid[x / 50][(y + 50) / 50] >= 10) ||
			(grid[(x + 50) / 50][(y + 50) / 50] >= 10) ||
			(grid[(x - 50) / 50][(y + 100) / 50] >= 10))
			return true;
		if (y + 100 > 800)
			return true;
		else
			return false;
	}
	else if (spin == 4) {
		if ((grid[x / 50][(y + 100) / 50] >= 10) ||
			(grid[(x - 50) / 50][y / 50] >= 10))
			return true;
		if (y + 100 > 800)
			return true;
		else
			return false;
	}
	return false;


}
