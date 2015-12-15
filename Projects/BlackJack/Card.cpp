#include "Card.h"

ALLEGRO_BITMAP* Card::_Deck = NULL;
float Card::CardWidth = 0;
float Card::CardHeight = 0;

Card::Card(Suit suit, Value val, int x, int y) : _Suit(suit), _Value(val), Played(false) {
	if (!_Deck) Card::_Deck = Util::LoadB("res/cards.png");
	Card::CardWidth = al_get_bitmap_width(_Deck) / 13;
	Card::CardHeight = al_get_bitmap_height(_Deck) / 5;
	Coords[0] = x;
	Coords[1] = y;
}

Card::~Card() {

}

Card::Suit Card::GetSuit() {
    return _Suit;
}

Card::Value Card::GetValue() {
    return _Value;
}

Card::Suit Card::IntToSuit(unsigned int suit) {
    switch (suit) {

        case DIAMONDS: return DIAMONDS;
        case SPADES:   return SPADES;
        case CLUBS:    return CLUBS;
        case HEARTS:   return HEARTS;
        default:       return S_ERROR;

    }
}

Card::Value Card::IntToValue(unsigned int value) {
    switch (value) {

        case ACE:   return ACE;
        case TWO:   return TWO;
        case THREE: return THREE;
        case FOUR:  return FOUR;
        case FIVE:  return FIVE;
        case SIX:   return SIX;
        case SEVEN: return SEVEN;
        case EIGHT: return EIGHT;
        case NINE:  return NINE;
        case TEN:   return TEN;
        case JACK:  return JACK;
        case QUEEN: return QUEEN;
        case KING:  return KING;
        default:    return V_ERROR;
    }
}

void Card::Render() {
    al_draw_bitmap_region(_Deck, _Value * CardWidth, _Suit * CardHeight,
                          CardWidth, CardHeight, Coords[0] - (CardWidth / 2), Coords[1] - (CardHeight / 2), 0);
    //al_draw_rectangle(Coords[0], Coords[1], Coords[0], Coords[1], al_map_rgb(255,0,0), 3);//debug
}
