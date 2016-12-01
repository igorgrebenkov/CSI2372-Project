#pragma once
#include "Card.h"
#include "Deck.h"

class CardFactory {
public:
	const static CardFactory* getFactory();
	Deck getDeck() const;
private:
	Deck deck;
	CardFactory();
	Card* createCard(const string &cardName);
};
