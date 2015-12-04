#ifndef BLACK_JACK_CARD_H
#define BLACK_JACK_CARD_H

#include <cstdio>
#include <unordered_map>
#include <string>

#include <allegro5/drawing.h>

#include "util.h"


class Card {
public:
    typedef enum {
        ACE = 0,
        TWO = 1,
        THREE = 2,
        FOUR = 3,
        FIVE = 4,
        SIX = 5,
        SEVEN = 6,
        EIGHT = 7,
        NINE = 8,
        TEN = 9,
        JACK = 10,
        QUEEN = 11,
        KING = 12,
        V_ERROR
    } Value;

    typedef enum {
        CLUBS = 0,
        DIAMONDS = 1,
        HEARTS = 2,
        SPADES = 3,
        S_ERROR
    } Suit;

    Card(Suit suit, Value val);

    virtual ~Card();

    /**
     * Updates the object start, called once per tick
     */
    void Update();

    /**
     * Renders the object, called once per draw tick
     */
    void Render();

    /**
    * @returns Value of the Card
    */
    Value GetValue();

    /**
    * @returns Suit of the Card
    */
    Suit GetSuit();

    /**
     * @returns Suit Value as an integer
     */
    static Suit IntToSuit(unsigned int suit);

    /**
     * @returns Value as an integer
     */
    static Value IntToValue(unsigned int value);

protected:
    Value _Value;
    Suit _Suit;
    bool _Played;
    static ALLEGRO_BITMAP* _Deck;
    static float _CardHeight;
    static float _CardWidth;
    ALLEGRO_BITMAP* _Card;
};

#endif // BLACK_JACK_CARD_H
