#include "util.h"
#include "Deck.h"
#include "Hand.h"

ALLEGRO_DISPLAY *display = NULL;
ALLEGRO_EVENT_QUEUE *queue;
ALLEGRO_TIMER *timer;

const unsigned int SCREEN_W = 800, SCREEN_H = 600;

typedef enum
{
    MainMenu,
    Game,
    FinalMenu
} GameState;

GameState gameState = GameState::Game;

int main(int argc, char **argv)
{
    if (!init(display, SCREEN_W, SCREEN_H)) return -1;

    queue = al_create_event_queue();
    al_register_event_source(queue, al_get_keyboard_event_source());
    timer = al_create_timer(1.0 / 60);
    al_register_event_source(queue, al_get_timer_event_source(timer));
    al_start_timer(timer);

    bool executing = true;
    while (executing)
    {
        ALLEGRO_EVENT event;
        al_wait_for_event(queue, &event);

        switch(event.type)
        {
        case ALLEGRO_EVENT_DISPLAY_CLOSE:
            break;
        case ALLEGRO_EVENT_KEY_DOWN:
            if (event.keyboard.keycode == ALLEGRO_KEY_ESCAPE) executing = false;
            break;
        case ALLEGRO_EVENT_TIMER:
            break;
        }

        if (al_is_event_queue_empty(queue))
        {
            switch (gameState)
            {

            case GameState::MainMenu:
                break;
            case GameState::Game:
                break;
            case GameState::FinalMenu:
                break;

            }
            al_flip_display();
        }
    }
    al_destroy_display(display);
    return 0;
}
