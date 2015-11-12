#ifndef BLACK_JACK_DECK_H
#define BLACK_JACK_DECK_H

#include <vector>

#include "Card.h"

class Deck {
public:
    Deck();

    virtual ~Deck();

    typedef std::vector<Card> Cards;

protected:
private:
};

#endif // BLACK_JACK_DECK_H
