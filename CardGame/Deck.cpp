#include <iostream>
#include "Deck.h"

using namespace std;

ostream& Deck::operator<<(ostream& os) {
	for (Card* c : *this) {
		os << c->getName()[0] << " ";
	}
	os << endl;
	return os;
}

Card* Deck::draw() {
	Card* drawnCard = back();
	pop_back();
	return drawnCard;
}