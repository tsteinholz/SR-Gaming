#ifndef ROW_H
#define ROW_H

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

struct Peg
{
public:
    typedef enum
    {
        RED     = 0xCF2104,
        BLUE    = 0x3F00FF,
        YELLOW  = 0xBAFF1E,
        GREEN   = 0x117050,
        WHITE   = 0xFFFFFF,
        ORANGE  = 0xC65104,
        NOTHING = 0x554E44,
    } COLOR;

    Peg() { SetColor(NOTHING); }

    inline void SetColor(COLOR color)
    {
        switch(color)
        {
            case RED:     m_Color = al_map_rgb(255, 51,  51);  break;
            case BLUE:    m_Color = al_map_rgb(51,  51,  255); break;
            case YELLOW:  m_Color = al_map_rgb(255, 255, 102); break;
            case GREEN:   m_Color = al_map_rgb(51,  255, 153); break;
            case WHITE:   m_Color = al_map_rgb(224, 224, 224); break;
            case ORANGE:  m_Color = al_map_rgb(255, 153, 51);  break;
            case NOTHING:
            default:      m_Color = al_map_rgb(96,  96,  96);  break;
        }
    }

    inline void Render(unsigned int x, unsigned int y, unsigned int r)
    {
        al_draw_filled_circle(x, y, r, m_Color);
    }

private:
    ALLEGRO_COLOR m_Color;
};

class Row
{
public:
    Row(unsigned int x, unsigned int y, bool results);
    virtual ~Row();

    void Render();

protected:
    Peg m_Pegs[4], m_ResultPegs[4];
    unsigned int m_x, m_y, m_Coords[4];
    bool m_Results;
};

#endif // ROW_H
