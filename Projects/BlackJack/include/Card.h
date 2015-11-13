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
    static sf::Texture _SpriteSheet;
    sf::Vector2u _ImageCoordinates;
    sf::Sprite _Card;
    Value _Value;
    Suit _Suit;
    bool _Played;
};

#endif // BLACK_JACK_CARD_H
