#include<iostream>
using namespace std;
#include<allegro5/allegro.h>
#include<allegro5/allegro_primitives.h>
#include<allegro5/allegro_image.h>
#include<allegro5/allegro_font.h>
#include<allegro5/allegro_ttf.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include<vector>
#include"line.h"
#include"piece.h"
#include"square.h"
#include"tblock.h"
#include"Lblock.h"
#include"Jblock.h"
#include"sblock.h"
#include"zblock.h"
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
	// 1. Install audio
	al_install_audio();
	// 2. Initialize codecs
	al_init_acodec_addon();
	// 3. Reserve 1 voice
	al_reserve_samples(2);

	srand(time(NULL));

	ALLEGRO_TIMER* timer = al_create_timer(1.0 / FPS);
	ALLEGRO_DISPLAY* display = al_create_display(SCREEN_WIDTH, SCREEN_HEIGHT);
	ALLEGRO_EVENT_QUEUE* event_queue = al_create_event_queue();
	ALLEGRO_FONT* font = al_load_font("myfont.ttf", 40, 0);
	ALLEGRO_AUDIO_STREAM* stream = al_load_audio_stream("Minecraft.mp3", 4, 2048);
	ALLEGRO_SAMPLE* sample = al_load_sample("gamebeep.mp3");
	bool doexit = false;
	int ticker = 0;
	int moveTimer = 0;
	bool key[4] = { false, false, false,false };
	bool redraw = true;
	bool ActivePiece = false;
	int pieceChoice = 0;
	int score = 0;

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
	al_rest(1);
	while (!doexit) {
	
		//if music is loaded
		if (stream) {
			al_attach_audio_stream_to_mixer(stream, al_get_default_mixer()); //connect the stream to mixer that plays audio //mixer controls all audio
			al_set_audio_stream_gain(stream, 1.0); //volume 100%
			al_set_audio_stream_speed(stream, 1.5); //speed (1.0 is normal, 0.5 is half, 2.0 is 2x speed)
			al_set_audio_stream_playmode(stream, ALLEGRO_PLAYMODE_LOOP); // play in a loop
		}

		//timer section///////////////////////////////////////////////////////////
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);
		if (ev.type == ALLEGRO_EVENT_TIMER) {
			ticker++;
			moveTimer++;

			//cull the grid
			if (ticker > 50)
				if (cullGrid() == true) {
					score += 100;
					al_play_sample(sample, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
					ticker = 0;
				}
					
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
				pieceChoice = rand() % 7 + 1; //randomly pick the next piece type

				if (pieceChoice == 1) {
					line* newline = new line((rand() % 10) * 50, 0);
					pieces.push_back(newline);
					cout << "pushed |" << endl;
				}
				else if (pieceChoice == 2) {
					square* newsquare = new square((rand() % 9) * 50, 0);
					pieces.push_back(newsquare);
					cout << "pushed O" << endl;
				}
				else if (pieceChoice == 3) {
					tblock* newtblock = new tblock((rand() % 8 + 1) * 50, 0);
					pieces.push_back(newtblock);
					cout << "pushed T" << endl;
				}
				else if (pieceChoice == 4) {
					sblock* newsblock = new sblock((rand() % 8 + 1) * 50, 0);
					pieces.push_back(newsblock);
					cout << "pushed S" << endl;
				}
				else if (pieceChoice == 5) {
					zblock* newzblock = new zblock((rand() % 8 + 1) * 50, 0);
					pieces.push_back(newzblock);
					cout << "pushed Z" << endl;
				}
				else if (pieceChoice == 6) {
					Lblock* newLblock = new Lblock((rand() % 8 + 1) * 50, 50);
					pieces.push_back(newLblock);
					cout << "pushed L" << endl;
				}
				else if (pieceChoice == 7) {
					Jblock* newJblock = new Jblock((rand() % 8 + 1) * 50, 50);
					pieces.push_back(newJblock);
					cout << "pushed J" << endl;
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
		//render section//////////////////////////////////////////////////////
		
		if (redraw && al_is_event_queue_empty(event_queue)) {
			redraw = false;
			al_clear_to_color(al_map_rgb(255, 255, 255));

			al_draw_textf(font, al_map_rgb(110, 110, 110), 20, 10, NULL, "Score: %d", score);

			//draw pieces
			for (iter = pieces.begin(); iter != pieces.end(); iter++) {
				(*iter)->draw(grid);
			}

			for (int x = 0; x < 10; x++) {
				for (int y = 0; y < 16; y++) {
					if (grid[x][y] == 0) //draw grid lines
						al_draw_rectangle(x * 50, y * 50, x * 50 + 50, y * 50 + 50, al_map_rgb(0, 0, 0), 2);

					if ((grid[x][y] == 1) || (grid[x][y] == 10)) {//draw line pieces
						al_draw_filled_rectangle(x * 50, y * 50, x * 50 + 50, y * 50 + 50, al_map_rgb(82, 208, 217)); //cyan
						al_draw_rectangle(x * 50, y * 50, x * 50 + 50, y * 50 + 50, al_map_rgb(25, 50, 55), 4);
					}
					if ((grid[x][y] == 2) || (grid[x][y] == 20)) {//draw square
						al_draw_filled_rectangle(x * 50, y * 50, x * 50 + 50, y * 50 + 50, al_map_rgb(255, 50, 55)); //red
						al_draw_rectangle(x * 50, y * 50, x * 50 + 50, y * 50 + 50, al_map_rgb(25, 50, 55), 4);
					}
					if ((grid[x][y] == 3) || (grid[x][y] == 30)) {//draw T
						al_draw_filled_rectangle(x * 50, y * 50, x * 50 + 50, y * 50 + 50, al_map_rgb(115, 72, 207)); //purple
						al_draw_rectangle(x * 50, y * 50, x * 50 + 50, y * 50 + 50, al_map_rgb(25, 50, 55), 4);
					}
					if ((grid[x][y] == 4) || (grid[x][y] == 40)) {//draw S
						al_draw_filled_rectangle(x * 50, y * 50, x * 50 + 50, y * 50 + 50, al_map_rgb(70, 163, 75)); //green
						al_draw_rectangle(x * 50, y * 50, x * 50 + 50, y * 50 + 50, al_map_rgb(25, 50, 55), 4);
					}
					if ((grid[x][y] == 5) || (grid[x][y] == 50)) {//draw Z
						al_draw_filled_rectangle(x * 50, y * 50, x * 50 + 50, y * 50 + 50, al_map_rgb(243, 255, 23)); //yellow
						al_draw_rectangle(x * 50, y * 50, x * 50 + 50, y * 50 + 50, al_map_rgb(25, 50, 55), 4);
					}
					if ((grid[x][y] == 6) || (grid[x][y] == 60)) {//draw L
						al_draw_filled_rectangle(x * 50, y * 50, x * 50 + 50, y * 50 + 50, al_map_rgb(63, 68, 217)); //blue
						al_draw_rectangle(x * 50, y * 50, x * 50 + 50, y * 50 + 50, al_map_rgb(25, 50, 55), 4);
					}
					if ((grid[x][y] == 7) || (grid[x][y] == 70)) {//draw J
						al_draw_filled_rectangle(x * 50, y * 50, x * 50 + 50, y * 50 + 50, al_map_rgb(250, 152, 60)); //orange
						al_draw_rectangle(x * 50, y * 50, x * 50 + 50, y * 50 + 50, al_map_rgb(25, 50, 55), 4);
					}
				}
			}
			al_flip_display();
		}//end of render

	}//end of game loop
	al_clear_to_color(al_map_rgb(255, 51, 51));
	al_draw_text(font, al_map_rgb(255, 255, 255), 150, 200, NULL, "GAME OVER!");
	al_draw_textf(font, al_map_rgb(255, 255, 255), 150, 300, NULL, "Score: %d", score);
	al_flip_display();
	al_rest(3);
	al_destroy_display(display);
	al_destroy_audio_stream(stream);

}



bool cullGrid() {
	int rowcount = 0;
	for (int k = 0; k < 16; k++) {
		rowcount = 0;
		for (int i = 0; i < 10; i++) {
			if (grid[i][k] >= 10) {
				rowcount++;
			}
		}
		if (rowcount == 10) {
			for (int i = 0; i < 10; i++)
				for (int j = k; j > 0; j--) { 
					grid[i][j] = grid[i][j - 1];
				}
			return true;
		}
	}
	return false;
}
