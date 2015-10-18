// Thomas Alexander Steinholz
// South River High School
// C++ w/ Gaming : 1A

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

#include <sstream>
#include <stdio.h>

typedef enum
{
    Menu,
    Game,
    Conclusion,
} Gamemode;

ALLEGRO_BITMAP* Load(const char* file)
{
    ALLEGRO_BITMAP* out = al_load_bitmap(file);
    if (!out) fprintf(stderr, "Failed to load %s graphic!\n", file);
    return out;
}

int main()
{
    const unsigned int SCREEN_W = 1280, SCREEN_H = 768;
    ALLEGRO_DISPLAY *display = NULL;
    ALLEGRO_FONT* century_gothic40;
    ALLEGRO_EVENT_QUEUE* queue;
    ALLEGRO_TIMER* timer;

    ALLEGRO_BITMAP* MenuBackground;
    ALLEGRO_BITMAP* ArenaBackground;
    ALLEGRO_BITMAP* Ball;

    Gamemode gamemode = Menu;

    if(!al_init())
    {
        printf("al_init Failed!\n");
        return -1;
    }
    if(!al_init_primitives_addon())
    {
        printf("al_init_primitives_addon Failed!\n");
        return -1;
    }
    display = al_create_display(SCREEN_W, SCREEN_H);

    if(!display)
    {
        printf("al_create_display Failed!\n");
        return -1;
    }
    al_init_font_addon();
    al_init_ttf_addon();
    al_install_keyboard();
    al_init_image_addon();
    queue = al_create_event_queue();
    al_register_event_source(queue, al_get_keyboard_event_source());
    timer = al_create_timer(1.0 / 60);
    al_register_event_source(queue, al_get_timer_event_source(timer));
    al_start_timer(timer);
    century_gothic40  = al_load_ttf_font("C:\\Windows\\Fonts\\GOTHIC.TTF" , 40, ALLEGRO_ALIGN_CENTRE);

    MenuBackground = Load("res\\menu.png");
    ArenaBackground = Load("res\\arena.png");
    Ball = Load("res\\ball.png");

    int player_y = 0, ai_y = 0, player_y_vel = 0, ai_y_vel = 0;

    bool render;
    bool executing = true;
    while (executing)
    {
        ALLEGRO_EVENT event;
        al_wait_for_event(queue, &event);
        //player_y_vel = ai_y_vel = 0;
        switch(event.type)
        {
        case ALLEGRO_EVENT_DISPLAY_CLOSE:
            executing = false;
            break;
        case ALLEGRO_EVENT_KEY_DOWN:
            switch(event.keyboard.keycode)
            {
                case ALLEGRO_KEY_ESCAPE:
                    executing = false;
                    break;
                case ALLEGRO_KEY_UP:
                case ALLEGRO_KEY_W:
                    player_y_vel = -5;
                    break;
                case ALLEGRO_KEY_DOWN:
                case ALLEGRO_KEY_S:
                    player_y_vel = 5;
                    break;
            }
            gamemode = Game;
            break;
        case ALLEGRO_EVENT_TIMER:
            render = true;
            if (gamemode == Game)
            {
                if (((((SCREEN_H/2)-50)+player_y) <= 4)&&(player_y_vel<0)) player_y_vel = 0;
                if (((((SCREEN_H/2)+50)+player_y) >= SCREEN_H+5)&&(player_y_vel>0)) player_y_vel = 0;
                player_y += player_y_vel;
                ai_y += ai_y_vel;
            }
            break;
        case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
            gamemode = Game;
            break;
        }

        if (al_is_event_queue_empty(queue) && render)
        {
            al_clear_to_color(al_map_rgb(0,0,0));
            al_set_target_bitmap(al_get_backbuffer(display));
            ////////////////////////////////////////////////////////////////////

            switch(gamemode)
            {
            case Menu:
                al_draw_bitmap(MenuBackground, 0, 0, 0);
                break;
            case Game:
                al_draw_bitmap(ArenaBackground, 0, 0, 0);
                al_draw_filled_rectangle(75,((SCREEN_H/2)-50)+player_y,90,((SCREEN_H/2)+50)+player_y,al_map_rgb(255,255,255));              //player
                al_draw_filled_rectangle(SCREEN_W-75,((SCREEN_H/2)-50)+ai_y,SCREEN_W-90,((SCREEN_H/2)+50)+ai_y,al_map_rgb(255,255,255));    //AI
                al_draw_scaled_bitmap(
                    Ball,
                    0, 0,
                    al_get_bitmap_width(Ball), al_get_bitmap_height(Ball),
                    (SCREEN_W/2)-12, (SCREEN_H/2)-15, //x, y
                    15, 15,
                    0);
                break;
            case Conclusion:

                break;
            }

            ////////////////////////////////////////////////////////////////////
            al_flip_display();
        }
        render = false;
    }

    al_destroy_display(display);
    return 0;
}
