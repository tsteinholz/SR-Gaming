#ifndef BLACK_JACK_DECK_H
#define BLACK_JACK_DECK_H

#include <vector>

#include "Cards.h"

class Deck
{
    public:
        Deck();
        virtual ~Deck();

        typedef std::vector<Cards> Cards;

    protected:
    private:
};

#endif // BLACK_JACK_DECK_H
