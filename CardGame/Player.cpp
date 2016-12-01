#include <iostream>
#include <string>
#include "Player.h"

using namespace std;

Player::Player(const string& s) : name(s), numCoins(0) {
	chains.push_back(new Chain_Base<Card>);
	chains.push_back(new Chain_Base<Card>);
}


const Player& Player::operator+=(int i) {
	numCoins += i;
	return *this;
}

ostream& operator<<(std::ostream& os, const Player& p) {
	os << p.name << "\t" << p.numCoins << endl;
	return os;
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
		chains.push_back(new Chain_Base<Card>);
	}
	else {
		   // exception here
	}
}

void Player::printHand(std::ostream&, bool) const {

}
