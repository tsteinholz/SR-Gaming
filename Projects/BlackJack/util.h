#ifndef UTIL_H_INCLUDED
#define UTIL_H_INCLUDED

#include <cstdio>
#include <fstream>
#include <iostream>

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_physfs.h>
#include <allegro5/allegro_ttf.h>

//-----------------------------------------------------------------------------
// Purpose: Functions that can make my code cleaner with less effort
//-----------------------------------------------------------------------------
struct Util
{
    //-----------------------------------------------------------------------------
    // Purpose: Safely open a bitmap with error handling and no effort
    //-----------------------------------------------------------------------------
    static inline ALLEGRO_BITMAP *LoadB(const char *file)
    {
        ALLEGRO_BITMAP *out = al_load_bitmap(file);
        if (!out) fprintf(stderr, "Failed to load %s graphic!\n", file);
        return out;
    }

    //-----------------------------------------------------------------------------
    // Purpose: Safely open a audio sample with error handling and no effort
    //-----------------------------------------------------------------------------
    static inline ALLEGRO_SAMPLE *LoadS(const char *file)
    {
        ALLEGRO_SAMPLE *out = al_load_sample(file);
        if (!out) fprintf(stderr, "Failed to load %s audio!\n", file);
        return out;
    }

    //-----------------------------------------------------------------------------
    // Purpose: Load a float value from file
    //-----------------------------------------------------------------------------
    static inline float LoadFloat(const char *file)
    {
        std::fstream _file(file, std::ios_base::in);

        float ret;
        while (_file >> ret)
        {
            if (ret != NULL || ret != 0) return ret;
        }
    }

    //-----------------------------------------------------------------------------
    // Purpose: Save a float to file
    //-----------------------------------------------------------------------------
    static inline void SaveFloat(const char *file, float x)
    {
        // TODO : Saving a generic value to file
        //std::ofstream output;
        //output.open(file);
        //if (output.good()) {
        //    output.write((unsigned int)x, sizeof(x));
        //}
        //output.close();
    }
};

#endif // UTIL_H_INCLUDED
