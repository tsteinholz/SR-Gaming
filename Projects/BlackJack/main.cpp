#include "BlackJack.h"

ALLEGRO_DISPLAY *display = NULL;
ALLEGRO_EVENT_QUEUE *queue;
ALLEGRO_TIMER *timer;
ALLEGRO_BITMAP *background;
ALLEGRO_FONT *CoffeeTin[7];
ALLEGRO_FONT *CowboyMovie[7];
ALLEGRO_SAMPLE *AprilShowers;

const unsigned int SCREEN_W = 900, SCREEN_H = 600;

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
    srand((unsigned int) time(NULL));
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

    al_set_window_title(display, "BlackJack by Thomas Steinholz");

    // Load Some Sweet Fonts (Coffee Tin)
	CoffeeTin[0] = al_load_ttf_font("res/CoffeeTin Initials.ttf", 12, ALLEGRO_ALIGN_CENTRE);
	CoffeeTin[1] = al_load_ttf_font("res/CoffeeTin Initials.ttf", 18, ALLEGRO_ALIGN_CENTRE);
	CoffeeTin[2] = al_load_ttf_font("res/CoffeeTin Initials.ttf", 24, ALLEGRO_ALIGN_CENTRE);
	CoffeeTin[3] = al_load_ttf_font("res/CoffeeTin Initials.ttf", 36, ALLEGRO_ALIGN_CENTRE);
	CoffeeTin[4] = al_load_ttf_font("res/CoffeeTin Initials.ttf", 48, ALLEGRO_ALIGN_CENTRE);
	CoffeeTin[5] = al_load_ttf_font("res/CoffeeTin Initials.ttf", 60, ALLEGRO_ALIGN_CENTRE);
	CoffeeTin[6] = al_load_ttf_font("res/CoffeeTin Initials.ttf", 72, ALLEGRO_ALIGN_CENTRE);

    // Load Some Sweet Fonts (Cowboy Movie)
	CowboyMovie[0] = al_load_ttf_font("res/Cowboy Movie.ttf", 12, ALLEGRO_ALIGN_CENTRE);
	CowboyMovie[1] = al_load_ttf_font("res/Cowboy Movie.ttf", 18, ALLEGRO_ALIGN_CENTRE);
	CowboyMovie[2] = al_load_ttf_font("res/Cowboy Movie.ttf", 24, ALLEGRO_ALIGN_CENTRE);
	CowboyMovie[3] = al_load_ttf_font("res/Cowboy Movie.ttf", 36, ALLEGRO_ALIGN_CENTRE);
	CowboyMovie[4] = al_load_ttf_font("res/Cowboy Movie.ttf", 48, ALLEGRO_ALIGN_CENTRE);
	CowboyMovie[5] = al_load_ttf_font("res/Cowboy Movie.ttf", 60, ALLEGRO_ALIGN_CENTRE);
	CowboyMovie[6] = al_load_ttf_font("res/Cowboy Movie.ttf", 72, ALLEGRO_ALIGN_CENTRE);

	background = Util::LoadB("res/table.jpeg");
    AprilShowers = Util::LoadS("res/AprilShowers.ogg");

    queue = al_create_event_queue();
    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_mouse_event_source());
    timer = al_create_timer(1.0 / 60);
    al_register_event_source(queue, al_get_timer_event_source(timer));
    al_start_timer(timer);

    al_play_sample(AprilShowers, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP, NULL);

    BlackJack* game = new BlackJack(CoffeeTin, CowboyMovie);

    bool executing = true;
    while (executing)
    {
        ALLEGRO_EVENT event;
        al_wait_for_event(queue, &event);

        executing = game->Executing;
        game->Update(&event);

        switch(event.type)
        {
        //case ALLEGRO_EVENT_MOUSE_LEAVE_DISPLAY://lol
        case ALLEGRO_EVENT_DISPLAY_CLOSE:
            executing = false;
            printf("debug: hit the close button");
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
        case ALLEGRO_EVENT_MOUSE_AXES:
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
				al_draw_text(CoffeeTin[6], al_map_rgb(255,255,255), (SCREEN_W / 2), 25,
                    ALLEGRO_ALIGN_CENTRE, "BLACK JACK");
                al_draw_text(CowboyMovie[2], al_map_rgb(255,255,255), (SCREEN_W / 2), 100,
                    ALLEGRO_ALIGN_CENTRE, "THOMAS STEINHOLZ");
				al_draw_text(CowboyMovie[4], al_map_rgb(255,255,255), (SCREEN_W / 2), 300,
                    ALLEGRO_ALIGN_CENTRE, "CLICK ANYWHERE TO CONTINUE...");
                break;
			case HowToBlackJack:
				al_draw_text(CoffeeTin[6], al_map_rgb(255,255,255), (SCREEN_W / 2), 25,
                    ALLEGRO_ALIGN_CENTRE, "WHAT IS BLACK JACK");
				al_draw_text(CowboyMovie[2], al_map_rgb(255,255,255), (SCREEN_W / 2), 150,
                    ALLEGRO_ALIGN_CENTRE, "BLACKJACK IS A POPULAR AMERICAN CASINO GAME, NOW FOUND THROUGHOUT THE WORLD.");
                al_draw_text(CowboyMovie[2], al_map_rgb(255,255,255), (SCREEN_W / 2), 190,
                    ALLEGRO_ALIGN_CENTRE, "IT IS A BANKING GAME IN WHICH THE AIM OF THE PLAYER IS TO ACHIEVE A HAND");
                al_draw_text(CowboyMovie[2], al_map_rgb(255,255,255), (SCREEN_W / 2), 230,
                    ALLEGRO_ALIGN_CENTRE, "WHOSE POINTS TOTAL NEARER TO 21 THAN THE BANKER\'S HAND, BUT WITHOUT EXCEEDING 21.");
				al_draw_text(CowboyMovie[2], al_map_rgb(255,255,255), (SCREEN_W / 2), 270,
                    ALLEGRO_ALIGN_CENTRE, "ALTHOUGH MANY PLAYERS MAY PLAY IN A SINGLE ROUND OF BLACKJACK, IT'S FUNDAMENTALLY A");
                al_draw_text(CowboyMovie[2], al_map_rgb(255,255,255), (SCREEN_W / 2), 310,
                    ALLEGRO_ALIGN_CENTRE, "TWO-PLAYER GAME. IN BLACKJACK, PLAYERS DON'T PLAY AGAINST EACH OTHER; AND THEY DON'T");
                al_draw_text(CowboyMovie[2], al_map_rgb(255,255,255), (SCREEN_W / 2), 350,
                    ALLEGRO_ALIGN_CENTRE, "CO-OPERATE. THE ONLY COMPETITION IS THE DEALER.");
                al_draw_text(CowboyMovie[2], al_map_rgb(255,255,255), (SCREEN_W / 2), 390,
                    ALLEGRO_ALIGN_CENTRE, "THE AIM OF THE GAME IS TO ACCUMULATE A HIGHER POINT TOTAL THAN THE DEALER, BUT WITHOUT");
                al_draw_text(CowboyMovie[2], al_map_rgb(255,255,255), (SCREEN_W / 2), 430,
                    ALLEGRO_ALIGN_CENTRE, "GOING OVER 21. YOU COMPUTE YOUR SCORE BY ADDING THE VALUES OF YOUR INDIVIDUAL CARDS.");
                break;
			case Instructions:
				al_draw_text(CoffeeTin[6], al_map_rgb(255,255,255), (SCREEN_W / 2), 25,
                    ALLEGRO_ALIGN_CENTRE, "INSTRUCTIONS");
                al_draw_text(CowboyMovie[2], al_map_rgb(255,255,255), (SCREEN_W / 2), 150,
                    ALLEGRO_ALIGN_CENTRE, "THERE IS GAMBLING IN THIS GAME, BUT IT IS NOT PUNISHABLE UNDER AACPS RULES DUE TO THE FACT THAT");
                al_draw_text(CowboyMovie[2], al_map_rgb(255,255,255), (SCREEN_W / 2), 190,
                    ALLEGRO_ALIGN_CENTRE, "THERE IS NOT PROPERTY OR MONEY BEING GAMBLED BUT ONLY IN GAME IMAGINARY CURRENCY THAT CANNOT");
                al_draw_text(CowboyMovie[2], al_map_rgb(255,255,255), (SCREEN_W / 2), 230,
                    ALLEGRO_ALIGN_CENTRE, "HARM ANYONE IN ANY WAY. YOU CAN PLAY THIS GAME UNLIMITEDLY, YOU PLAY EACH ROUND INDEPENDATLY");
                al_draw_text(CowboyMovie[2], al_map_rgb(255,255,255), (SCREEN_W / 2), 270,
                    ALLEGRO_ALIGN_CENTRE, "OF EACH OTHERTHE GAME STARTS BY DEALING YOU A CARD, YOU PUSH THE BUTTON \"HIT ME\" OR \"HOLD\"");
                al_draw_text(CowboyMovie[2], al_map_rgb(255,255,255), (SCREEN_W / 2), 310,
                    ALLEGRO_ALIGN_CENTRE, "YOU WILL CONTINUE TO HIT THESE BUTTONS UNTILL YOU BUST OR HOLD, ONCE YOU GET TO THAT POINT THE");
                al_draw_text(CowboyMovie[2], al_map_rgb(255,255,255), (SCREEN_W / 2), 350,
                    ALLEGRO_ALIGN_CENTRE, "CARDS OF THE DEALER WILL BE SHOWN TO YOU AND YOU WILL SEE WHO WON, YOU OR THE DEALER. YOU WILL");
                al_draw_text(CowboyMovie[2], al_map_rgb(255,255,255), (SCREEN_W / 2), 390,
                    ALLEGRO_ALIGN_CENTRE, "BE ABLE TO BET ON EACH ROUND, EVERY WIN IS 2X WHAT YOU PUT IN AND YOU GET 1/2 OF WHAT YOU PUT IN");
                al_draw_text(CowboyMovie[2], al_map_rgb(255,255,255), (SCREEN_W / 2), 430,
                    ALLEGRO_ALIGN_CENTRE, "FOR A LOSS.");
				break;
            case Game:
                game->Render();
                break;
            case FinalMenu:
                break;
            }
            al_flip_display();
        }
    }
    delete game;
    al_destroy_display(display);

    return 0;
}
