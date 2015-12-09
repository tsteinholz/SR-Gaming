#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_physfs.h>
#include <allegro5/allegro_ttf.h>

#include "util.h"
#include "Card.h"
#include "Deck.h"
#include "Hand.h"

ALLEGRO_DISPLAY *display = NULL;
ALLEGRO_EVENT_QUEUE *queue;
ALLEGRO_TIMER *timer;
ALLEGRO_BITMAP *background;
ALLEGRO_FONT *CoffeeTin[7];
ALLEGRO_FONT *CowboyMovie[7];

const unsigned int SCREEN_W = 800, SCREEN_H = 600;

typedef enum
{
    MainMenu,
	HowToBlackJack,
	Instructions,
    Game,
    FinalMenu
} GameState;

GameState gameState = MainMenu;

int main(int argc, char **argv)
{
    srand(time(NULL));
    if(!al_init())
    {
        fprintf(stderr, "Failed to initialize allegro!\n");
    }
    display = al_create_display(SCREEN_W, SCREEN_H);
    if(!display)
    {
        fprintf(stderr, "Failed to create display!\n");
    }
    al_init_image_addon();
    if(!al_install_audio())
    {
        fprintf(stderr, "Failed to initialize audio!\n");
        return -1;
    }

    if(!al_init_acodec_addon())
    {
        fprintf(stderr, "Failed to initialize audio codecs!\n");
        return -1;
    }

    if (!al_reserve_samples(1))
    {
        fprintf(stderr, "Failed to reserve samples!\n");
        return -1;
    }
    if(!al_install_mouse())
    {
        fprintf(stderr, "Failed to initialize the mouse!\n");
        return -1;
    }
    if(!al_init_primitives_addon())
    {
        fprintf(stderr, "Failed to initialize primitives!\n");
    }
    al_init_font_addon();
    al_init_ttf_addon();
    al_install_keyboard();
    al_clear_to_color(al_map_rgb(0,0,0));

	CoffeeTin[0] = al_load_ttf_font("res/CoffeeTin Initials.ttf", 12, ALLEGRO_ALIGN_CENTRE);
	CoffeeTin[1] = al_load_ttf_font("res/CoffeeTin Initials.ttf", 18, ALLEGRO_ALIGN_CENTRE);
	CoffeeTin[2] = al_load_ttf_font("res/CoffeeTin Initials.ttf", 24, ALLEGRO_ALIGN_CENTRE);
	CoffeeTin[3] = al_load_ttf_font("res/CoffeeTin Initials.ttf", 36, ALLEGRO_ALIGN_CENTRE);
	CoffeeTin[4] = al_load_ttf_font("res/CoffeeTin Initials.ttf", 48, ALLEGRO_ALIGN_CENTRE);
	CoffeeTin[5] = al_load_ttf_font("res/CoffeeTin Initials.ttf", 60, ALLEGRO_ALIGN_CENTRE);
	CoffeeTin[6] = al_load_ttf_font("res/CoffeeTin Initials.ttf", 72, ALLEGRO_ALIGN_CENTRE);

	CowboyMovie[0] = al_load_ttf_font("res/Cowboy Movie.ttf", 12, ALLEGRO_ALIGN_CENTRE);
	CowboyMovie[1] = al_load_ttf_font("res/Cowboy Movie.ttf", 18, ALLEGRO_ALIGN_CENTRE);
	CowboyMovie[2] = al_load_ttf_font("res/Cowboy Movie.ttf", 24, ALLEGRO_ALIGN_CENTRE);
	CowboyMovie[3] = al_load_ttf_font("res/Cowboy Movie.ttf", 36, ALLEGRO_ALIGN_CENTRE);
	CowboyMovie[4] = al_load_ttf_font("res/Cowboy Movie.ttf", 48, ALLEGRO_ALIGN_CENTRE);
	CowboyMovie[5] = al_load_ttf_font("res/Cowboy Movie.ttf", 60, ALLEGRO_ALIGN_CENTRE);
	CowboyMovie[6] = al_load_ttf_font("res/Cowboy Movie.ttf", 72, ALLEGRO_ALIGN_CENTRE);

	background = Util::LoadB("res/table.jpeg");


    queue = al_create_event_queue();
    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_mouse_event_source());
    timer = al_create_timer(1.0 / 60);
    al_register_event_source(queue, al_get_timer_event_source(timer));
    al_start_timer(timer);

	Card test(Card::DIAMONDS, Card::TWO, 30, 234);
	Card test2(Card::SPADES, Card::FOUR, 83, 59);

    bool executing = true;
    while (executing)
    {
        ALLEGRO_EVENT event;
        al_wait_for_event(queue, &event);

        switch(event.type)
        {
        case ALLEGRO_EVENT_DISPLAY_CLOSE:
            break;
        case ALLEGRO_EVENT_KEY_DOWN:
			if (event.keyboard.keycode == ALLEGRO_KEY_ESCAPE) executing = false;
			switch (gameState) {
			case MainMenu:
				gameState = HowToBlackJack;
				break;
			case HowToBlackJack:
				gameState = Instructions;
				break;
			case Instructions:
				gameState = Game;
				break;
			case Game:
				break;
			case FinalMenu:
				break;
			}
            break;
		case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
			switch (gameState) {
			case MainMenu:
				gameState = HowToBlackJack;
				break;
			case HowToBlackJack:
				gameState = Instructions;
				break;
			case Instructions:
				gameState = Game;
				break;
			case Game:
				break;
			case FinalMenu:
				break;
			}
			break;
        case ALLEGRO_EVENT_TIMER:
            break;
        }

        if (al_is_event_queue_empty(queue))
        {
            al_draw_scaled_bitmap(background, 0, 0, al_get_bitmap_width(background), al_get_bitmap_height(background), 0, 0 , SCREEN_W, SCREEN_H, 0);
			switch (gameState)
            {
            case MainMenu:
				al_draw_text(CoffeeTin[6], al_map_rgb(255,255,255), 400, 25, ALLEGRO_ALIGN_CENTRE, "BLACK JACK");
				al_draw_text(CowboyMovie[3], al_map_rgb(255,255,255), 400, 300, ALLEGRO_ALIGN_CENTRE, "CLICK ANYWHERE TO CONTINUE...");
                break;
			case HowToBlackJack:
				al_draw_text(CoffeeTin[6], al_map_rgb(255,255,255), 400, 25, ALLEGRO_ALIGN_CENTRE, "WHAT IS BLACK JACK");
				//al_draw_text(CowboyMovie[3], al_map_rgb(255,255,255), 50, 50, ALLEGRO_ALIGN_CENTRE, "Blackjack is a popular American casino game, now found throughout the world. It is a banking game in which the aim of the player is to achieve a hand whose points total nearer to 21 than the banker\'s hand, but without exceeding 21.");
				
				break;
			case Instructions:
				al_draw_text(CoffeeTin[6], al_map_rgb(255,255,255), 400, 25, ALLEGRO_ALIGN_CENTRE, "INSTRUCTIONS");
				break;
            case Game:
				test.Render();
				test2.Render();
                break;
            case FinalMenu:
                break;

            }
            al_flip_display();
        }
    }
    al_destroy_display(display);
    return 0;
}
