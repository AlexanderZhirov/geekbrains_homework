#include <iostream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>

#include "ai.hpp"
#include "map.hpp"
#include "parse_args.hpp"

int main(int argc, char **argv)
{
	int countKeys = 3;

	ra::key ks;  // size
	ra::key kw;  // width/height window
	ra::key km;  // margin map

	ra::key *keys[countKeys] = {&ks, &kw, &km};

	ra::parse_args(argc, argv, keys);

	int size = 3;
	int window_wh = 600;
	int margin_map = 20;

	if (ks.isset)
	{
		size = atoi(ks.arguments[0]);
		if (size > 10 || size < 3)
			size = 3;
	}

	if (kw.isset)
	{
		window_wh = atoi(kw.arguments[0]);
		if (window_wh > 1000 || window_wh < 300)
			window_wh = 600;
	}

	if (km.isset)
	{
		margin_map = atoi(km.arguments[0]);
		if (margin_map > 100 || size < 20)
			margin_map = 20;
	}

	map *m = init_map(size, window_wh, margin_map);

	bool done = false;
	bool redraw = true;
	bool isdraw = true;
	int FPS = 60;
	bool move_ai = false;

	int mouse_x = 0;
	int mouse_y = 0;

	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	ALLEGRO_TIMER *timer = NULL;
	ALLEGRO_BITMAP *img_x = NULL;
	ALLEGRO_BITMAP *img_o = NULL;

	if (!al_init())
	{
		al_show_native_message_box(NULL, NULL, NULL,
				"Не удается инициализировать allegro!", NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return (-1);
	}
	
	display = al_create_display(window_wh, window_wh);

	if(!display)
	{
		al_show_native_message_box(NULL, NULL, "Ошибка!", "Не удается инициализировать дисплей!", NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return (-1);
	}

	al_init_primitives_addon();
	al_install_keyboard();
	al_install_mouse();
	al_init_image_addon();

	img_x = al_load_bitmap("x.png");

	if(!img_x)
	{
		al_show_native_message_box(display, NULL, "Ошибка!", "Не удается инициализировать \"x.png\"", NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return (-1);
	}

	img_o = al_load_bitmap("o.png");

	if(!img_o)
	{
		al_show_native_message_box(display, NULL, "Ошибка!", "Не удается инициализировать \"o.png\"!", NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return (-1);
	}

	timer = al_create_timer(1.0 / FPS);
	event_queue = al_create_event_queue();

	if(!event_queue)
	{
		al_show_native_message_box(display, NULL, "Ошибка!",
				"Не удается инициализировать событие!", NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return (-1);
	}

	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_display_event_source(display));
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_mouse_event_source());

	al_start_timer(timer);

	while (!done)
	{
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);

		if (ev.type == ALLEGRO_EVENT_KEY_UP)
		{
			switch (ev.keyboard.keycode)
			{
				case ALLEGRO_KEY_ESCAPE:
					if (exit_game(display))
					{
						done = true;
						continue;
					}
					al_flush_event_queue(event_queue);
			}
		}
		else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
		{
			if (exit_game(display))
			{
				done = true;
				continue;
			}
			al_flush_event_queue(event_queue);
		}
		else if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP)
		{
			if (isdraw && enter_cell(m, mouse_x, mouse_y, HUMAN))
			{
				move_ai = true;
				isdraw = false;
			}
		}
		else if (ev.type == ALLEGRO_EVENT_MOUSE_AXES)
		{
			mouse_x = ev.mouse.x;
			mouse_y = ev.mouse.y;
		}
		else if (ev.type == ALLEGRO_EVENT_TIMER)
		{
			if (isdraw)
			{
				if (game_check(m, display))
				{
					al_flush_event_queue(event_queue);
					done = true;
					continue;
				}

				if (move_ai)
				{
					aiTurn(m);
					move_ai = false;
					isdraw = false;
				}
			}

			select_cell(m, mouse_x, mouse_y);

			redraw = true;
		}

		if (redraw && al_is_event_queue_empty(event_queue))
		{
			redraw = false;
			isdraw = true;

			draw_map(m, img_x, img_o);

			al_flip_display();
			al_clear_to_color(al_map_rgb(255, 255, 255));
		}
	}

	free_map(m);

	al_destroy_display(display);
	al_destroy_bitmap(img_x);
	al_destroy_bitmap(img_o);
	al_destroy_timer(timer);
	al_destroy_event_queue(event_queue);

	return (0);
}
