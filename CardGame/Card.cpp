#include "Card.h"
using namespace std;

/*************** Quartz Class Member Functions ***************/
int Quartz::getCardsPerCoin(const int& coins) const {
	switch (coins) {
		case 1:
			return 4;
			break;
		case 2:
			return 6;
			break;
		case 3:
			return 8;
			break;
		case 4:
			return 10;
			break;
		default:
			return 0;
			break;
	}
}

string Quartz::getName() const {
	return cardName;
}

void Quartz::print(ostream& out) const {
	out << cardName[0] << endl;
}

/*************** Hematite Class Member Functions ***************/
int Hematite::getCardsPerCoin(const int& coins) const {
	switch (coins) {
		case 1:
			return 3;
			break;
		case 2:
			return 6;
			break;
		case 3:
			return 8;
			break;
		case 4:
			return 9;
			break;
		default:
			return 0;
			break;
	}
}

string Hematite::getName() const {
	return cardName;
}

void Hematite::print(ostream& out) const {
	out << cardName[0] << endl;
}

/*************** Obsidian Class Member Functions ***************/
int Obsidian::getCardsPerCoin(const int& coins) const {
	switch (coins) {
		case 1:
			return 3;
			break;
		case 2:
			return 5;
			break;
		case 3:
			return 7;
			break;
		case 4:
			return 8;
			break;
		default:
			return 0;
			break;
	}
}

string Obsidian::getName() const {
	return cardName;
}

void Obsidian::print(ostream& out) const {
	out << cardName[0] << endl;
}

/*************** Malachite Class Member Functions ***************/
int Malachite::getCardsPerCoin(const int& coins) const {
	switch (coins) {
		case 1:
			return 3;
			break;
		case 2:
			return 5;
			break;
		case 3:
			return 6;
			break;
		case 4:
			return 7;
			break;
		default:
			return 0;
			break;
	}
}

string Malachite::getName() const {
	return cardName;
}

void Malachite::print(ostream& out) const {
	out << cardName[0] << endl;
}

/*************** Turquoise Class Member Functions ***************/
int Turquoise::getCardsPerCoin(const int& coins) const {
	switch (coins) {
		case 1:
			return 2;
			break;
		case 2:
			return 4;
			break;
		case 3:
			return 6;
			break;
		case 4:
			return 7;
			break;
		default:
			return 0;
			break;
	}
}

string Turquoise::getName() const {
	return cardName;
}

void Turquoise::print(ostream& out) const {
	out << cardName[0] << endl;
}

/*************** Ruby Class Member Functions ***************/
int Ruby::getCardsPerCoin(const int& coins) const {
	switch (coins) {
		case 1:
			return 2;
			break;
		case 2:
			return 4;
			break;
		case 3:
			return 5;
			break;
		case 4:
			return 6;
			break;
		default:
			return 0;
			break;
	}
}

string Ruby::getName() const {
	return cardName;
}

void Ruby::print(ostream& out) const {
	out << cardName[0] << endl;
}

/*************** Amethyst Class Member Functions ***************/
int Amethyst::getCardsPerCoin(const int& coins) const {
	switch (coins) {
		case 1:
			return 2;
			break;
		case 2:
			return 3;
			break;
		case 3:
			return 4;
			break;
		case 4:
			return 5;
			break;
		default:
			return 0;
			break;
	}
}

string Amethyst::getName() const {
	return cardName;
}

void Amethyst::print(ostream& out) const {
	out << cardName[0] << endl;
}

/*************** Emerald Class Member Functions ***************/
int Emerald::getCardsPerCoin(const int& coins) const {
	switch (coins) {
		case 2:
			return 2;
			break;
		case 3:
			return 3;
			break;
		default:
			return 0;
			break;
	}
}

string Emerald::getName() const {
	return cardName;
}

void Emerald::print(ostream& out) const {
	out << cardName[0] << endl;
}



