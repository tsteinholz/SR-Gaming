#ifndef BLACK_JACK_H
#define BLACK_JACK_H

#include "Hand.h"
#include "Deck.h"

class BlackJack {

public:
    
    BlackJack();
    virtual ~BlackJack();

    typedef enum {
        SETUP,
        INPUT,
        COMPUTE,
        FINISH
    } Mode;

    void Render();
    
    void Tick();

protected:
    Mode _CurrentMode;
    Hand *_PlayerHand;
    Hand *_DealerHand;
    Deck *_Deck;
    unsigned int _Bank;
};
#endif // BLACK_JACK_H
