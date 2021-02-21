#include <iostream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_primitives.h>

#include "map.hpp"

int main()
{
	int size = 3;
	int window_wh = 600;
	int margin_map = 20;

	map *m = init_map(size, window_wh, margin_map);

	ALLEGRO_DISPLAY *display = NULL;

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

	al_clear_to_color(al_map_rgb(0, 0, 0));

	draw_map(m);

	al_flip_display();

	al_rest(10.0);

	al_destroy_display(display);

	return (0);
}
