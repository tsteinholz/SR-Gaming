#include "BlackJack.h"

BlackJack::BlackJack(ALLEGRO_FONT **fonts1,ALLEGRO_FONT **fonts2) {
    _Deck = new Deck();
    _PlayerHand = new Hand(_Deck);
    _DealerHand = new Hand(_Deck);
    _CardBack = new Card(Card::BACK, Card::ACE, 450, 75);
    _Button = Util::LoadB("res/border.png");
    _left_button_active = false;
    _right_button_active = false;

    for (int i = 0; i < 7; i++) {
        _Font1[i] = fonts1[i];
        _Font2[i] = fonts2[i];
    }

    // todo : load bank
    _Bank = 2000;
    _CurrentMode = SETUP;
}

BlackJack::~BlackJack() {
    delete _Deck;
    delete _PlayerHand;
    delete _DealerHand;
    delete _CardBack;
}

void BlackJack::Render() 
{
    for (int i = 0; i < 4; i++) {
        int offset = 3;
        _CardBack->Coords[0] += offset;
        _CardBack->Coords[1] += offset;
        _CardBack->Render();
    }
    _CardBack->Coords[0] = 450;
    _CardBack->Coords[1] = 75;

    al_draw_scaled_bitmap(_Button, 0, 0, al_get_bitmap_width(_Button), al_get_bitmap_height(_Button), 75, 50, 125, 75, 0);
    al_draw_text(_Font1[2], al_map_rgb(218,204,0), 135, 75, ALLEGRO_ALIGN_CENTRE, "H O L D");
    if (_left_button_active) al_draw_rectangle(75, 50, 75 + 125, 50 + 75, al_map_rgb(255,255,0), 3);
    al_draw_scaled_bitmap(_Button, 0, 0, al_get_bitmap_width(_Button), al_get_bitmap_height(_Button), 700, 50, 125, 75, 0);
    al_draw_text(_Font1[2], al_map_rgb(218,204,0), 760, 75, ALLEGRO_ALIGN_CENTRE, "H I T");
    if (_right_button_active) al_draw_rectangle(700, 50, 700 + 125, 50 + 75, al_map_rgb(255,255,0), 3);
    
    al_draw_textf(_Font2[2], al_map_rgb(218,204,0), 450, 525, ALLEGRO_ALIGN_CENTRE, "BANK ACCOUNT CONTAINS $%.2f", _Bank);
    al_draw_textf(_Font2[2], al_map_rgb(218,204,0), 100, 500, ALLEGRO_ALIGN_CENTRE, "CARD TOTAL IS %i", _PlayerHand->Count());

    _PlayerHand->Render();

}

void BlackJack::Update(ALLEGRO_EVENT *event) {

    switch (_CurrentMode) {
        case SETUP:
            _PlayerHand->Draw();
            _PlayerHand->Draw();
            _CurrentMode = INPUT;
            break;
        case INPUT:
            if (event->type == ALLEGRO_EVENT_MOUSE_AXES) {
                if (event->mouse.y >= 50 && event->mouse.y <= 50 + 75) {
                    if (event->mouse.x >= 75 && event->mouse.x <= 75 + 125) {
                        _left_button_active = true;
                    } else if (event->mouse.x >= 700 && event->mouse.x <= 700 + 125) {
                        _right_button_active = true;
                    } else { //reset x dir
                        _left_button_active = false;
                        _right_button_active = false;
                    }
                } else { // reset y dir
                    _left_button_active = false;
                    _right_button_active = false;
                }
            }
            if (event->type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
                if (_left_button_active) {
                    _CurrentMode = COMPUTE;
                } else if (_right_button_active) {
                    _PlayerHand->Draw();
                    // todo : check if bust
                }
            }
            break;
        case COMPUTE:

            break;
        case FINISH:
        
            break;
    }
}
