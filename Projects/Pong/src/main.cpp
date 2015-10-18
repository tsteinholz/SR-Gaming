// Thomas Alexander Steinholz
// South River High School
// C++ w/ Gaming : 1A

#include <sstream>
#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

int main()
{
    const unsigned int SCREEN_W = 1080, SCREEN_H = 824;
    ALLEGRO_DISPLAY *display = NULL;
    ALLEGRO_FONT* century_gothic40;
    ALLEGRO_EVENT_QUEUE* queue;
    ALLEGRO_TIMER* timer;
    unsigned int score1 = 0, score2 = 0;

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
    queue = al_create_event_queue();
    al_register_event_source(queue, al_get_keyboard_event_source());
    timer = al_create_timer(1.0 / 60);
    al_register_event_source(queue, al_get_timer_event_source(timer));
    al_start_timer(timer);
    century_gothic40  = al_load_ttf_font("C:\\Windows\\Fonts\\GOTHIC.TTF" , 40, ALLEGRO_ALIGN_CENTRE);

    bool render;
    bool executing = true;
    while (executing)
    {
        ALLEGRO_EVENT event;
        al_wait_for_event(queue, &event);

        switch(event.type)
        {
        case ALLEGRO_EVENT_DISPLAY_CLOSE:
            executing = false;
            break;
        case ALLEGRO_EVENT_KEY_DOWN:
            if (event.keyboard.keycode == ALLEGRO_KEY_ESCAPE) executing = false;
            break;
        case ALLEGRO_EVENT_TIMER:
            render = true;
            break;
        case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
            break;
        }

        if (al_is_event_queue_empty(queue) && render)
        {
            al_clear_to_color(al_map_rgb(0,0,0));
            al_set_target_bitmap(al_get_backbuffer(display));
            ////////////////////////////////////////////////////////////////////

            std::stringstream ss;
            ss << " " << score1;
            const char* sscore1 = ss.str().c_str();
            ss.str( std::string() );
            ss.clear();
            ss << " " << score2;
            const char* sscore2 = ss.str().c_str();
            // Scores
            al_draw_text(century_gothic40, al_map_rgb(255,255,255), 250,          100, ALLEGRO_ALIGN_CENTRE, sscore1);
            al_draw_text(century_gothic40, al_map_rgb(255,255,255), SCREEN_W-250, 100, ALLEGRO_ALIGN_CENTRE, sscore2);


            ////////////////////////////////////////////////////////////////////
            al_flip_display();
        }
        render = false;
    }

    // Destroying the display we created, to avoid memory leaking.
    al_destroy_display(display);

    return 0;
}
