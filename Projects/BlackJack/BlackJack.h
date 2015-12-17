#ifndef BLACK_JACK_H
#define BLACK_JACK_H

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_physfs.h>
#include <allegro5/allegro_ttf.h>

#include "Hand.h"
#include "Deck.h"

class BlackJack {

public:
    
    BlackJack(ALLEGRO_FONT **fonts1, ALLEGRO_FONT **fonts2);

    virtual ~BlackJack();

    //-----------------------------------------------------------------------------
    // Purpose: To keep track of the current state of the game and to execute
    // everything else accordingly
    //-----------------------------------------------------------------------------
    typedef enum {
        SETUP,
        INPUT,
        COMPUTE,
        FINISH
    } Mode;

    //-----------------------------------------------------------------------------
    // Purpose: To define the state of the current round in refrence to a win or a
    // loss (maybe somewhere in between)
    //-----------------------------------------------------------------------------
    typedef enum {
        UNKNOWN,
        WIN,
        LOSS,
        TIE,
    } Outcome;

    //-----------------------------------------------------------------------------
    // Purpose: Renders BlackJack
    //-----------------------------------------------------------------------------
    void Render();
    
    //-----------------------------------------------------------------------------
    // Purpose: Called whenever user input (that we care about) is inputed so that
    // the game itself can process it accordingly and efficiently
    //-----------------------------------------------------------------------------
    void Update(ALLEGRO_EVENT *event);

    //-----------------------------------------------------------------------------
    // Purpose: TODO
    //-----------------------------------------------------------------------------
    bool Executing;

protected:
    Mode _CurrentMode;
    Hand *_PlayerHand;
    Hand *_DealerHand;
    Deck *_Deck;
    Card *_CardBack;

    ALLEGRO_BITMAP *_Button;
    ALLEGRO_FONT *_Font1[7];
    ALLEGRO_FONT *_Font2[7];
    float _Bank;
    Outcome _Outcome;
    bool _left_button_active;
    bool _right_button_active;
    bool _Holding;
};

#endif // BLACK_JACK_H
