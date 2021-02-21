#ifndef MAP_HPP_
#define MAP_HPP_

#include <allegro5/allegro.h>

typedef enum {HUMAN, AI, EMPTY} PLAYER;

typedef struct
{
	bool is_draw;
	bool select;
	float pos_x;
	float pos_y;
	float width;
	float sym_pos_x;
	float sym_pos_y;
	PLAYER p;
} cell;

typedef enum {HORIZONTAL, VERTICAL} DIRECTION;

typedef struct
{
	DIRECTION d;
	float pos_x;
	float pos_y;
	float width;
	float height;
} line;

typedef struct
{
	cell ***cells;
	line ***grid;
	int toWin;
	int size;
	int window_wh;
	int margin_map;
	int sym_width;
} map;

map *init_map(const int, const int, const int);
cell *create_cell(const float, const float, const float, const float, const float, const float);
line *create_line(DIRECTION, const float, const float, const float, const float, const float);
void draw_map(const map *, ALLEGRO_BITMAP *, ALLEGRO_BITMAP *);
void select_cell(map *, const int, const int);
bool enter_cell(map *, const int, const int, PLAYER);
bool game_check(map *);
void clear_map(map *);
void free_map(map *);
bool exit_game();

#endif
