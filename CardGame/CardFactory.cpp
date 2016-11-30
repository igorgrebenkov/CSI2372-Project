#include "CardFactory.h"
#include "Card.h"
#include<vector>

using namespace std;

CardFactory::CardFactory() {
	
	deck.push_back(createCard("Quartz"));
}

const CardFactory* CardFactory::getFactory() {
	static CardFactory cardFactory;
	return &cardFactory;
}

const Deck CardFactory::getDeck() const {
	return deck;
}

Card* CardFactory::createCard(const string &name) {
	if (name == "Quartz") {
		return new Quartz(name);
	}
}
