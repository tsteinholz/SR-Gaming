#include <stdio.h>

#include <allegro5/allegro.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

#include "Card.h"

const int SCREEN_W = 1080, SCREEN_H = 824;

ALLEGRO_BITMAP* background;
ALLEGRO_EVENT_QUEUE* queue;
ALLEGRO_DISPLAY* display = NULL;
ALLEGRO_FONT* century_gothic48B;
ALLEGRO_FONT* century_gothic24;
ALLEGRO_TIMER* timer;

bool init();

int main()
{
    init();

    return 0;
}

bool init()
{
    srand(time(NULL));
    if(!al_init())
    {
        fprintf(stderr, "Failed to initialize allegro!\n");
        return false;
    }
    display = al_create_display(SCREEN_W, SCREEN_H);
    if(!display)
    {
        fprintf(stderr, "Failed to create display!\n");
        return false;
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
        return false;
    }
    al_init_font_addon();
    al_init_ttf_addon();
    al_install_keyboard();
    al_clear_to_color(al_map_rgb(0,0,0));

    century_gothic48B = al_load_ttf_font("C:\\Windows\\Fonts\\GOTHICB.TTF", 48, ALLEGRO_ALIGN_CENTRE);
    century_gothic24  = al_load_ttf_font("C:\\Windows\\Fonts\\GOTHIC.TTF" , 24, ALLEGRO_ALIGN_CENTRE);

    queue = al_create_event_queue();
    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_mouse_event_source());
    timer = al_create_timer(1.0 / 60);
    al_register_event_source(queue, al_get_timer_event_source(timer));
    al_start_timer(timer);
    return true;
}

ALLEGRO_BITMAP* LoadB(const char* file)
{
    ALLEGRO_BITMAP* out = al_load_bitmap(file);
    if (!out) fprintf(stderr, "Failed to load %s graphic!\n", file);
    return out;
}

ALLEGRO_SAMPLE* LoadS(const char* file)
{
    ALLEGRO_SAMPLE* out = al_load_sample(file);
    if (!out) fprintf(stderr, "Failed to load %s audio!\n", file);
    return out;
}
