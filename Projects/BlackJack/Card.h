#ifndef BLACK_JACK_CARD_H
#define BLACK_JACK_CARD_H

#include <algorithm>
#include <cstdio>
#include <unordered_map>
#include <string>
#include <vector>

#include <allegro5/drawing.h>

#include "util.h"

class Card {
public:
    
    //-----------------------------------------------------------------------------
    // Purpose: Cooresponds to the numeric value of the card as well as the
    // sequencial order that the cards appear in the image used to render the cards
    // themselfs
    //-----------------------------------------------------------------------------
    typedef enum {
        ACE   = 0,
        TWO   = 1,
        THREE = 2,
        FOUR  = 3,
        FIVE  = 4,
        SIX   = 5,
        SEVEN = 6,
        EIGHT = 7,
        NINE  = 8,
        TEN   = 9,
        JACK  = 10,
        QUEEN = 11,
        KING  = 12,
        V_ERROR
    } Value;

    //-----------------------------------------------------------------------------
    // Purpose: Cooresponding with the Value Enum, this enum has all the suits a
    // card has and is used to render the cards by enumerating the suits in order
    // of when they appear in the image they are rendered from.
    //-----------------------------------------------------------------------------
    typedef enum {
        CLUBS    = 0,
        DIAMONDS = 1,
        HEARTS   = 2,
        SPADES   = 3,
        BACK     = 4,
        S_ERROR
    } Suit;

    Card(Suit suit, Value val, int x = 0, int y = 0);

    virtual ~Card();

    //-----------------------------------------------------------------------------
    // Purpose: Renders the object, called once per draw tick
    //-----------------------------------------------------------------------------
    void Render();

    //-----------------------------------------------------------------------------
    // Purpose: returns Value of the Card
    //-----------------------------------------------------------------------------
    Value GetValue();

    //-----------------------------------------------------------------------------
    // Purpose: returns Suit of the Card
    //-----------------------------------------------------------------------------
    Suit GetSuit();

    //-----------------------------------------------------------------------------
    // Purpose: returns Suit Value as an integer
    //-----------------------------------------------------------------------------
    static Suit IntToSuit(unsigned int suit);

    //-----------------------------------------------------------------------------
    // Purpose: returns Value as an integer
    //-----------------------------------------------------------------------------
    static Value IntToValue(unsigned int value);

    //-----------------------------------------------------------------------------
    // Purpose: A simple typedef for a vector of card pointers
    //-----------------------------------------------------------------------------
    typedef std::vector<Card*> Cards;

    //-----------------------------------------------------------------------------
    // Purpose: A boolean value of if the card was used or not in the current deck
    //-----------------------------------------------------------------------------
    bool Played;

    //-----------------------------------------------------------------------------
    // Purpose : The location that the card will be rendered
    //-----------------------------------------------------------------------------
    int Coords[2];
protected: 
    Value _Value;
    Suit _Suit;
    
    ALLEGRO_BITMAP* _Card;

    static ALLEGRO_BITMAP* _Deck;
    static float _CardHeight;
    static float _CardWidth;
};

#endif // BLACK_JACK_CARD_H
