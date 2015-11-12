#ifndef BLACK_JACK_CARD_H
#define BLACK_JACK_CARD_H

class Card
{
    public:
        Card();
        virtual ~Card();

        typedef enum
        {
            ACE   = 1,
            TWO   = 2,
            THREE = 3,
            FOUR  = 4,
            FIVE  = 5,
            SIX   = 6,
            SEVEN = 7,
            EIGHT = 8,
            NINE  = 9,
            TEN   = 10,
            JACK  = 11,
            QUEEN = 12,
            KING  = 13
        } Value;

        typedef enum
        {
            DIAMONDS,
            SPADES,
            CLUBS,
            HEARTS
        } Suit;

        /**
        * @returns Value of the Card
        */
        Value GetValue();

        /**
        * @returns Suit of the Card
        */
        Suit GetSuit();

    protected:
        char *_ImagePath;
        Value _Value;
        Suit _Suit;
};

#endif // BLACK_JACK_CARD_H
