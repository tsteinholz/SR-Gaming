#ifndef BLACK_JACK_HAND_H
#define BLACK_JACK_HAND_H

#include "Deck.h"

class Hand
{
    public:
        Hand(Deck *deck);
        virtual ~Hand();

        ///////////////////////////////////////////////////////////////////////////////////////////////////
        // Purpose: Draw a card from a deck
        //
        ///////////////////////////////////////////////////////////////////////////////////////////////////
        void Draw();

        void Count();

        void Render(); 

    protected:
        Deck *_Deck;
};

#endif // BLACK_JACK_HAND_H
