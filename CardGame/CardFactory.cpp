#include<vector>
#include <iostream>
#include <algorithm>
#include <random>
#include <chrono>

#include "CardFactory.h"

#define NUM_CARD_TYPES 7
#define NUM_CARDS 104
#define NUM_QUARTZ 20
#define NUM_HEMATITE 18
#define NUM_OBSIDIAN 16
#define NUM_MALACHITE 14
#define NUM_TURQUOISE 12
#define NUM_RUBY 10
#define NUM_AMETHYST 8
#define NUM_EMERALD 6

using namespace std;

CardFactory::CardFactory() {
	for (int i = 0; i < NUM_QUARTZ; i++) {
		deck.push_back(createCard("Quartz"));
	}
	for (int i = 0; i < NUM_HEMATITE; i++) {
		deck.push_back(createCard("Hematite"));
	}
	for (int i = 0; i < NUM_OBSIDIAN; i++) {
		deck.push_back(createCard("Obsidian"));
	}
	for (int i = 0; i < NUM_MALACHITE; i++) {
		deck.push_back(createCard("Malachite"));
	}
	for (int i = 0; i < NUM_TURQUOISE; i++) {
		deck.push_back(createCard("Turquoise"));
	}
	for (int i = 0; i < NUM_RUBY; i++) {
		deck.push_back(createCard("Ruby"));
	}
	for (int i = 0; i < NUM_AMETHYST; i++) {
		deck.push_back(createCard("Amethyst"));
	}
	for (int i = 0; i < NUM_EMERALD; i++) {
		deck.push_back(createCard("Emerald"));
	}

	// generates a seed based on the current time for random shuffle
	unsigned seed = chrono::system_clock::now().time_since_epoch().count();
	shuffle(begin(deck), end(deck), default_random_engine(seed));
}

const CardFactory* CardFactory::getFactory() {
	static CardFactory* cardFactory = new CardFactory();
	return cardFactory;
}

Deck CardFactory::getDeck() const {
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
	else {
		return new Emerald(name);
	}
}
