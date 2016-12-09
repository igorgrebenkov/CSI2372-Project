#include "TradeArea.h"
#include <iostream>

TradeArea::TradeArea(istream& is, const CardFactory* cf) {
	string tradeStr;
	getline(is, tradeStr);

	// Get temp deck we can use to reconstruct TradeArea from file
	Deck tmp = cf->getDeck();

	for (char c : tradeStr) {
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

TradeArea::~TradeArea() {
	for (Card* c : *this) {
		delete c;
	}
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

