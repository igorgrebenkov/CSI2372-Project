#include "TradeArea.h"

TradeArea::TradeArea(istream& os, const CardFactory* cf) {

}

const TradeArea& TradeArea::operator+=(Card* card) {
	push_back(card);
	return *this;
}

const ostream& TradeArea::operator<<(ostream& os) {
	for (const Card* c : *this) {
		os << c->getName()[0] << " ";
	}
	os << endl;
	return os;
}

bool TradeArea::legal(Card* card) {
	bool hasCard = false;
	for (const Card* c : *this) {
		if (*card == *c) {
			hasCard = true;
		}
	}
	return hasCard;
}

const Card* TradeArea::trade(string s) {
	const Card* tradedCard = NULL;
	for (Card* c : *this) {
		if (c->getName() == s) {
			tradedCard = c;
			remove(c);
		}
	}
	return tradedCard;
}
int TradeArea::numCards() {
	return size();
}
