#include "BlackJack.h"

BlackJack::BlackJack() : _Deck() {
    _PlayerHand = new Hand(_Deck);
    _DealerHand = new Hand(_Deck);
    _Button = Util::LoadB("res/border.png");

    // todo : load bank
    _Bank = 0;
    _CurrentMode = INPUT;
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
            al_draw_bitmap(_Button, 100, 100, 0);
            //al_draw_text(_CofeeTin[2], al_map_rgb(218,204,0), 150, 390, ALLEGRO_ALIGN_CENTRE, "HIT");
            al_draw_bitmap(_Button, 200, 200, 0);
            break;
        case COMPUTE:

            break;
        case FINISH:

            break;
    }

}

void BlackJack::Update() {

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
