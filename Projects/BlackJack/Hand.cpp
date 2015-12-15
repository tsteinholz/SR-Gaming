#include "Hand.h"

Hand::Hand(Deck *deck) : _Deck(deck) {

}

Hand::~Hand() {
    //dtor
}

void Hand::Render() {
    // TODO
    unsigned int offset = (unsigned int) (Card::CardWidth + 0);
    unsigned int length = (unsigned int) (_Cards.size() * offset);
    unsigned int x = (900 / 2) - (length / 2);
    for (unsigned long i = 0; i < _Cards.size(); i++) {
        Card *c = _Cards.at(i);
        c->Coords[0] = x;
        c->Coords[1] = 350;
        c->Render();
        x+=50;//offset;
        //printf("width %f\n",Card::CardWidth);
    }
}

void Hand::Draw() {
	_Cards.push_back(_Deck->Draw());
}

int Hand::Count() {
	int count = 0, aces = 0;
	for (Card *card : _Cards) {
		if (card->GetValue() == Card::ACE)
            aces++;
        else
            count += (card->GetValue() + 1);
	}
	while (aces > 0) {
		
		if (11 + count < 21)
			count += 11;
		else
			count++;
		
		aces--;
	}
    return count;
}
