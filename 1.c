//GoofProg - 10-30-2017
//admiralsmithzero@gmail.com
//Allegro Hello World with font
//Computer used:  Dell Vostro 1520 with Fedora 26
//Allegro installed from OS not compile.
//installed with 'sudo dnf install allegro5*'
//Compiled with 'gcc 1.c -lallegro -lallegro_font -lallegro_ttf'
//Most of the code was from examples with a little modification.

//This code is meant for a game loop event so if there was an actual game made it would all be redrawn in the event loop

#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

const float FPS = 60;

int main()
{
	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	ALLEGRO_TIMER *timer = NULL;

	bool running = true;
	bool redraw = true;

	if (!al_init()) {
		fprintf(stderr,"FAILED\n");
		return 1;
		}

	display = al_create_display(800,600);
	if (!display) {
		fprintf(stderr,"FAILED\n");
		return 1;
		}

	event_queue = al_create_event_queue();
	if (!event_queue) {
		fprintf(stderr,"FAILED\n");
		return 1;
	}

	timer = al_create_timer(1.0 / FPS);
	if (!timer) {
		fprintf(stderr, "Failed to create timer.\n");
		return 1;
	}

	al_init_font_addon();
	al_init_ttf_addon();
	ALLEGRO_FONT *font = al_load_ttf_font("Perfect DOS VGA 437.ttf",36,0);
	if (!font) {
		fprintf(stderr,"FAILED\n");
		return 1;
		}


	al_register_event_source(event_queue, al_get_display_event_source(display));
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	// Display a black screen
	al_clear_to_color(al_map_rgb(0, 0, 0));
	al_flip_display();

	// Start the timer
	al_start_timer(timer);

	// Game loop
	while (running) {
		ALLEGRO_EVENT event;
		ALLEGRO_TIMEOUT timeout;

		// Initialize timeout
		al_init_timeout(&timeout, 0.06);

		// Fetch the event (if one exists)
		bool get_event = al_wait_for_event_until(event_queue, &event, &timeout);

		// Handle the event
		if (get_event) {
			switch (event.type) {
				case ALLEGRO_EVENT_TIMER:
					redraw = true;
					break;
				case ALLEGRO_EVENT_DISPLAY_CLOSE:
					running = false;
					break;
				default:
					fprintf(stderr, "Unsupported event received: %d\n",event.type);
					break;
			}
		}

		// Check if we need to redraw
		if (redraw && al_is_event_queue_empty(event_queue)) {
			// Redraw
			al_clear_to_color(al_map_rgb(0, 0, 0));
			al_draw_text(font, al_map_rgb(0xFF,0xFF,0xFF),800/2, (800/4), ALLEGRO_ALIGN_CENTRE,"Hello World from Allegro 5!");
			al_draw_text(font, al_map_rgb(0xFF,0xA5,0x00),800/2,(800/4)+30, ALLEGRO_ALIGN_CENTER,"Happy Halloween! 10-30-17");
			al_draw_text(font, al_map_rgb(0x00,0xFF,0x00),0,560,0,"-GoofProg");
			al_flip_display();
			redraw = false;
		}
	} 

	// Clean up
	al_destroy_display(display);
	al_destroy_event_queue(event_queue);

return 0;
}

//references:
//hexadecimal conversion handled with ISO99 
//http://www.color-hex.com/color/ffa500

