#ifndef BLACK_JACK_HAND_H
#define BLACK_JACK_HAND_H

#include "Deck.h"

//-----------------------------------------------------------------------------
// Purpose: Represents a hand in blackjack. Contains an array of cards and a
// pointer to the deck it is drawing from, so two hands can actually share one
// Deck.
//-----------------------------------------------------------------------------
class Hand {
public:

    Hand(Deck *deck);

    virtual ~Hand();

    //-----------------------------------------------------------------------------
    // Render all the cards in the hand on screen and shape them accordingly
    //-----------------------------------------------------------------------------
    void Render();

    //-----------------------------------------------------------------------------
    // Purpose: Draw a card from a deck and add it to the hand
    //-----------------------------------------------------------------------------
    void Draw();

    //-----------------------------------------------------------------------------
    // Purpose : Count the cards to get their value to see where they are from 0-21
    //-----------------------------------------------------------------------------
    int Count();

    //-----------------------------------------------------------------------------
    // Purpose: Rest the Hand for a new round
    //-----------------------------------------------------------------------------
    void Reset();

    //-----------------------------------------------------------------------------
    // Purpose: The Y value where the hand will be rendered
    //-----------------------------------------------------------------------------
    int Y;

protected:
    //-----------------------------------------------------------------------------
    // Purpose: Pointer to the deck the hand takes it's cards from
    //-----------------------------------------------------------------------------
    Deck *_Deck;

    //-----------------------------------------------------------------------------
    // Purpose: Where we want to store the hand's cards
    //-----------------------------------------------------------------------------
    Card::Cards _Cards;
};

#endif // BLACK_JACK_HAND_H
