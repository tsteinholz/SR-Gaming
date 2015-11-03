// Thomas Alexander Steinholz
// South River High School
// C++ w/ Gaming : 1A

#include <iostream>
#include <ctime>
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
const int SCREEN_W = 1080, SCREEN_H = 824;

using namespace std;

bool init();

struct Peg
{
public:
    typedef enum
    {
        RED = 0xCF2104,
        BLUE = 0x3F00FF,
        YELLOW = 0xBAFF1E,
        GREEN = 0x117050,
        WHITE = 0xFFFFFF,
        ORANGE = 0xC65104,
        GREY = 0xBBBBBB,
        BLACK = 0x000000,
        NOTHING = 0x554E44,
    } COLOR;

    Peg() : UsedForHint(false), UsedForMatch(false)
    {
        SetColor(NOTHING);
    }

    inline void SetColor(COLOR color)
    {
        m_PegColor = color;
        switch (color)
        {
        case RED:    m_Color = al_map_rgb(255, 51,  51);   break;
        case BLUE:   m_Color = al_map_rgb(51,  51,  255);  break;
        case YELLOW: m_Color = al_map_rgb(255, 255, 102);  break;
        case GREEN:  m_Color = al_map_rgb(51,  255, 153);  break;
        case WHITE:  m_Color = al_map_rgb(224, 224, 224);  break;
        case ORANGE: m_Color = al_map_rgb(255, 153, 51);   break;
        case GREY:   m_Color = al_map_rgb(175, 175, 175);  break;
        case BLACK:  m_Color = al_map_rgb(15 , 15 , 15 );  break;
        case NOTHING:
        default:     m_Color = al_map_rgb(96,  96,  96);   break;
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

    bool operator==(const Peg &other) const
    {
        return (m_PegColor == other.m_PegColor);
    }

    bool operator!=(const Peg &other) const {
        return !(*this == other);
    }

    inline void ResetCheck()
    {
        UsedForHint = false;
        UsedForMatch = false;
    }

    bool UsedForHint;
    bool UsedForMatch;

private:
    COLOR m_PegColor;
    ALLEGRO_COLOR m_Color;
};

struct Code
{
    Code()
    {
        Peg temp[4];
        for(int i = 0; i < 4; i++)
        {
            switch(rand() % 6)
            {
                case 0:  temp[i].SetColor(Peg::RED);     break;
                case 1:  temp[i].SetColor(Peg::BLUE);    break;
                case 2:  temp[i].SetColor(Peg::YELLOW);  break;
                case 3:  temp[i].SetColor(Peg::GREEN);   break;
                case 4:  temp[i].SetColor(Peg::WHITE);   break;
                case 5:  temp[i].SetColor(Peg::ORANGE);  break;
                default: temp[i].SetColor(Peg::NOTHING); break;
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
        return A.GetColor() != Peg::NOTHING &&
               B.GetColor() != Peg::NOTHING &&
               C.GetColor() != Peg::NOTHING &&
               D.GetColor() != Peg::NOTHING;
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
    Peg codePeg[4] = {code->A, code->B, code->C, code->D}, guessPeg[4]= {guess->A, guess->B, guess->C, guess->D};

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

    inline Peg GetPeg(int index)
    {
        return m_Pegs[index];
    }

    inline Peg GetResult(int index)
    {
        return m_ResultPegs[index];
    }

    inline void SetPeg(int index, Peg::COLOR color)
    {
        m_Pegs[index].SetColor(color);
    }

    inline void SetResult(int index, Peg::COLOR color)
    {
        m_ResultPegs[index].SetColor(color);
    }

    inline void SetRandomPegs()
    {
        for (int i = 0; i < 4; i++)
        {
            switch (rand() % 6)
            {
            case 0:  m_Pegs[i].SetColor(Peg::RED);     break;
            case 1:  m_Pegs[i].SetColor(Peg::BLUE);    break;
            case 2:  m_Pegs[i].SetColor(Peg::YELLOW);  break;
            case 3:  m_Pegs[i].SetColor(Peg::GREEN);   break;
            case 4:  m_Pegs[i].SetColor(Peg::WHITE);   break;
            case 5:  m_Pegs[i].SetColor(Peg::ORANGE);  break;
            }
        }
    }

    inline void ResetCheck()
    {
        for (auto& x : m_Pegs)
        {
            x.ResetCheck();
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
        if ((mouse.y <= (int) m_y + 27) && (mouse.y >= (int) m_y - 27))
        {
            for (unsigned int i = 0; i < 6; i++)
            {
                if ((mouse.x <= (int) m_Coords[i] + 27) && (mouse.x >= (int) m_Coords[i] - 27))
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
        return ((mouse.y <= (int) m_y + 27) && (mouse.y >= (int) m_y - 27) && (mouse.x <= (int) m_x + 110) && (mouse.x >= (int) m_x));
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
        : m_Grid(grid), m_Solution(solution), m_Enter(enter), m_Backspapce(backsp), m_Input(input) , m_Blank(750, SCREEN_H - 38, false)
        {
            m_CurrentPosX = 0;
            m_CurrentPosY = 0;
            playing = true;
            m_Solution.SetRandomPegs();
            won = false;
        }

    void Update(ALLEGRO_MOUSE_EVENT mouse)
    {
        if (playing)
        {
            Peg::COLOR temp = m_Input.Update(mouse);
            if (temp != Peg::NOTHING && m_CurrentPosX < 4) m_Grid.at(m_CurrentPosY).SetPeg(m_CurrentPosX++, temp);

            if (m_Enter.Update(mouse))
            {
                if (m_CurrentPosY >= 9 && m_CurrentPosX >= 4) { playing = false; }
                if (m_CurrentPosX >= 4)
                {
                    for (int i = 0; i < 4; i ++) //go through each user inputed value
                    {
                        if ((m_Grid.at(m_CurrentPosY).GetPeg(i) == m_Solution.GetPeg(i)) && !m_Solution.GetPeg(i).UsedForMatch)
                        {
                            m_Solution.SetResult(i, Peg::WHITE);
                            m_Solution.GetPeg(i).UsedForMatch = true;
                        }
                        else
                        {
                            for (int j = 1; j < 4; j++)
                            {
                                if ((m_Grid.at(m_CurrentPosY).GetPeg(i) == m_Solution.GetPeg(j)) && !m_Solution.GetPeg(j).UsedForHint)
                                {
                                    m_Solution.GetPeg(j).UsedForHint = true;
                                    m_Solution.SetResult(i, Peg::BLACK);
                                }
                            }
                        }
                    }

//////////////////////////////////////////////////////////////////////////////////////////////////

                    bool checked;
                    std::string result = "";
                    for (int i = 0; i < 4; i++)
                    {
                        for (int j = i; j < 4; j++)
                        {
                            checked = false;
                            if (m_Grid.at(m_CurrentPosY).GetPeg(i) == m_Solution.GetPeg(j))
                            {
                                if (i == j)
                                {
                                    result += "o";
                                    checked = true;
                                }
                            }
                            else
                            {
                                for (int k = i + 1; k < 4; k++)
                                {
                                    if ((m_Grid.at(m_CurrentPosY).GetPeg(k) == m_Solution.GetPeg(j)) && (m_Grid.at(m_CurrentPosY).GetPeg(k) != m_Solution.GetPeg(k) && (k > j) && !checked))
                                    {
                                        result += "~";
                                        checked = true;
                                    }
                                }
                            }
                        }
                    }
                    printf(result.c_str());
                    int count = 0;
                    for (auto& x : result)
                    {
                        switch (result.at(count))
                        {
                        case 'o':
                            m_Grid.at(m_CurrentPosY).SetResult(count, Peg::WHITE);
                            break;
                        case '~':
                            m_Grid.at(m_CurrentPosY).SetResult(count, Peg::BLACK);
                            break;
                        }
                        count++;
                    }
                    m_CurrentPosY++;
                    m_CurrentPosX = 0;
                    if (!result.compare("oooo")) { playing = false; won = true; Render(); }
                }
                printf("enter\n");//debug
            }
            if (m_Backspapce.Update(mouse))
            {
                if (m_CurrentPosX > 0)
                {
                    m_CurrentPosX--;
                    m_Grid.at(m_CurrentPosY).SetPeg(m_CurrentPosX, Peg::NOTHING);
                }
                printf("backspace\n");//debug
            }
        }
        else
        {

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
        //if (playing) m_Blank.Render();
        /*else*/ m_Solution.Render();
        m_Input.Render();
        m_Enter.Render();
        m_Backspapce.Render();
    }

private:
    vector<Row> m_Grid;
    Row m_Solution, m_Blank;
    Button m_Enter, m_Backspapce;
    Input m_Input;

    int m_CurrentPosX, m_CurrentPosY;
    bool playing, won;
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
    al_destroy_bitmap(border);
    al_destroy_bitmap(key_enter);
    al_destroy_bitmap(key_backspace);
    al_destroy_display(display);
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
