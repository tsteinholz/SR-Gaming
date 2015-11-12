#include "Card.h"

std::unordered_map<const char*, sf::Texture> Card::_Textures = std::unordered_map<const char*, sf::Texture>();

Card::Card(Suit suit, Value val) : _Suit(suit), _Value(val) {
    _ImagePath = _Suit + _Value + ".png";
    sf::Texture texture;
    if (!texture.loadFromFile(_ImagePath)) printf("Failed to load %s", _ImagePath.c_str());
    _Textures.insert(std::pair<const char*, sf::Texture>(_ImagePath.c_str(), texture));
}

Card::~Card() {
    //dtor
}

Card::Suit Card::GetSuit() {
    return _Suit;
}

Card::Value Card::GetValue() {
    return _Value;
}