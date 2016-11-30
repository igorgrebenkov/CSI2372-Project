#include <iostream>
#include <string>
#include "Player.h"

using namespace std;

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
	return 0;
}

const int Player::getNumChains() const {
	return 0;
}

void Player::buyThirdChain() const {
}

void Player::printHand(std::ostream&, bool) const {
}
