#include"Jblock.h"
#include<allegro5/allegro_primitives.h>

Jblock::Jblock() {
	x = 0;
	y = 0;
	spin = 1;
	landed = false;
}

Jblock::Jblock(int xpos, int ypos) {
	x = xpos;
	y = ypos;
	landed = false;
	spin = 1;
}

int Jblock::turn(char dir) {
	if (spin == 4) {
		spin = 1;
		return 1;
	}
	//dont spin if too close to the right edge
	if (spin < 4 && (x < (9 * 50)))
		spin += 1;
	return 1;
}

void Jblock::draw(int map[10][16]) {
	if (spin == 1) {
		map[x / 50][y / 50] = 7;
		map[(x - 50) / 50][y / 50] = 7;
		map[(x + 50) / 50][y / 50] = 7;
		map[(x + 50) / 50][(y + 50) / 50] = 7;
	}
	else if (spin == 2) {
		map[x / 50][y / 50] = 7;
		map[x / 50][(y + 50) / 50] = 7;
		map[x / 50][(y - 50) / 50] = 7;
		map[(x - 50) / 50][(y + 50) / 50] = 7;
	}
	else if (spin == 3) {
		map[x / 50][y / 50] = 7;
		map[(x - 50) / 50][(y - 50) / 50] = 7;
		map[(x - 50) / 50][y / 50] = 7;
		map[(x + 50) / 50][y / 50] = 7;
	}
	else if (spin == 4) {
		map[x / 50][y / 50] = 7;
		map[x / 50][(y + 50) / 50] = 7;
		map[(x + 50) / 50][(y - 50) / 50] = 7;
		map[x / 50][(y - 50) / 50] = 7;
	}
}

void Jblock::land(int map[10][16]) {
	landed = true;
	if (spin == 1) {
		map[x / 50][y / 50] = 70;
		map[(x - 50) / 50][y / 50] = 70;
		map[(x + 50) / 50][y / 50] = 70;
		map[(x + 50) / 50][(y + 50) / 50] = 70;
	}
	else if (spin == 2) {
		map[x / 50][y / 50] = 70;
		map[x / 50][(y + 50) / 50] = 70;
		map[x / 50][(y - 50) / 50] = 70;
		map[(x - 50) / 50][(y + 50) / 50] = 70;
	}
	else if (spin == 3) {
		map[x / 50][y / 50] = 70;
		map[(x - 50) / 50][(y - 50) / 50] = 70;
		map[(x - 50) / 50][y / 50] = 70;
		map[(x + 50) / 50][y / 50] = 70;
	}
	else if (spin == 4) {
		map[x / 50][y / 50] = 70;
		map[x / 50][(y + 50) / 50] = 70;
		map[(x + 50) / 50][(y - 50) / 50] = 70;
		map[x / 50][(y - 50) / 50] = 70;
	}
}
//moves the piece based on keyboard input
void Jblock::MoveSideways(char dir, int grid[10][16]) {

	if (dir == 'r' && spin == 1 && x < 500 - 50 &&
		(grid[(x + 100) / 50][(y + 50) / 50] < 10))
		x += 50;
	else if ((dir == 'r') && (spin == 2) && x < 500 &&
		(grid[(x + 50) / 50][y / 50] < 10) &&
		(grid[(x + 50) / 50][(y + 50) / 50] < 10) &&
		(grid[(x + 50) / 50][(y - 50) / 50] < 10))
		x += 50;
	else if ((dir == 'r') && (spin == 3) && x < 500 - 50 && 
		(grid[(x + 100) / 50][y / 50] < 10) &&
		(grid[x / 50][(y - 50) / 50] < 10))
		x += 50;
	else if ((dir == 'r') && (spin == 4) && x < 500 - 50
		&& (grid[(x + 50) / 50][y / 50] < 10)
		&& (grid[(x + 100) / 50][(y - 50) / 50] < 10)
		&& (grid[(x + 50) / 50][(y + 50) / 50] < 10))
		x += 50;


	else if (dir == 'l' && (spin == 1) && x > 50 &&
		(grid[x / 50][(y + 50) / 50] < 10) &&
		(grid[(x - 100) / 50][y / 50] < 10))
		x -= 50;
	else if (dir == 'l' && (spin == 2) && x > 50 &&
		(grid[(x - 50) / 50][y / 50] < 10) &&
		(grid[(x - 50) / 50][(y - 50) / 50] < 10) &&
		(grid[(x - 100) / 50][(y + 50) / 50] < 10))
		x -= 50;
	else if (dir == 'l' && (spin == 3) && x > 50 &&
		(grid[(x - 100) / 50][y / 50] < 10) &&
		(grid[(x - 100) / 50][(y - 50) / 50] < 10))
		x -= 50;
	else if (dir == 'l' && (spin == 4) && x > 0 &&
		(grid[(x - 50) / 50][y / 50] < 10) &&
		(grid[(x - 50) / 50][(y - 50) / 50] < 10) &&
		(grid[(x - 50) / 50][(y + 50) / 50] < 10))
		x -= 50;
	else if (dir == 'd' && y < 800 - 100)
		y += 50;

}

bool Jblock::checkCollision(int grid[10][16]) {

	if (spin == 1) {
		if ((grid[x / 50][(y + 50) / 50] >= 10) ||
			(grid[(x + 50) / 50][(y + 100) / 50] >= 10) ||
			(grid[(x - 50) / 50][(y + 50) / 50] >= 10))
			return true;
		if (y + 100 > 800)
			return true;
		else
			return false;
	}
	else if (spin == 2) {
		if ((grid[x / 50][(y + 100) / 50] >= 10) ||
			(grid[(x - 50) / 50][(y + 100) / 50] >= 10))
			return true;
		if (y + 100 > 800)
			return true;
		else
			return false;
	}
	else if (spin == 3) {
		if ((grid[x / 50][(y + 50) / 50] >= 10) ||
			(grid[(x + 50) / 50][(y + 50) / 50] >= 10) ||
			(grid[(x - 50) / 50][(y + 50) / 50] >= 10))
			return true;
		if (y + 50 > 800)
			return true;
		else
			return false;
	}
	else if (spin == 4) {
		if ((grid[x / 50][(y + 100) / 50] >= 10) ||
			(grid[(x + 50) / 50][y / 50] >= 10))
			return true;
		if (y + 100 > 800)
			return true;
		else
			return false;
	}
	return false;


}
