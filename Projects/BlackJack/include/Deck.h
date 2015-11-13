#ifndef BLACK_JACK_DECK_H
#define BLACK_JACK_DECK_H

#include <algorithm>
#include <vector>

#include "Card.h"

class Deck {
public:
    Deck();

    virtual ~Deck();

    typedef std::vector<Card> Cards;

    void Shuffle();

protected:
    Cards _Cards;
private:
};

#endif // BLACK_JACK_DECK_H
