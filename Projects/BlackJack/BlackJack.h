#ifndef BLACK_JACK_H
#define BLACK_JACK_H

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

#include "Hand.h"
#include "Deck.h"

class BlackJack {

public:
    
    BlackJack();

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
    // Purpose: Renders BlackJack
    //-----------------------------------------------------------------------------
    void Render();
    
    //-----------------------------------------------------------------------------
    // Purpose: Called whenever user input (that we care about) is inputed so that
    // the game itself can process it accordingly and efficiently
    //-----------------------------------------------------------------------------
    void Update();

    //-----------------------------------------------------------------------------
    // Purpose:
    //-----------------------------------------------------------------------------
    void Hit();

    //-----------------------------------------------------------------------------
    // Purpose:
    //-----------------------------------------------------------------------------
    void Hold();

protected:
    Mode _CurrentMode;
    Hand *_PlayerHand;
    Hand *_DealerHand;
    Deck *_Deck;

    ALLEGRO_BITMAP *_Button;

    unsigned int _Bank;
};

#endif // BLACK_JACK_H
