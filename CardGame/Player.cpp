#include <iostream>
#include <string>
#include "Player.h"

using namespace std;

Player::Player(const string& s) : name(s), numCoins(0) {
	chains.push_back(new Chain_Base<Card>());
	chains.push_back(new Chain_Base<Card>());
	hand = new Hand();
}


const Player& Player::operator+=(int i) {
	numCoins += i;
	return *this;
}

ostream& Player::operator<<(std::ostream& os) const {
	os << name << "\t" << numCoins << endl;
	if (chains[0] != NULL) {
		os << (*chains[0])[0]->getName();
		os << "\t";
		for (size_t i = 0; i < (*chains[0]).size(); i++) {
			os << (*chains[0])[0]->getName();
		}

	}
	return os;
}

Hand* const Player::getHand() const {
	return hand;
}


const string Player::getName() const {
	return name;
}


const int Player::getNumCoins() const {
	return numCoins;
}

const int Player::getMaxNumChains() const {
	return chains.size();
}

const int Player::getNumChains() const {
	int numChains = 0;
	for (Chain_Base<Card>* c : chains) {
		if (c->size() > 0) {
			numChains++;
		}
	}
	return numChains;
}

const Chain_Base<Card>& Player::operator[](int i) {
	return *chains[i];
}


void Player::buyThirdChain() {
	// ADD EXCEPTION HANDLING
	if (numCoins >= 2) {
		chains.push_back(new Chain_Base<Card>());
	}
	else {
		   // exception here
	}
}

void Player::printHand(std::ostream& os, bool b) const {
	if (!b) {
		os << (hand->front())->getName() << endl;
	} else {
		os << hand;
	}
}
