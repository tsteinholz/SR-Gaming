#ifndef BLACK_JACK_HAND_H
#define BLACK_JACK_HAND_H

#include "Deck.h"

class Hand
{
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

    protected:
        Deck *_Deck;
        Card::Cards _Cards;
};

#endif // BLACK_JACK_HAND_H
