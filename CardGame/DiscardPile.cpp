#include "DiscardPile.h"
#include<iostream>
using namespace std;

DiscardPile::DiscardPile(std::istream& is, const CardFactory* cf) {
	// Get temp deck to get cards for restoring discard pile
	Deck tmp = cf->getDeck();
	string discardStr;
	getline(is, discardStr);

	for (char c : discardStr) {
		if (c != ' ') {
			for (Card* card : tmp) {
				char firstLetter = card->getName().at(0);
				if (firstLetter == c) {
					*this += card;
					break;
				}
			}
		}
	}
}

const DiscardPile& DiscardPile::operator+=(Card* card) {
	push_back(card);
	return *this;
}

const ostream& DiscardPile::operator<<(ostream& os) {
	if (!this->empty()) {
		const Card* topCard = back();
		os << topCard->getName() << endl;
	}
	else {
		os << endl;
	}
	return os;
}

Card* DiscardPile::pickUp() {
	Card* topCard = back();
	pop_back();
	return topCard;
}

Card* DiscardPile::top() {
	return back();
}

void DiscardPile::print(ostream& os) {
	for (Card* c : *this) {
		os << c->getName()[0] << " ";
	}
	os << endl;
}



