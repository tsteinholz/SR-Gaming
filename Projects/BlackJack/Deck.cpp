#include "Deck.h"

Deck::Deck()
{
    for (unsigned int s = 1; s < 5; s++)
    {
        for (unsigned int v = 1; v < 14; v++)
        {
            _Cards.push_back(Card(Card::IntToSuit(s),Card::IntToValue(v)));
        }
    }
    Shuffle();
}

Deck::~Deck()
{
    //dtor
}

void Deck::Shuffle()
{
    std::random_shuffle(_Cards.begin(), _Cards.end());
}
