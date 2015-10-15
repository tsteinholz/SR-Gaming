#include <iostream>
#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

bool init();

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
    Row(unsigned int x, unsigned int y, bool results)
        : m_x(x), m_y(y), m_Results(results)
    {
        m_Coords[0] = m_x;
        m_Coords[1] = m_Coords[0] + 100;
        m_Coords[2] = m_Coords[1] + 100;
        m_Coords[3] = m_Coords[2] + 100;

        if (m_Results)
        {
            //TODO: results math
        }
    }
    virtual ~Row() {}

    void Render()
    {
        for (unsigned int i = 0; i < 4; i++)
        {
            m_Pegs[i].Render(m_Coords[i], m_y, 20);
        }

        if (m_Results)
        {
            //for (unsigned int i = 0; i < 4; i++)
            //{
            //    m_ResultPegs[i].Render(m_Coords[i], m_Coords[i], 5);
            //}
        }
    }

protected:
    Peg m_Pegs[4], m_ResultPegs[4];
    unsigned int m_x, m_y, m_Coords[4];
    bool m_Results;
};

ALLEGRO_DISPLAY* display = NULL;
ALLEGRO_EVENT_QUEUE* queue;
ALLEGRO_TIMER* timer;
ALLEGRO_BITMAP* background;
ALLEGRO_BITMAP* border;
ALLEGRO_FONT* century_gothic48B;

const unsigned int SCREEN_W = 1080, SCREEN_H = 824;

int main(int argc, char **argv)
{
    if (!init()) return -1;

    queue = al_create_event_queue();
    al_register_event_source(queue, al_get_keyboard_event_source());
    timer = al_create_timer(1.0 / 60);
    al_register_event_source(queue, al_get_timer_event_source(timer));
    al_start_timer(timer);

    Row* Grid[10] =
    {
        new Row(480, 160, false),
        new Row(480, 207, false),
        new Row(480, 254, false),
        new Row(480, 301, false),
        new Row(480, 348, false),
        new Row(480, 395, false),
        new Row(480, 442, false),
        new Row(480, 489, false),
        new Row(480, 536, false),
        new Row(480, 583, false)
    };

    bool executing = true;
    while (executing) {
        ALLEGRO_EVENT event;
        al_wait_for_event(queue, &event);

        switch(event.type) {
            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                break;
            case ALLEGRO_EVENT_KEY_DOWN:
                if (event.keyboard.keycode == ALLEGRO_KEY_ESCAPE) executing = false;
                break;
            case ALLEGRO_EVENT_TIMER:
                break;
        }

        if (al_is_event_queue_empty(queue)) {
            al_clear_to_color(al_map_rgb(0,0,0));
            al_set_target_bitmap(al_get_backbuffer(display));
            al_draw_bitmap(background, 0, 0, 0);
            al_draw_bitmap(border, 400, 30, 0);
            al_draw_text(century_gothic48B, al_map_rgb(255,255,255), SCREEN_W-355, 50, ALLEGRO_ALIGN_CENTRE, "Master Mind");
            //TODO : Add more text
            ////////////////////////////////////////////////////////////////////

            for (unsigned int i = 0; i < 10; i++) Grid[i]->Render();

            ////////////////////////////////////////////////////////////////////
            al_flip_display();
        }
    }

    for (unsigned int i = 0; i < 10; i++) delete Grid[i];

    al_destroy_bitmap(background);
    al_destroy_display(display);
    return 0;
}

bool init() {
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
    if(!al_init_primitives_addon()) {
        fprintf(stderr, "Failed to initialize primitives!\n");
        return false;
    }
    al_init_font_addon();
    al_init_ttf_addon();
    al_install_keyboard();
    al_clear_to_color(al_map_rgb(0,0,0));

    background = al_load_bitmap("res\\background.png");
    if (!background) {
        fprintf(stderr, "Failed load background image!\n");
        al_destroy_display(display);
        return false;
    }
    border = al_load_bitmap("res\\border.png");
    if (!border) {
        fprintf(stderr, "Failed load border image!\n");
        al_destroy_display(display);
        return false;
    }

    century_gothic48B = al_load_ttf_font("C:\\Windows\\Fonts\\GOTHICB.TTF", 48, ALLEGRO_ALIGN_CENTRE);

    return true;
}

