#include<iostream>
using namespace std;
#include<allegro5/allegro.h>
#include<allegro5/allegro_primitives.h>
#include<allegro5/allegro_image.h>
#include<allegro5/allegro_font.h>
#include<allegro5/allegro_ttf.h>
#include<vector>
#include"line.h"
#include"piece.h"
#include"square.h"
#include"iblock.h"
#include"squiggle.h"
const int SCREEN_WIDTH = 500;
const int SCREEN_HEIGHT = 800;
const int FPS = 60;

bool cullGrid(); 

int grid[10][16] = {
	0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0
};
enum MYKEYS
{
	KEY_LEFT, KEY_RIGHT, KEY_UP, KEY_DOWN
};

int main() {
	al_init();
	al_init_primitives_addon();
	al_init_image_addon();
	al_install_keyboard();
	al_init_primitives_addon();
	al_init_font_addon();
	al_init_ttf_addon();

	srand(time(NULL));

	ALLEGRO_TIMER* timer = al_create_timer(1.0 / FPS);
	ALLEGRO_DISPLAY* display = al_create_display(SCREEN_WIDTH, SCREEN_HEIGHT);
	ALLEGRO_EVENT_QUEUE* event_queue = al_create_event_queue();
	ALLEGRO_FONT* font = al_load_font("myfont.ttf", 40, 0);
	bool doexit = false;
	int ticker = 0;
	int moveTimer = 0;
	bool key[4] = { false, false, false,false };
	bool redraw = true;
	bool ActivePiece = false;
	int pieceChoice = 0;

	vector<piece*> pieces;
	vector<piece*>::iterator iter;

	//allegro start up stuff
	al_set_target_bitmap(al_get_backbuffer(display));

	al_register_event_source(event_queue, al_get_display_event_source(display));

	al_register_event_source(event_queue, al_get_timer_event_source(timer));

	al_register_event_source(event_queue, al_get_keyboard_event_source());

	al_clear_to_color(al_map_rgb(0, 0, 0));

	al_flip_display();

	al_start_timer(timer);

	al_clear_to_color(al_map_rgb(0, 0, 0));
	al_draw_text(font, al_map_rgb(200, 200, 200), 200, 200, NULL, "Tetris!");
	al_flip_display();
	al_rest(3);
	while (!doexit) {
		//render section//////////////////////////////////////////////////////
		if (redraw && al_is_event_queue_empty(event_queue)) {
			redraw = false;
			al_clear_to_color(al_map_rgb(0, 0, 0));

			//draw pieces
			for (iter = pieces.begin(); iter != pieces.end(); iter++) {
				(*iter)->draw(grid);
			}

			for (int x = 0; x < 10; x++) {
				for (int y = 0; y < 16; y++) {
					if (grid[x][y] == 0) //draw grid lines
						al_draw_rectangle(x * 50, y * 50, x * 50 + 50, y * 50 + 50, al_map_rgb(255, 255, 255), 2);
					if (grid[x][y] == 1) {//draw active line pieces
						al_draw_filled_rectangle(x * 50, y * 50, x * 50 + 50, y * 50 + 50, al_map_rgb(255, 50, 55));
						al_draw_rectangle(x * 50, y * 50, x * 50 + 50, y * 50 + 50, al_map_rgb(25, 50, 55), 4);
					}
					if (grid[x][y] == 10) {//draw inactive line pieces
						al_draw_filled_rectangle(x * 50, y * 50, x * 50 + 50, y * 50 + 50, al_map_rgb(255, 50, 55));
						al_draw_rectangle(x * 50, y * 50, x * 50 + 50, y * 50 + 50, al_map_rgb(25, 50, 55), 4);
					}
				}
			}
		}

		al_flip_display();


		//timer section///////////////////////////////////////////////////////////
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);
		if (ev.type == ALLEGRO_EVENT_TIMER) {
			ticker++;
			moveTimer++;

			//cull the grid
			if (ticker > 50)
				if (cullGrid() == true)
					ticker = 0;
			if (moveTimer > 5) {
				if (key[KEY_LEFT]) {
					for (iter = pieces.begin(); iter != pieces.end(); iter++) {
						(*iter)->MoveSideways('l', grid);
					}
				}
				if (key[KEY_RIGHT]) {
					for (iter = pieces.begin(); iter != pieces.end(); iter++) {
						(*iter)->MoveSideways('r', grid);
					}
				}
				if (key[KEY_DOWN]) {
					for (iter = pieces.begin(); iter != pieces.end(); iter++) {
						(*iter)->MoveSideways('d', grid);
					}
				}
				if (key[KEY_UP]) {
					for (iter = pieces.begin(); iter != pieces.end(); iter++) {
						(*iter)->turn('r');
					}
				}
				moveTimer = 0;
			}

			//create new piece
			if (ActivePiece == false && ticker > 50) {
				pieceChoice = rand() % 1 + 1; //randomly pick the next piece type

				if (pieceChoice == 1) {
					line* newline = new line((rand() % 10) * 50, 0);
					pieces.push_back(newline);
					cout << "pushed line" << endl;
				}

				ActivePiece = true;
			}

			//check if player has lost
			for (iter = pieces.begin(); iter != pieces.end(); iter++) {
				if ((*iter)->checkCollision(grid)) {
					cout << "y vaule is " << (*iter)->getY() << endl;
					if ((*iter)->getY() <= 0) {
						cout << "game over" << endl;
						doexit = true;
					}
				}
			}

			//check if a piece has hit the bottom or other pieces
			for (iter = pieces.begin(); iter != pieces.end(); iter++) {
				if ((*iter)->checkCollision(grid)) {
					(*iter)->land(grid);
					ActivePiece = false;
					iter = pieces.erase(iter); //erase the piece from the vector when it lands
					break;
				}
			}

			//move pieces if they haven't hit the bottom
			for (iter = pieces.begin(); iter != pieces.end(); iter++) {
				if (!(*iter)->isLanded())
					(*iter)->move();
			}
			//wipe map
			for (int x = 0; x < 10; x++) {
				for (int y = 0; y < 16; y++) {
					if (grid[x][y] < 10)
						grid[x][y] = 0;
				}
			}
			redraw = true;

		}//end of timer

		else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			break;
		}
		else if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
			switch (ev.keyboard.keycode) {


			case ALLEGRO_KEY_LEFT:
				key[KEY_LEFT] = true;
				break;

			case ALLEGRO_KEY_RIGHT:
				key[KEY_RIGHT] = true;
				break;

			case ALLEGRO_KEY_DOWN:
				key[KEY_DOWN] = true;
				break;

			case ALLEGRO_KEY_UP:
				key[KEY_UP] = true;
				break;
			}
		}
		else if (ev.type == ALLEGRO_EVENT_KEY_UP) {
			switch (ev.keyboard.keycode) {


			case ALLEGRO_KEY_LEFT:
				key[KEY_LEFT] = false;
				break;

			case ALLEGRO_KEY_RIGHT:
				key[KEY_RIGHT] = false;
				break;

			case ALLEGRO_KEY_DOWN:
				key[KEY_DOWN] = false;
				break;
			case ALLEGRO_KEY_UP:
				key[KEY_UP] = false;
				break;

			case ALLEGRO_KEY_ESCAPE:
				doexit = true;
				break;
			}
		}
	}
}
bool cullGrid() {

	int RowCount = 0;

	for (int k = 0; k < 16; k++) {
		RowCount = 0;
		for (int i = 0; i < 10; i++) {
			if (grid[i][k] == 10) {
				RowCount++;
			}
		}
		//if 10 out of 10 squares are filled, move the whole matrix down a row
		if (RowCount == 10) {
			for (int i = 0; i < 10; i++)
				for (int j = k; j > 0; j--) { //start from the bottom up so we don't erase data
					grid[i][j] = grid[i][j - 1];//replaces a row with whatever is above it
				}

			return true;


		}
	}
	return false;

}
