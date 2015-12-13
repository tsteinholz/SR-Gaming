#include "Deck.h"

Deck::Deck()
{
    for (unsigned int s = 1; s < 5; s++)
    {
        for (unsigned int v = 1; v < 14; v++)
        {
            _Cards.push_back(new Card(Card::IntToSuit(s),Card::IntToValue(v)));
        }
    }
    Shuffle();
    printf("size of cars: %lu", _Cards.size());
}

Deck::~Deck()
{
    for (Card *card : _Cards) {
        delete card;
    }
    _Cards.clear();
}

void Deck::Shuffle()
{
    std::random_shuffle(_Cards.begin(), _Cards.end());
}

Card *Deck::Draw() {
    //unsigned long rndindex = rand() % _Cards.size();
    Card *x = _Cards.at(rand() % _Cards.size());
    x->Played = true;
    return x;
}
