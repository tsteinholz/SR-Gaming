#ifndef UTIL_H_INCLUDED
#define UTIL_H_INCLUDED

#include <cstdio>

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_physfs.h>
#include <allegro5/allegro_ttf.h>

struct Util
{
    static ALLEGRO_BITMAP* LoadB(const char* file)
    {
        ALLEGRO_BITMAP* out = al_load_bitmap(file);
        if (!out) fprintf(stderr, "Failed to load %s graphic!\n", file);
        return out;
    }

    static ALLEGRO_SAMPLE* LoadS(const char* file)
    {
        ALLEGRO_SAMPLE* out = al_load_sample(file);
        if (!out) fprintf(stderr, "Failed to load %s audio!\n", file);
        return out;
    }


    static bool init(ALLEGRO_DISPLAY* display, int width, int height)
    {
        if(!al_init())
        {
            fprintf(stderr, "Failed to initialize allegro!\n");
            return false;
        }
        display = al_create_display(width, height);
        if(!display)
        {
            fprintf(stderr, "Failed to create display!\n");
            return false;
        }
        al_init_font_addon();
        al_init_image_addon();
        al_init_ttf_addon();
        al_install_keyboard();
        al_clear_to_color(al_map_rgb(0,0,0));
        return true;
    }
};
#endif // UTIL_H_INCLUDED
