#ifndef BLACK_JACK_CARD_H
#define BLACK_JACK_CARD_H

#include <SFML/Graphics.hpp>

#include <cstdio>
#include <unordered_map>
#include <string>

class Card {
public:
    typedef enum {
        ACE = 1,
        TWO = 2,
        THREE = 3,
        FOUR = 4,
        FIVE = 5,
        SIX = 6,
        SEVEN = 7,
        EIGHT = 8,
        NINE = 9,
        TEN = 10,
        JACK = 11,
        QUEEN = 12,
        KING = 13,
    } Value;

    typedef enum {
        DIAMONDS = 0,
        SPADES = 1,
        CLUBS = 2,
        HEARTS = 3,
    } Suit;

    Card(Suit suit, Value val);

    virtual ~Card();

    /**
    * @returns Value of the Card
    */
    Value GetValue();

    /**
    * @returns Suit of the Card
    */
    Suit GetSuit();

protected:
    static std::unordered_map<const char*, sf::Texture> _Textures;
    std::string _ImagePath;
    Value _Value;
    Suit _Suit;
};

#endif // BLACK_JACK_CARD_H
