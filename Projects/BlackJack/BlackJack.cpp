#include "BlackJack.h"

BlackJack::BlackJack(ALLEGRO_FONT **fonts1, ALLEGRO_FONT **fonts2) : Executing(true) {
    _Deck = new Deck();
    _PlayerHand = new Hand(_Deck);
    _DealerHand = new Hand(_Deck);
    _DealerHand->Y = 75;
    _CardBack = new Card(Card::BACK, Card::ACE, 75, 225);
    _Button = Util::LoadB("res/border.png");
    _left_button_active = false;
    _right_button_active = false;
    _Holding = false;
    _Outcome = UNKNOWN;

    for (int i = 0; i < 7; i++) {
        _Font1[i] = fonts1[i];
        _Font2[i] = fonts2[i];
    }

    // todo : load bank
    _Bank = Util::LoadFloat("Bank.txt");
    _Bet = 0;
    _Conclusion = (char *) "";
    _CurrentMode = SETUP;
}

BlackJack::~BlackJack() {
    delete _Deck;
    delete _PlayerHand;
    delete _DealerHand;
    delete _CardBack;
}

void BlackJack::Render() {
    switch (_CurrentMode) {
        case SETUP:
        case INPUT:
            // Card Stack
            for (int i = 0; i < 4; i++) {
                int offset = 3;
                _CardBack->Coords[0] += offset;
                _CardBack->Coords[1] += offset;
                _CardBack->Render();
            }
            // Dealers Hand
            _CardBack->Coords[0] = 415;
            _CardBack->Coords[1] = 75;
            _DealerHand->Render();
            _CardBack->Render();
            // Reset Card Stack
            _CardBack->Coords[0] = 75;
            _CardBack->Coords[1] = 225;

            // Button Hold
            al_draw_scaled_bitmap(_Button, 0, 0, al_get_bitmap_width(_Button), al_get_bitmap_height(_Button), 75, 50,
                                  125, 75, 0);
            al_draw_text(_Font1[2], al_map_rgb(218, 204, 0), 135, 75, ALLEGRO_ALIGN_CENTRE, "H O L D");
            if (_left_button_active) al_draw_rectangle(75, 50, 75 + 125, 50 + 75, al_map_rgb(255, 255, 0), 3);

            // Button Hit
            al_draw_scaled_bitmap(_Button, 0, 0, al_get_bitmap_width(_Button), al_get_bitmap_height(_Button), 700, 50,
                                  125, 75, 0);
            al_draw_text(_Font1[2], al_map_rgb(218, 204, 0), 760, 75, ALLEGRO_ALIGN_CENTRE, "H I T");
            if (_right_button_active) al_draw_rectangle(700, 50, 700 + 125, 50 + 75, al_map_rgb(255, 255, 0), 3);

            // Bank Account Money
            al_draw_textf(_Font2[2], al_map_rgb(218, 204, 0), 450, 525, ALLEGRO_ALIGN_CENTRE,
                          "BANK ACCOUNT CONTAINS $%.2f", _Bank);
            // Player Hand Count
            al_draw_textf(_Font2[2], al_map_rgb(218, 204, 0), 100, 500, ALLEGRO_ALIGN_CENTRE, "CARD TOTAL IS %i",
                          _PlayerHand->Count());

            // Player Hand
            _PlayerHand->Render();

            break;
        case FINISH:

            // Card Stack
            for (int i = 0; i < 4; i++) {
                int offset = 3;
                _CardBack->Coords[0] += offset;
                _CardBack->Coords[1] += offset;
                _CardBack->Render();
            }
            _CardBack->Coords[0] = 75;
            _CardBack->Coords[1] = 225;

            // Button New
            al_draw_scaled_bitmap(_Button, 0, 0, al_get_bitmap_width(_Button), al_get_bitmap_height(_Button), 75, 50,
                                  125, 75, 0);
            al_draw_text(_Font1[2], al_map_rgb(218, 204, 0), 135, 75, ALLEGRO_ALIGN_CENTRE, "N E W");
            if (_left_button_active) al_draw_rectangle(75, 50, 75 + 125, 50 + 75, al_map_rgb(255, 255, 0), 3);

            // Button Quit
            al_draw_scaled_bitmap(_Button, 0, 0, al_get_bitmap_width(_Button), al_get_bitmap_height(_Button), 700, 50,
                                  125, 75, 0);
            al_draw_text(_Font1[2], al_map_rgb(218, 204, 0), 760, 75, ALLEGRO_ALIGN_CENTRE, "Q U I T");
            if (_right_button_active) al_draw_rectangle(700, 50, 700 + 125, 50 + 75, al_map_rgb(255, 255, 0), 3);

            // Conclusion
            al_draw_textf(_Font1[5], al_map_rgb(218, 204, 0), 450, 225, ALLEGRO_ALIGN_CENTRE, _Conclusion);

            // Bank Account Money
            al_draw_textf(_Font2[2], al_map_rgb(218, 204, 0), 450, 525, ALLEGRO_ALIGN_CENTRE,
                          "BANK ACCOUNT CONTAINS $%.2f", _Bank);
            // Player Hand Count
            al_draw_textf(_Font2[2], al_map_rgb(218, 204, 0), 100, 500, ALLEGRO_ALIGN_CENTRE, "CARD TOTAL IS %i",
                          _PlayerHand->Count());

            // Player Hand
            _PlayerHand->Render();
            // Dealer Hand
            _DealerHand->Render();
            break;
    }
}

void BlackJack::Update(ALLEGRO_EVENT *event) {

    switch (_CurrentMode) {
        case SETUP:
            // TODO : Bug fix, 2nd restart crashes game
            //printf("debug: enter setup\n");
            _Conclusion = (char *) "";
            _Bet = 0;
            _Deck->Shuffle();
            _PlayerHand->Reset();
            _DealerHand->Reset();
            for (unsigned int i = 0; i < 2; i++) {
                _PlayerHand->Draw();
            }
            _DealerHand->Draw();
            _Outcome = UNKNOWN;
            _Holding = false;
            //printf("debug: enter input\n");
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
                    Hold();
                    _left_button_active = false;
                }
                else if (_right_button_active) {
                    Hit();
                    _right_button_active = false;
                }
            }
        case COMPUTE:
            if (_PlayerHand->Count() > 21) {
                Compute();
            } else {
                if (_Holding)
                    Compute();
                else
                    _CurrentMode = INPUT;
            }
            break;
        case FINISH:
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
                    //printf("debug: \'new\' button pressed\n");
                    _left_button_active = false;
                    _right_button_active = false;
                    //printf("debug: new round\n");
                    _CurrentMode = SETUP;

                } else if (_right_button_active) {
                    //printf("debug: \'quit\' button pressed\n");
                    Executing = false;
                    break;
                }
            }
            break;
    }
}

void BlackJack::Hit() {
    //printf("debug: \'hit\' button pressed\n");
    _PlayerHand->Draw();
    //printf("debug: Enter Compute State\n");
    _CurrentMode = COMPUTE;
}

void BlackJack::Hold() {
    //printf("debug: \'hold\' button pressed\n");
    _Holding = true;
    _CurrentMode = COMPUTE;
    //printf("Enter Finish State\n");
    _CurrentMode = FINISH;
}

void BlackJack::Compute() {
    while (_DealerHand->Count() <= 15) {
        _DealerHand->Draw();
    }

    //printf("debug: players hand is %i\n", _PlayerHand->Count());
    //printf("debug: dealers hand is %i\n", _DealerHand->Count());

    if (_PlayerHand->Count() <= 21) {
        if (_PlayerHand->Count() > _DealerHand->Count()) _Outcome = WIN;        // Player Wins
        else if (_PlayerHand->Count() == _DealerHand->Count()) _Outcome = TIE;  // Tie
        else if (_DealerHand->Count() > 21) _Outcome = WIN;                     // Dealer Busted
        else _Outcome = LOSS;                                                   // Dealer Beat Player
    } else _Outcome = LOSS;                                                     // Bust

    switch (_Outcome) {

        case WIN:
            //printf("debug: win\n");
            _Bank += (2 * _Bet);
            _Conclusion = (char *) "YOU WIN";
            break;
        case LOSS:
            _Bank -= _Bet;
            _Conclusion = (char *) "YOU LOSE";
            //printf("debug: loss\n");
            break;
        case TIE:
            _Conclusion = (char *) "TIE";
            //printf("debug: tie\n");
            break;
        case UNKNOWN:
            _Conclusion = (char *) "UNKOWN";
            //printf("debug: unknown!?\n");
            break;

    }
    // TODO : save bank to file
    _CurrentMode = FINISH;
}
