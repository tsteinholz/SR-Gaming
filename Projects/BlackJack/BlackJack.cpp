#include "BlackJack.h"

BlackJack::BlackJack() : _PlayerHand(), _DealerHand(), _Deck() {

}

BlackJack::~BlackJack() {

}

void BlackJack::Render() 
{
 
    switch (_CurrentMode) {
        case SETUP:
            break;
        case INPUT:
            break;
        case COMPUTE:
            break;
        case FINISH:
            break;
    }

}

void BlackJack::Tick() {

}
