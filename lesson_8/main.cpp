#include <iostream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>

#include "ai.hpp"
#include "map.hpp"

int main()
{
	int size = 5;
	int window_wh = 900;
	int margin_map = 20;

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
				"Ошибка при инициализации библиотеки allegro!", NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return (-1);
	}
	
	display = al_create_display(window_wh, window_wh);

	if(!display)
	{
		al_show_native_message_box(NULL, NULL, NULL, "Ошибка при инициализации дисплея!", NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return (-1);
	}

	al_init_primitives_addon();
	al_install_keyboard();
	al_install_mouse();
	al_init_image_addon();

	img_x = al_load_bitmap("x.png");
	img_o = al_load_bitmap("o.png");
	timer = al_create_timer(1.0 / FPS);
	event_queue = al_create_event_queue();

	if(!event_queue)
	{
		al_show_native_message_box(NULL, NULL, NULL,
				"Ошибка при инициализации события!", NULL, ALLEGRO_MESSAGEBOX_ERROR);
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

		if (ev.type == ALLEGRO_EVENT_KEY_DOWN)
		{
			switch (ev.keyboard.keycode)
			{

			}
		}
		else if (ev.type == ALLEGRO_EVENT_KEY_UP)
		{
			switch (ev.keyboard.keycode)
			{
				case ALLEGRO_KEY_ESCAPE:
					done = true;
					continue;
			}
		}
		else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
		{
			done = true;
			continue;
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
				if (game_check(m, HUMAN) || game_check(m, AI))
				{
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

	al_destroy_display(display);

	return (0);
}
