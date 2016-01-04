#ifndef BLACK_JACK_H
#define BLACK_JACK_H

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_physfs.h>
#include <allegro5/allegro_ttf.h>

#include "Hand.h"
#include "Deck.h"

//-----------------------------------------------------------------------------
// Purpose: The game class for blackjack that manages everything inside the
// game itself. This class has it's own state system that has the implementation
// to stop the game completely.
//-----------------------------------------------------------------------------
class BlackJack {
public:

    BlackJack(ALLEGRO_FONT **fonts1, ALLEGRO_FONT **fonts2);

    virtual ~BlackJack();

    //-----------------------------------------------------------------------------
    // Purpose: To keep track of the current state of the game and to execute
    // everything else accordingly
    //-----------------------------------------------------------------------------
    typedef enum {
        SETUP,
        INPUT,
        COMPUTE,
        FINISH
    } Mode;

    //-----------------------------------------------------------------------------
    // Purpose: To define the state of the current round in reference to a win or a
    // loss (maybe somewhere in between)
    //-----------------------------------------------------------------------------
    typedef enum {
        UNKNOWN,
        WIN,
        LOSS,
        TIE,
    } Outcome;

    //-----------------------------------------------------------------------------
    // Purpose: Renders BlackJack
    //-----------------------------------------------------------------------------
    void Render();

    //-----------------------------------------------------------------------------
    // Purpose: Called whenever user input (that we care about) is inputed so that
    // the game itself can process it accordingly and efficiently
    //-----------------------------------------------------------------------------
    void Update(ALLEGRO_EVENT *event);

    void Hit();

    void Hold();

    void Compute();

    //-----------------------------------------------------------------------------
    // Purpose: If the game is executing or not, used to close down the entire
    // game if appropriate.
    //-----------------------------------------------------------------------------
    bool Executing;

protected:
    Mode _CurrentMode;          // The mode of the game
    Hand *_PlayerHand;          // The player's hand
    Hand *_DealerHand;          // The dealer's hand
    Deck *_Deck;                // The Deck the game will use
    Card *_CardBack;            // A Generic Image for rendering the back of a card

    ALLEGRO_BITMAP *_Button;    // An Image for my lazy button implementation
    ALLEGRO_FONT *_Font1[7];    // A Font used for everything in the game
    ALLEGRO_FONT *_Font2[7];    // A Font used for everything in the game

    bool _left_button_active;   // Lazy button implementation
    bool _right_button_active;  // Lazy button implementation
    bool _Holding;              // If the player is holding or if he is not

    float _Bank;                // The Player's bank account amount
    float _Bet;                 // The amount the bank is paying
    Outcome _Outcome;           // The outcome of the current round
    char *_Conclusion;          // The conclusion statment
};

#endif // BLACK_JACK_H
