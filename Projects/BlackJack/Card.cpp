#include "Card.h"

ALLEGRO_BITMAP* Card::_Deck = Util::LoadB("res/cards.png");
//float Card::_CardWidth = al_get_bitmap_width(_Deck) / 13;
//float Card::_CardHeight = al_get_bitmap_height(_Deck) / 5;

Card::Card(Suit suit, Value val) : _Suit(suit), _Value(val), _Played(false) {

    //blit(_Deck, _Card, value * _CardWidth, suit * _CardHeight, 0, 0, _CardWidth, _CardHeight);

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
