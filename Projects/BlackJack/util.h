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
};

#endif // UTIL_H_INCLUDED
