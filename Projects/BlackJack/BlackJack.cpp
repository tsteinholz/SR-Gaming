#include "BlackJack.h"

BlackJack::BlackJack() : _Deck() {
    _PlayerHand = new Hand(_Deck);
    _DealerHand = new Hand(_Deck);

    // todo : load bank
}

BlackJack::~BlackJack() {
    delete _PlayerHand;
    delete _DealerHand;
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
