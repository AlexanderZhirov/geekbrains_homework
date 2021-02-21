#include "map.hpp"
#include <cstdlib>
#include <allegro5/allegro_primitives.h>

map *init_map(const int size, const int window_wh, const int margin_map)
{
	map *m = (map *)malloc(sizeof(map));

	float map_wh = 0;                             // размер карты с учётом отступов
	float cell_width = 0;                         // ширина ячейки
	float cell_margin = 0;                        // отступ внутри ячейки
	float line_count = 0;                         // количество линий на одно направление
	float line_width = 0;                         // ширина линии
	float cell_sym_width = 0;                     // ширина сивола внутри ячейки

	m->size = size;
	m->window_wh = window_wh;
	m->margin_map = margin_map;

	line_count = size - 1;
	map_wh = window_wh - margin_map * 2;
	line_width = map_wh * 0.0036;
	cell_width = map_wh / size;
	cell_margin = cell_width * 0.0538;
	cell_sym_width = cell_width - (line_width * 2) - (cell_margin * 2);

	m->sym_width = cell_sym_width;

	m->cells = (cell ***)malloc(sizeof(cell **) * (size * size));

	for (int i = 0; i < size; ++i)
	{
		m->cells[i] = (cell **)malloc(sizeof(cell *) * size);

		for (int j = 0; j < size; ++j)
		{
			m->cells[i][j] = create_cell(j, i, cell_width, cell_margin, line_width, margin_map);
		}
	}

	m->grid = (line ***)malloc(sizeof(line **) * (line_count * line_count));

	for (int i = 0; i < 2; ++i)
	{
		m->grid[i] = (line **)malloc(sizeof(line *) * line_count);

		direction d = (i == 0 ? horizontal : vertical);

		for (int j = 0; j < line_count; ++j)
		{
			m->grid[i][j] = create_line(d, j, line_width, map_wh, cell_width, margin_map);
		}
	}

	return m;
}

cell *create_cell(const float row, const float col, const float cell_width, const float cell_margin, const float line_width, const float margin_map)
{
	cell *c = (cell *)malloc(sizeof(cell));
	c->select = false;
	c->is_draw = false;
	c->pos_x = row * cell_width + margin_map;
	c->pos_y = col * cell_width + margin_map;
	c->width = cell_width;
	c->sym_pos_x = c->pos_x + line_width + cell_margin;
	c->sym_pos_y = c->pos_y + line_width + cell_margin;
	return c;
}

line *create_line(direction d, const float row, const float line_width, const float map_wh, const float cell_width, const float margin_map)
{
	line *l = (line *)malloc(sizeof(line));
	l->d = d;
	l->height = map_wh;
	l->width = line_width;
	if (d == horizontal)
	{
		l->pos_x = margin_map;
		l->pos_y = (row + 1) * cell_width + margin_map - line_width;
	}
	else
	{
		l->pos_x = (row + 1) * cell_width + margin_map - line_width;
		l->pos_y = margin_map;
	}

	return l;
}

void draw_map(const map *m, ALLEGRO_BITMAP *b)
{
	int size = m->size;

	int swh = al_get_bitmap_width(b);

	for (int i = 0; i < size; ++i)
	{
		for (int j = 0; j < size; ++j)
		{
			cell *c = m->cells[i][j];

			if (c->is_draw)
				al_draw_scaled_bitmap(b, 0, 0, swh, swh, c->sym_pos_x, c->sym_pos_y, m->sym_width, m->sym_width, 0);
//				al_draw_filled_rectangle(c->pos_x, c->pos_y, c->pos_x + c->width, c->pos_y + c->width, al_map_rgb(255, 0, 255));
//				al_draw_text(f, al_map_rgba_f(100, 100, 255, 0.9), 0 - c->sym_width / 2, 0 - c->sym_width / 2, 0, "x");
//				al_draw_text(f, al_map_rgba_f(100, 100, 255, 0.9), (c->sym_pos_x + c->sym_width / 2) - (c->sym_width / 4), (c->sym_pos_y + c->sym_width / 2) - (c->sym_width / 4), 0, "X");


			if (c->select)
			{
				if (c->is_draw)
					al_draw_tinted_scaled_bitmap(b, al_map_rgba_f(255, 0, 0, 0.3), 0, 0, swh, swh, c->sym_pos_x, c->sym_pos_y, m->sym_width, m->sym_width, 0);
				else
					al_draw_tinted_scaled_bitmap(b, al_map_rgba_f(0, 255, 0, 0.3), 0, 0, swh, swh, c->sym_pos_x, c->sym_pos_y, m->sym_width, m->sym_width, 0);
			}


//				al_draw_filled_rectangle(c->pos_x, c->pos_y, c->pos_x + c->width, c->pos_y + c->width, al_map_rgb(0, 0, 255));
		}
	}

	for (int i = 0; i < 2; ++i)
	{
		for (int j = 0; j < size - 1; ++j)
		{
			line *l = m->grid[i][j];

			if (l->d == horizontal)
				al_draw_filled_rectangle(l->pos_x, l->pos_y, l->pos_x + l->height, l->pos_y + l->width, al_map_rgb(255, 255, 255));
			else
				al_draw_filled_rectangle(l->pos_x, l->pos_y, l->pos_x + l->width, l->pos_y + l->height, al_map_rgb(255, 255, 255));
		}
	}
}

void select_cell(map *m, const int mouse_x, const int mouse_y)
{
	int size = m->size;

	for (int i = 0; i < size; ++i)
	{
		for (int j = 0; j < size; ++j)
		{
			cell *c = m->cells[i][j];

			if ((mouse_x >= c->pos_x && mouse_y >= c->pos_y) &&
					(mouse_x <= (c->pos_x + c->width) && mouse_y <= (c->pos_y + c->width)))
				c->select = true;
			else
				c->select = false;
		}
	}
}

void enter_cell(map *m, const int mouse_x, const int mouse_y)
{
	int size = m->size;

	for (int i = 0; i < size; ++i)
	{
		for (int j = 0; j < size; ++j)
		{
			cell *c = m->cells[i][j];

			if (!c->is_draw && (mouse_x >= c->pos_x && mouse_y >= c->pos_y) &&
					(mouse_x <= (c->pos_x + c->width) && mouse_y <= (c->pos_y + c->width)))
				c->is_draw = true;
		}
	}
}
