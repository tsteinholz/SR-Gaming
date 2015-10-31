// Thomas Alexander Steinholz
// South River High School
// C++ w/ Gaming : 1A

#include <iostream>
#include <stdio.h>
#include <vector>

#include <allegro5/allegro.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

// Global Variables
ALLEGRO_BITMAP* background;
ALLEGRO_BITMAP* border;
ALLEGRO_BITMAP* key_backspace;
ALLEGRO_BITMAP* key_enter;
ALLEGRO_EVENT_QUEUE* queue;
ALLEGRO_DISPLAY* display = NULL;
ALLEGRO_FONT* century_gothic48B;
ALLEGRO_FONT* century_gothic24;
ALLEGRO_TIMER* timer;
const unsigned int SCREEN_W = 1080, SCREEN_H = 824;

using namespace std;

bool init();

struct Code
{
    enum Peg
    {
        RED, BLUE, YELLOW,
        GREEN, WHITE, ORANGE,
        NOTHING,
    };

    Code()
    {
        Peg temp[4];
        for(int i = 0; i < 4; i++)
        {
            switch(rand() % 6)
            {
                case 0:  temp[i] = RED;    break;
                case 1:  temp[i] = BLUE;   break;
                case 2:  temp[i] = YELLOW; break;
                case 3:  temp[i] = GREEN;  break;
                case 4:  temp[i] = WHITE;  break;
                case 5:  temp[i] = ORANGE; break;
                default: temp[i] = NOTHING;
            }
        }
        A = temp[0]; B = temp[1];
        C = temp[2]; D = temp[3];
    }

    Code(Peg x)
        : A(x), B(x), C(x), D(x) {}

    Code(Peg a, Peg b, Peg c, Peg d)
        : A(a), B(b), C(c), D(d) {}

    Code(const Code& copy)
        : A(copy.A), B(copy.B), C(copy.C), D(copy.D) {}

    Peg A, B, C, D;

    inline bool Verify()
    {
        return A != NOTHING &&
               B != NOTHING &&
               C != NOTHING &&
               D != NOTHING;
    }

    bool operator==(const Code& other) const
    {
        return ((A == other.A) && (B == other.B) && (C == other.C) && (D == other.D));
    }

    bool operator!=(const Code &other) const {
        return !(*this == other);
    }
};

Code* Turn()
{
    return NULL;
}

bool Feedback(Code* code, Code* guess)
{
    std::string result = "";
    bool checked;
    Code::Peg codePeg[4] = {code->A, code->B, code->C, code->D}, guessPeg[4]= {guess->A, guess->B, guess->C, guess->D};

    for (int i = 0; i < 4; i++)
    {
        for (int j = i; j < 4; j++)
        {
            checked = false;
            if (codePeg[i] == guessPeg[j])
            {
                if (i == j)
                {
                    result += "o";
                    checked = true;
                }
            }
            else
            {
                for (int k = i+1; k < 4; k++)
                {
                    if ((codePeg[k] == guessPeg[j]) && (codePeg[k] != guessPeg[k]) && (k > j) && !checked)
                    {
                        result += "~";
                        checked = true;
                    }
                }
            }
        }
    }
    return (bool) !result.compare("oooo");
}

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

    Peg()
    {
        SetColor(NOTHING);
    }

    inline void SetColor(COLOR color)
    {
        m_PegColor = color;
        switch (color)
        {
        case RED:    m_Color = al_map_rgb(255, 51, 51);   break;
        case BLUE:   m_Color = al_map_rgb(51, 51, 255);   break;
        case YELLOW: m_Color = al_map_rgb(255, 255, 102); break;
        case GREEN:  m_Color = al_map_rgb(51, 255, 153);  break;
        case WHITE:  m_Color = al_map_rgb(224, 224, 224); break;
        case ORANGE: m_Color = al_map_rgb(255, 153, 51);  break;
        case NOTHING:
        default:     m_Color = al_map_rgb(96, 96, 96);    break;
        }
    }

    inline void Render(unsigned int x, unsigned int y, unsigned int r)
    {
        al_draw_circle(x, y, r + 1.5f, al_map_rgb(0, 0, 0), 2.5f);
        al_draw_filled_circle(x, y, r, m_Color);
    }

    inline COLOR GetColor()
    {
        return m_PegColor;
    }

private:
    COLOR m_PegColor;
    ALLEGRO_COLOR m_Color;
};

class Row
{
public:
    Row(unsigned int x, unsigned int y, bool results)
        : m_x(x), m_y(y), m_Results(results)
    {
        m_Coords[0] = m_x;
        m_Coords[1] = m_Coords[0] + 56;
        m_Coords[2] = m_Coords[1] + 56;
        m_Coords[3] = m_Coords[2] + 56;

        if (m_Results)
        {
            for (unsigned int i = 0; i < 4; i++)
                m_PegCoords[i] = m_Coords[i] + 300;
        }
    }

    void Render()
    {
        for (unsigned int i = 0; i < 4; i++)
        {
            m_Pegs[i].Render(m_Coords[i], m_y, 20);
        }

        if (m_Results)
        {
            for (unsigned int i = 0; i < 4; i++)
            {
                m_ResultPegs[i].Render(m_PegCoords[i], m_y, 5);
            }
        }
    }

protected:
    Peg m_Pegs[4], m_ResultPegs[4];
    unsigned int m_x, m_y, m_Coords[4], m_PegCoords[8];
    bool m_Results;
};

class Input
{
public:
    Input(unsigned int x, unsigned int y)
        : m_x(x), m_y(y)
    {
        m_Coords[0] = m_x;
        m_Coords[1] = m_Coords[0] + 56;
        m_Coords[2] = m_Coords[1] + 56;
        m_Coords[3] = m_Coords[2] + 56;
        m_Coords[4] = m_Coords[3] + 56;
        m_Coords[5] = m_Coords[4] + 56;

        m_Pegs[0].SetColor(Peg::RED);
        m_Pegs[1].SetColor(Peg::BLUE);
        m_Pegs[2].SetColor(Peg::YELLOW);
        m_Pegs[3].SetColor(Peg::GREEN);
        m_Pegs[4].SetColor(Peg::WHITE);
        m_Pegs[5].SetColor(Peg::ORANGE);
    }

    Peg::COLOR Update(ALLEGRO_MOUSE_EVENT mouse)
    {
        if ((mouse.y <= m_y + 27) && (mouse.y >= m_y - 27))
        {
            for (unsigned int i = 0; i < 6; i++)
            {
                if ((mouse.x <= m_Coords[i] + 27) && (mouse.x >= m_Coords[i] - 27))
                    return m_Pegs[i].GetColor();
            }
        }
        return Peg::NOTHING;
    }

    void Render()
    {
        for (unsigned int i = 0; i < 6; i++)
        {
            m_Pegs[i].Render(m_Coords[i], m_y, 20);
        }
    }

private:
    Peg m_Pegs[6];
    unsigned int m_x, m_y, m_Coords[6];
};

class Button
{
public:
    Button(unsigned int x, unsigned int y, ALLEGRO_BITMAP* image)
        : m_x(x), m_y(y), m_BMP(image)
    { }

    bool Update(ALLEGRO_MOUSE_EVENT mouse)
    {
        return ((mouse.y <= m_y + 27) && (mouse.y >= m_y - 27) && (mouse.x <= m_x + 110) && (mouse.x >= m_x));
    }

    void Render()
    {
        al_draw_scaled_bitmap(
            m_BMP,
            0, 0,
            al_get_bitmap_width(m_BMP), al_get_bitmap_height(m_BMP),
            m_x, m_y,
            110, 50,
            0);
    }

private:
    unsigned int m_x, m_y;
    ALLEGRO_BITMAP* m_BMP;
};

class MasterMind
{
public:
    MasterMind(vector<Row> grid, Row solution, Button enter, Button backsp, Input input)
        : m_Grid(grid), m_Solution(solution), m_Enter(enter), m_Backspapce(backsp), m_Input(input) { m_State = COLLECTING; }

    void Update(ALLEGRO_MOUSE_EVENT mouse)
    {
        switch (m_Input.Update(mouse))
        {
        case Peg::RED:
            printf("red\n");
            break;
        case Peg::BLUE:
            printf("blue\n");
            break;
        case Peg::YELLOW:
            printf("yellow\n");
            break;
        case Peg::GREEN:
            printf("green\n");
            break;
        case Peg::WHITE:
            printf("white\n");
            break;
        case Peg::ORANGE:
            printf("orange\n");
            break;
        }
        if (m_Enter.Update(mouse))
        {
            printf("enter\n");
        }
        if (m_Backspapce.Update(mouse))
        {
            printf("backspace\n");
        }
    }

    void Render()
    {
        al_draw_bitmap(background, 0, 0, 0);
        al_draw_bitmap(border, 400, 30, 0);
        al_draw_text(century_gothic48B, al_map_rgb(255,255,255), SCREEN_W-355, 50, ALLEGRO_ALIGN_CENTRE, "Master Mind");
        al_draw_text(century_gothic48B, al_map_rgb(255,255,255), 200, 200, ALLEGRO_ALIGN_CENTRE, "Choose a Color");
        al_draw_text(century_gothic48B, al_map_rgb(255,255,255), 600, SCREEN_H-70, ALLEGRO_ALIGN_CENTRE, "Solution :");
        for (auto& x : m_Grid) x.Render();
        m_Solution.Render();
        m_Input.Render();
        m_Enter.Render();
        m_Backspapce.Render();
    }

private:
    typedef enum
    {
        COLLECTING,
        EVALUATING,
        FINSIHED,
    } STATE;

    vector<Row> m_Grid;
    Row m_Solution;
    Button m_Enter, m_Backspapce;
    Input m_Input;
    STATE m_State;
};

int main(int argc, char **argv)
{
    // Initialize
    if (!init()) return -1;

    // Create Game Objects
    vector<Row> Grid
    {
        Row(500, 140, true),
        Row(500, 196, true),
        Row(500, 252, true),
        Row(500, 308, true),
        Row(500, 364, true),
        Row(500, 420, true),
        Row(500, 476, true),
        Row(500, 532, true),
        Row(500, 588, true),
        Row(500, 645, true)
    };

    Row solution(750, SCREEN_H-38, false);
    Input input(65, 280);
    Button enter(85, 320, key_enter);
    Button backsc(210, 320, key_backspace);

    MasterMind master_mind(Grid, solution, enter, backsc, input);
    // Game Loop
    bool executing = true, render = false;
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
            master_mind.Update(event.mouse);
            break;
        }

        if (al_is_event_queue_empty(queue) && render)
        {
            al_clear_to_color(al_map_rgb(0,0,0));
            al_set_target_bitmap(al_get_backbuffer(display));
            master_mind.Render();
            al_flip_display();
        }
        render = false;
    }


    // De-initialization
    al_destroy_bitmap(background);
    al_destroy_display(display);
    return 0;
}

bool init()
{
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

    background = al_load_bitmap("res\\background.png");
    if (!background)
    {
        fprintf(stderr, "Failed load background image!\n");
        al_destroy_display(display);
        return false;
    }
    border = al_load_bitmap("res\\border.png");
    if (!border)
    {
        fprintf(stderr, "Failed load border image!\n");
        al_destroy_display(display);
        return false;
    }
    key_backspace = al_load_bitmap("res\\backspace.png");
    if (!key_backspace)
    {
        fprintf(stderr, "Failed load backspace image!\n");
        al_destroy_display(display);
        return false;
    }
    key_enter = al_load_bitmap("res\\enter.png");
    if (!key_enter)
    {
        fprintf(stderr, "Failed load enter image!\n");
        al_destroy_display(display);
        return false;
    }

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
