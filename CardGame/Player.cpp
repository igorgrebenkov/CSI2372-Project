#include <iostream>
#include <string>
#include "Player.h"

using namespace std;

Player::Player(const string& s) : name(s), numCoins(0), chain1Type("") {
	chains.push_back(new Chain<Ruby*>());
	chain1Type = "Ruby";
	//chains.push_back(new Chain_Base());
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
	
	//if (chain1Type == "Ruby") {
		Chain<Ruby*>* c = static_cast<Chain<Ruby*>*>(chains[0]);
	//}

	if (!c->empty()) {
		os << (*c)[0]->getName();
		os << "\t";
		for (size_t i = 0; i < c->size(); i++) {
			os << (*c)[0]->getName();
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

vector<Chain_Base*> Player::getChains() const {
	return chains;
}


const int Player::getNumCoins() const {
	return numCoins;
}

const int Player::getMaxNumChains() const {
	return chains.size();
}

const int Player::getNumChains() const {
	int numChains = 0;
	for (Chain_Base* c : chains) {
		Chain<Ruby*>* t = static_cast<Chain<Ruby*>*>(c);
		if (t->size() > 0) {
			numChains++;
		}
	}
	return numChains;
}

const Chain_Base& Player::operator[](int i) {
	return *chains[i];
}


void Player::buyThirdChain() {
	// ADD EXCEPTION HANDLING
	if (numCoins >= 2) {
		chains.push_back(new Chain<Ruby*>());
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
