#include "Hand.h"

Hand::Hand(Deck *deck) : _Deck(deck) {
	
}

Hand::~Hand() {
    //dtor
}

void Hand::Draw() {

}

int Hand::Count() {
	int count = 0, aces = 0;
	for (Card *card : _Cards) {
		if (card->GetValue() == Card::ACE) aces++;
		count += card->GetValue();
	}
	while (aces > 0) {
		
		if (11 + count < 21)
			count += 11;
		else
			count++;
		
		aces--;
	}
}
