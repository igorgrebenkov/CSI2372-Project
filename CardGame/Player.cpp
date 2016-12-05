#include <iostream>
#include <string>
#include "Player.h"

using namespace std;

Player::Player(const string& s) : name(s), numCoins(0),
chainTypes{ " ", " ", "empty" } {
	chains = new vector<Chain_Base*>();
	chains->push_back(new Chain_Base());
	chains->push_back(new Chain_Base());
	chains->push_back(new Chain_Base());

	hand = new Hand();
}


const Player& Player::operator+=(int i) {
	numCoins += i;
	return *this;
}

ostream& Player::operator<<(std::ostream& os) const {
	os.width(12);
	os << left << name <<
	left << numCoins << " coins" << endl;

	for (int i = 0; i < 3; i++) {
		string chainType = chainTypes[i];
		Chain_Base* chain = (*chains)[i];
		switch (chainType.at(0)) {
			case 'Q': {
				Chain<Quartz*>* q = static_cast<Chain<Quartz*>*> (chain);
				*q << cout;
			}
					  break;
			case 'H': {
				Chain<Hematite*>* h = static_cast<Chain<Hematite*>*> (chain);
				*h << cout;
			}
					  break;
			case 'O': {
				Chain<Obsidian*>* o = static_cast<Chain<Obsidian*>*> (chain);
				*o << cout;
			}
					  break;
			case 'M': {
				Chain<Malachite*>* m = static_cast<Chain<Malachite*>*> (chain);
				*m << cout;
			}
					  break;
			case 'T': {
				Chain<Turquoise*>* t = static_cast<Chain<Turquoise*>*> (chain);
				*t << cout;
			}
					  break;
			case 'R': {
				Chain<Ruby*>* r = static_cast<Chain<Ruby*>*> (chain);
				*r << cout;
				break;
			}
			case 'A': {
				Chain<Amethyst*>* a = static_cast<Chain<Amethyst*>*> (chain);
				*a << cout;
			}
					  break;
			case 'E': {
				Chain<Emerald*>* e = static_cast<Chain<Emerald*>*> (chain);
				*e << cout;
			}
					  break;
		}
	}
	return os;

}

void Player::createChain(int index, string cardType) {
	/*
	if ((*chains)[index] != NULL) {
		delete (*chains)[index]; // delete old chain
	}
	*/
	switch (cardType.at(0)) {
		case 'Q':
			(*chains)[index] = new Chain<Quartz*>();
			break;
		case 'H':
			(*chains)[index] = new Chain<Hematite*>();
			break;
		case 'O':
			(*chains)[index] = new Chain<Obsidian*>();
			break;
		case 'M':
			(*chains)[index] = new Chain<Malachite*>();
			break;
		case 'T':
			(*chains)[index] = new Chain<Turquoise*>();
			break;
		case 'R':
			(*chains)[index] = new Chain<Ruby*>();
			break;
		case 'A':
			(*chains)[index] = new Chain<Amethyst*>();
			break;
		case 'E':
			(*chains)[index] = new Chain<Emerald*>();
			break;
	}
	chainTypes[index] = cardType;
}

void Player::addCardToChain(int index, string cardType, Card* card) {
	Chain_Base* cb = (*chains)[index];
	switch (cardType.at(0)) {
		case 'Q': {
			Chain<Quartz*>* q = static_cast<Chain<Quartz*>*> (cb);
			*q += card;
		}
				  break;
		case 'H': {
			Chain<Hematite*>* h = static_cast<Chain<Hematite*>*> (cb);
			*h += card;
		}
				  break;
		case 'O': {
			Chain<Obsidian*>* o = static_cast<Chain<Obsidian*>*> (cb);
			*o += card;
		}
				  break;
		case 'M': {
			Chain<Malachite*>* m = static_cast<Chain<Malachite*>*> (cb);
			*m += card;
		}
				  break;
		case 'T': {
			Chain<Turquoise*>* t = static_cast<Chain<Turquoise*>*> (cb);
			*t += card;
		}
				  break;
		case 'R': {
			Chain<Ruby*>* r = static_cast<Chain<Ruby*>*> (cb);
			*r += card;
			break;
		}
		case 'A': {
			Chain<Amethyst*>* a = static_cast<Chain<Amethyst*>*> (cb);
			*a += card;
		}
				  break;
		case 'E': {
			Chain<Emerald*>* e = static_cast<Chain<Emerald*>*> (cb);
			*e += card;
		}
				  break;
	}
}


Hand* const Player::getHand() const {
	return hand;
}


const string Player::getName() const {
	return name;
}

vector<Chain_Base*>* Player::getChains() const {
	return chains;
}

const vector<string> Player::getChainTypes() const {
	return chainTypes;
}


const int Player::getNumCoins() const {
	return numCoins;
}

const int Player::getMaxNumChains() const {
	return chains->size();
}

const int Player::getNumChains() const {
	int numChains = 0;
	for (Chain_Base* c : *chains) {
		Chain<Ruby*>* t = static_cast<Chain<Ruby*>*>(c);
		if (t->size() > 0) {
			numChains++;
		}
	}
	return numChains;
}

const Chain_Base& Player::operator[](int i) {
	return *(*chains)[i];
}


void Player::buyThirdChain() {
	// ADD EXCEPTION HANDLING
	if (numCoins >= 2) {
		chains->push_back(new Chain<Ruby*>());
	}
	else {
		// exception here
	}
}

void Player::printHand(std::ostream& os, bool b) const {
	if (!b) {
		os << (hand->front())->getName() << endl;
	}
	else {
		os << hand;
	}
}


