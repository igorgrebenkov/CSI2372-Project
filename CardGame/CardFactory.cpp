#include<vector>
#include <algorithm>
#include<random>

#include "CardFactory.h"
#include "Card.h"


#define NUM_CARD_TYPES 7
#define NUM_CARDS 104

using namespace std;

CardFactory::CardFactory() {
	for (int i = 0; i < 20; i++) {
		deck.push_back(createCard("Quartz"));
	}
	for (int i = 0; i < 18; i++) {
		deck.push_back(createCard("Hematite"));
	}
	for (int i = 0; i < 16; i++) {
		deck.push_back(createCard("Obsidian"));
	}
	for (int i = 0; i < 14; i++) {
		deck.push_back(createCard("Malachite"));
	}
	for (int i = 0; i < 12; i++) {
		deck.push_back(createCard("Turquoise"));
	}
	for (int i = 0; i < 10; i++) {
		deck.push_back(createCard("Ruby"));
	}
	for (int i = 0; i < 8; i++) {
		deck.push_back(createCard("Amethyst"));
	}
	for (int i = 0; i < 6; i++) {
		deck.push_back(createCard("Emerald"));
	}
	//auto engine = default_random_engine{};
	//shuffle(begin(deck), end(deck), engine);
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
	else if (name == "Hematite") {
		return new Hematite(name);
	}
	else if (name == "Obsidian") {
		return new Obsidian(name);
	}
	else if (name == "Malachite") {
		return new Malachite(name);
	}
	else if (name == "Turquoise") {
		return new Turquoise(name);
	}
	else if (name == "Ruby") {
		return new Ruby(name);
	}
	else if (name == "Amethyst") {
		return new Amethyst(name);
	}
	else if (name == "Emerald") {
		return new Emerald(name);
	}
}
