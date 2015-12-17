#include "Deck.h"

Deck::Deck()
{
    for (unsigned int s = 1; s < 4; s++)
    {
        for (unsigned int v = 0; v < 13; v++)
        {
            _Cards.push_back(new Card(Card::IntToSuit(s),Card::IntToValue(v)));
        }
    }
    Shuffle();
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
    for (Card *card : _Cards) {
        card->Played = false;
    }
}

Card *Deck::Draw() {
    Card *x;
    int timeout = 0;
    do {
        x = _Cards.at(rand() % _Cards.size());
        timeout++;
        if (timeout > 10) exit(-5);
    } while (x->Played);
    x->Played = true;
    return x;
}
