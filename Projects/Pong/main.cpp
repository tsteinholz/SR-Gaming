// Thomas Alexander Steinholz
// South River High School
// C++ w/ Gaming : 1A

#include <allegro5/allegro.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

#include <sstream>
#include <stdio.h>

typedef enum
{
    Menu,
    Description,
    Game,
    Conclusion,
} Gamemode;

/*
TODO :

Fix AI...
    [x] bounds on max and min
    [] not triggering movement when ball if above AI in negative coord space
    [x] smoothness

[~] Get sound working (different instances or whatever)
[x] Start menu ( check paper for info )
[x] working with buttons
[] fix escape -> conclusion page
[x] implement game (play to 10 points then end screen prompting stats, restart to main menu, and quit)
[x] figure out how to distribute Pong.exe (fix the compiler)
*/


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

int main()
{
    const int SCREEN_W = 1280, SCREEN_H = 768;

    ALLEGRO_DISPLAY *display = NULL;

    ALLEGRO_EVENT_QUEUE* queue;

    ALLEGRO_FONT* century_gothic40;
    ALLEGRO_FONT* century_gothic24;

    ALLEGRO_BITMAP* MenuBackground;
    ALLEGRO_BITMAP* ArenaBackground;
    ALLEGRO_BITMAP* Ball;

    ALLEGRO_SAMPLE* BackgroundMusic;
    ALLEGRO_SAMPLE* Boop;
    ALLEGRO_SAMPLE* Score;
    ALLEGRO_SAMPLE* Intro;

    ALLEGRO_TIMER* timer;

    Gamemode gamemode = Menu;

    std::string player_text = "PLAYER : 0", ai_text = "BOT : 0";
    unsigned int player_score = 0, ai_score = 0;

    if(!al_init())
    {
        printf("al_init Failed!\n");
        return -1;
    }
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
        printf("al_init_primitives_addon Failed!\n");
        return -1;
    }
    display = al_create_display(SCREEN_W, SCREEN_H);

    if(!display)
    {
        printf("al_create_display Failed!\n");
        return -1;
    }

    srand(time(NULL));

    al_init_font_addon();
    al_init_ttf_addon();
    al_install_keyboard();
    al_init_image_addon();

    queue = al_create_event_queue();
    timer = al_create_timer(1.0 / 60);

    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_mouse_event_source());
    al_register_event_source(queue, al_get_display_event_source(display));
    al_register_event_source(queue, al_get_timer_event_source(timer));

    al_start_timer(timer);

    century_gothic40  = al_load_ttf_font("C:\\Windows\\Fonts\\GOTHIC.TTF" , 40, ALLEGRO_ALIGN_CENTRE);
    century_gothic24  = al_load_ttf_font("C:\\Windows\\Fonts\\GOTHIC.TTF" , 24, ALLEGRO_ALIGN_CENTRE);

    MenuBackground = LoadB("res\\menu.png");
    ArenaBackground = LoadB("res\\arena.png");
    Ball = LoadB("res\\ball.png");

    BackgroundMusic = LoadS("res\\rain.wav");
    Boop = LoadS("res\\boop.ogg");
    Score = LoadS("res\\score.wav");
    Intro = LoadS("res\\intro.ogg");

    ALLEGRO_VOICE *audioDevice = al_create_voice(44100,  ALLEGRO_AUDIO_DEPTH_FLOAT32 , ALLEGRO_CHANNEL_CONF_2);
    ALLEGRO_MIXER *mixerMaster = al_create_mixer(44100,  ALLEGRO_AUDIO_DEPTH_FLOAT32 , ALLEGRO_CHANNEL_CONF_2);
    ALLEGRO_MIXER *mixerMusic = al_create_mixer(44100,  ALLEGRO_AUDIO_DEPTH_FLOAT32 , ALLEGRO_CHANNEL_CONF_2);
    ALLEGRO_MIXER *mixerSounds = al_create_mixer(44100,  ALLEGRO_AUDIO_DEPTH_FLOAT32 , ALLEGRO_CHANNEL_CONF_2);

    if (audioDevice == NULL || mixerMaster == NULL || mixerMusic == NULL || mixerSounds == NULL)
    {
        printf("Failed to start audio devices");
    }

/*  Attempt of Audio
    al_attach_sample_instance_to_mixer(Boop, mixerSounds);
    al_attach_sample_instance_to_mixer(BackgroundMusic, mixerMusic);
    al_attach_sample_instance_to_mixer(Score, mixerSounds);
    al_attach_sample_instance_to_mixer(Intro, mixerSounds);

    al_attach_mixer_to_mixer(mixerMusic, mixerMaster);
    al_attach_mixer_to_mixer(mixerSounds, mixerMaster);
    al_attach_mixer_to_voice(mixerMaster, audioDevice);

    //ALLEGRO_SAMPLE_INSTANCE BoopI = al_create_sample_instance(Boop);
    //ALLEGRO_SAMPLE_INSTANCE ScoreI = al_create_sample_instance(Score);
    //al_play_sample(BackgroundMusic, 1.0, 0.0,1.0,ALLEGRO_PLAYMODE_LOOP,NULL);*/

    float player_y = 0, player_y_vel = 0,
          ai_y_vel = 0, ai_y = 0,
          ball_x = (SCREEN_W/2)-12, ball_x_vel = (rand() % 2) ? 5 : -5,
          ball_y = (SCREEN_H/2)-15, ball_y_vel = 0,
          multiplier = 1;

    bool render , scored, executing = true;
    al_play_sample(Intro, 1.0, 0.0,1.0,ALLEGRO_PLAYMODE_ONCE,NULL);
    while (executing)
    {
        ALLEGRO_EVENT event;
        al_wait_for_event(queue, &event);
        switch(event.type)
        {
        case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
            switch (gamemode)
            {
            case Menu:
                if ((event.mouse.x >= (SCREEN_W / 2) - 150) && (event.mouse.x <= (SCREEN_W / 2) + 150))
                {
                    if ((event.mouse.y >= 205) && (event.mouse.y <= 280))
                    {
                        gamemode = Game;
                    }
                    else if ((event.mouse.y >= 305) && (event.mouse.y <= 380))
                    {
                        gamemode = Description;
                    }
                    else if ((event.mouse.y >= 405) && (event.mouse.y <= 480))
                    {
                        executing = false;
                    }
                }
                break;
            case Description:

                break;
            case Conclusion:
                if ((event.mouse.x >= (SCREEN_W/2)-150) && (event.mouse.x <= (SCREEN_W/2)+150))
                {
                    if ((event.mouse.y >= 305) && (event.mouse.y <= 380))
                    {
                        player_score = ai_score = player_y = player_y_vel = ai_y_vel = ai_y = ball_y_vel = 0;
                        ball_x_vel = (rand() % 2) ? 5 : -5;
                        ball_x = (SCREEN_W / 2) - 12;
                        ball_y = (SCREEN_H / 2) - 15;
                        multiplier = 1;
                        player_text = "PLAYER : 0";
                        ai_text = "BOT : 0";
                        gamemode = Menu;
                    }
                    else if ((event.mouse.y >= 405) && (event.mouse.y <= 480))
                    {
                        executing = false;
                    }
                }
                break;
            }
            break;
        case ALLEGRO_EVENT_DISPLAY_CLOSE:
            executing = false;
            break;
        case ALLEGRO_EVENT_KEY_DOWN:
            switch(event.keyboard.keycode)
            {
            case ALLEGRO_KEY_ESCAPE:
                switch (gamemode)
                {
                case Game:
                    executing = false;
                    break;
                }
                break;
            case ALLEGRO_KEY_UP:
            case ALLEGRO_KEY_W:
                player_y_vel = -10;
                break;
            case ALLEGRO_KEY_DOWN:
            case ALLEGRO_KEY_S:
                player_y_vel = 10;
                break;
            case ALLEGRO_KEY_ENTER:
                executing = false;
                break;
            }
            gamemode = Game;
            break;
        case ALLEGRO_EVENT_KEY_UP:
            player_y_vel = 0;
            break;
        case ALLEGRO_EVENT_TIMER:
            render = true;
            switch(gamemode)
            {
            case Game:
                // Scoring
                bool scored = false;
                if (ball_x >= SCREEN_W)
                {
                    player_score++;
                    scored = true;
                    std::stringstream ss;
                    ss << "PLAYER : " << player_score;
                    player_text = ss.str();
                }
                if (ball_x <= 0)
                {
                    ai_score++;
                    scored = true;
                    std::stringstream ss;
                    ss << "BOT : " << ai_score;
                    ai_text = ss.str();
                }
                if (scored)
                {
                    al_play_sample(Score, 1.0, 0.0,1.0,ALLEGRO_PLAYMODE_ONCE,NULL);
                    //al_play_sample_instance(ScoreI);
                    ball_x = (SCREEN_W/2)-12;
                    ball_y = (SCREEN_H/2)-15;
                    ball_x_vel = (rand() % 2) ? 5.75 : -5.75;
                    ball_y_vel = 0;
                    ai_y = 0;
                    player_y = 0;
                    multiplier = 1;
                }
                // Collision
                if (((((SCREEN_H/2)-50)+player_y)<=0)&&(player_y_vel<0)) player_y_vel = 0;
                if (((((SCREEN_H/2)+50)+player_y)>=SCREEN_H)&&(player_y_vel>0)) player_y_vel = 0;
                if ((ball_y <= 0) || (ball_y >= SCREEN_H)) ball_y_vel = -ball_y_vel;
                if (((ball_y <= (((SCREEN_H / 2) + 50) + player_y) && (ball_y >= (((SCREEN_H / 2) - 50) + player_y))) && ((ball_x <= 90) && (ball_x >= 75))) || (((ball_y <= (((SCREEN_H / 2) + 50) + ai_y)) && (ball_y >= (((SCREEN_H / 2) - 50) + ai_y))) && (((ball_x >= SCREEN_W - 110)) && (ball_x <= SCREEN_W - 75))))
                {
                    //al_play_sample(Boop, 1.0, 0.0,1.0,ALLEGRO_PLAYMODE_ONCE,NULL);
                    //al_play_sample_instance(BoopI);
                    ball_x_vel = -ball_x_vel * multiplier;
                    multiplier += 0.005f;
                    ball_y_vel = (rand() % 10) - 5;
                }
                // AI
                if (ball_x_vel > 0)                                                 // Ball comming towards AI
                {
                    if ((ai_y <= 340) && (ai_y >= -340))                              // AI is in game bounds
                    {
                        if ((SCREEN_H/2)+ai_y < ball_y) ai_y_vel = abs(ball_y_vel) < 3 ? abs(ball_y_vel) : 5;
                        else if ((SCREEN_H/2)+ai_y == ball_y) ai_y_vel = 0;
                        else ai_y_vel = abs(ball_y_vel) < 3 ? -abs(ball_y_vel) : -5;
                    }
                    else if (ai_y >  340) ai_y_vel = -3;
                    else if (ai_y < -340) ai_y_vel = 3;
                    else ai_y_vel = 0;
                }
                else                                                                 // Go towards center
                {
                    if (ai_y > 10) ai_y_vel = -1;
                    else if (ai_y < 10) ai_y_vel = 1;
                    else ai_y_vel = 0;
                }
                // Movement
                player_y += player_y_vel;
                ai_y += ai_y_vel;
                ball_x += ball_x_vel;
                ball_y += ball_y_vel;
                if (player_score >= 10 || ai_score >= 10) gamemode = Conclusion;
                break;
            }
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
                al_draw_text(century_gothic40, al_map_rgb(250,250,250), SCREEN_W/2, 40, ALLEGRO_ALIGN_CENTRE, "Ultimate Pong");
                al_draw_rectangle((SCREEN_W / 2) - 150, 205, (SCREEN_W / 2) + 150, 280, al_map_rgb(255, 255, 255), 3);
                al_draw_text(century_gothic40, al_map_rgb(250, 250, 250), SCREEN_W / 2, 220, ALLEGRO_ALIGN_CENTRE, "Play");
                al_draw_rectangle((SCREEN_W / 2) - 150, 305, (SCREEN_W / 2) + 150, 380, al_map_rgb(255, 255, 255), 3);
                al_draw_text(century_gothic40, al_map_rgb(250, 250, 250), SCREEN_W / 2, 320, ALLEGRO_ALIGN_CENTRE, "About");
                al_draw_rectangle((SCREEN_W / 2) - 150, 405, (SCREEN_W / 2) + 150, 480, al_map_rgb(255, 255, 255), 3);
                al_draw_text(century_gothic40, al_map_rgb(250, 250, 250), SCREEN_W / 2, 420, ALLEGRO_ALIGN_CENTRE, "Quit");
                al_draw_text(century_gothic24, al_map_rgb(250,250,250), 200, SCREEN_H - 50, ALLEGRO_ALIGN_CENTRE, "Game by Thomas Steinholz");

                break;
            case Description:
                al_draw_bitmap(MenuBackground, 0, 0, 0);
                al_draw_text(century_gothic40, al_map_rgb(250, 250, 250), SCREEN_W / 2, 40, ALLEGRO_ALIGN_CENTRE, "About Ultimate Pong");
                al_draw_text(century_gothic24, al_map_rgb(250,250,250), 100, 240, ALLEGRO_ALIGN_LEFT, "This is the game of Ultimate Pong! The game consists of 2 paddles knocking a ball back and");
                al_draw_text(century_gothic24, al_map_rgb(250,250,250), 100, 260, ALLEGRO_ALIGN_LEFT, "forth until one misses it and it goes into the goal. The point of the game is to score 10 ");
                al_draw_text(century_gothic24, al_map_rgb(250,250,250), 100, 280, ALLEGRO_ALIGN_LEFT, "points. You can score a point by getting the ball in the other player's goal (right behind");
                al_draw_text(century_gothic24, al_map_rgb(250,250,250), 100, 300, ALLEGRO_ALIGN_LEFT, "the enemy paddle). You control the game by using either the UP and DOWN arrow or the W and");
                al_draw_text(century_gothic24, al_map_rgb(250,250,250), 100, 320, ALLEGRO_ALIGN_LEFT, "S key. As you can guess, the up arrow brings your player up while the down arrow brings   ");
                al_draw_text(century_gothic24, al_map_rgb(250,250,250), 100, 340, ALLEGRO_ALIGN_LEFT, "your player down. The W key functions the same as the UP arrow as the S key functions the");
                al_draw_text(century_gothic24, al_map_rgb(250,250,250), 100, 360, ALLEGRO_ALIGN_LEFT, "same as the DOWN key. The game ends once either the player of AI has reached a point value");
                al_draw_text(century_gothic24, al_map_rgb(250,250,250), 100, 380, ALLEGRO_ALIGN_LEFT, "of 10. You play as the left paddle and the AI plays as the right paddle. You can see the  ");
                al_draw_text(century_gothic24, al_map_rgb(250,250,250), 100, 400, ALLEGRO_ALIGN_LEFT, "corresponding scores above the side you play as if you get lost or confused. To get       ");
                al_draw_text(century_gothic24, al_map_rgb(250,250,250), 100, 420, ALLEGRO_ALIGN_LEFT, "started, hit the ESC button. DISCLAIMER : IF YOU GET HURT, ITS NOT PONGS FAULT SO DONT SUE");
                al_draw_text(century_gothic24, al_map_rgb(250,250,250), 200, SCREEN_H - 50, ALLEGRO_ALIGN_CENTRE, "PRESS sESC TO PLAY");

                break;
            case Game:
                al_draw_bitmap(ArenaBackground, 0, 0, 0);
                al_draw_line((SCREEN_W/2)-3,0,(SCREEN_W/2)-3,SCREEN_H,al_map_rgb(255,255,255), 2);
                al_draw_circle((SCREEN_W/2)-5,(SCREEN_H/2)-5, 150, al_map_rgb(255,255,255), 2);
                al_draw_filled_rectangle(75,((SCREEN_H/2)-50)+player_y,90,((SCREEN_H/2)+50)+player_y,al_map_rgb(255,255,255));              //Player
                al_draw_filled_rectangle(SCREEN_W-75,((SCREEN_H/2)-50)+ai_y,SCREEN_W-90,((SCREEN_H/2)+50)+ai_y,al_map_rgb(255,255,255));    //AI
                al_draw_scaled_bitmap(
                    Ball,
                    0, 0,
                    al_get_bitmap_width(Ball), al_get_bitmap_height(Ball),
                    ball_x, ball_y,
                    15, 15,
                    0);
                al_draw_text(century_gothic40, al_map_rgb(250,250,250), 140, 40, ALLEGRO_ALIGN_CENTRE, player_text.c_str());
                al_draw_text(century_gothic40, al_map_rgb(250,250,250), SCREEN_W-100, 40, ALLEGRO_ALIGN_CENTRE, ai_text.c_str());
                break;
            case Conclusion:
                al_draw_bitmap(MenuBackground, 0, 0, 0);
                al_draw_text(century_gothic40, al_map_rgb(250, 250, 250), SCREEN_W / 2, 40, ALLEGRO_ALIGN_CENTRE, "Game Over!");
                al_draw_text(century_gothic40, al_map_rgb(250, 250, 250), SCREEN_W / 2, 80, ALLEGRO_ALIGN_CENTRE, ai_score < player_score ? "You Win!" : "You Lose!");
                al_draw_textf(century_gothic40, al_map_rgb(250, 250, 250), SCREEN_W / 2, 120, ALLEGRO_ALIGN_CENTRE, "%d : %d", player_score, ai_score);
                al_draw_rectangle((SCREEN_W/2)-150, 305, (SCREEN_W/2)+150, 380, al_map_rgb(255, 255, 255), 3);
                al_draw_text(century_gothic40, al_map_rgb(250, 250, 250), SCREEN_W / 2, 320, ALLEGRO_ALIGN_CENTRE, "Restart");
                al_draw_rectangle((SCREEN_W / 2) - 150, 405, (SCREEN_W / 2) + 150, 480, al_map_rgb(255, 255, 255), 3);
                al_draw_text(century_gothic40, al_map_rgb(250, 250, 250), SCREEN_W / 2, 420, ALLEGRO_ALIGN_CENTRE, "Quit");
                break;
            }

            ////////////////////////////////////////////////////////////////////
            al_flip_display();
        }
        render = false;
    }

    al_destroy_bitmap(MenuBackground);
    al_destroy_bitmap(ArenaBackground);
    al_destroy_bitmap(Ball);
    al_destroy_sample(BackgroundMusic);
    al_destroy_sample(Boop);
    al_destroy_sample(Score);
    al_destroy_display(display);

    return 0;
}
