#ifndef MAP_HPP_
#define MAP_HPP_

typedef struct
{
	bool is_draw;
	bool select;
	float pos_x;
	float pos_y;
	float width;
	float sym_pos_x;
	float sym_pos_y;
	float sym_width;

} cell;

typedef enum {horizontal, vertical} direction;

typedef struct
{
	direction d;
	float pos_x;
	float pos_y;
	float width;
	float height;
} line;

typedef struct
{
	cell ***cells;
	line ***grid;
	int size;
	int window_wh;
	int margin_map;
} map;

map *init_map(const int, const int, const int);
cell *create_cell(const float, const float, const float, const float, const float, const float, const float);
line *create_line(direction, const float, const float, const float, const float, const float);
void draw_map(const map *);

#endif
