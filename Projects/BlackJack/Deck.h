#ifndef BLACK_JACK_DECK_H
#define BLACK_JACK_DECK_H

#include "Card.h"

//-----------------------------------------------------------------------------
// Purpose: Represents a full deck of cards, nothing else, only the full deck
// of cards with one of each card.
//-----------------------------------------------------------------------------
class Deck {
public:
    Deck();

    virtual ~Deck();

	//-----------------------------------------------------------------------------
	// Purpose: Shuffles the deck
    //-----------------------------------------------------------------------------
    void Shuffle();

    //-----------------------------------------------------------------------------
    // Purpose: Draw a random card from the deck
    //
    // returns the drawn card
    //-----------------------------------------------------------------------------
    Card *Draw();

protected:
    Card::Cards _Cards;
private:
};

#endif // BLACK_JACK_DECK_H
