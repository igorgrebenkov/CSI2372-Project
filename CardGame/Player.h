#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "Chain.h"
using namespace std;
class Player {
private:
	string name;
	int numCoins;
	vector<Chain_Base<Card> *> chains;
public:
	Player(const string& s);
	const Player& operator+=(int i);
	friend ostream& operator<<(ostream& os, const Player&);
	const int getNumCoins() const;
	const int getMaxNumChains() const;
	const int getNumChains() const;
	const Chain_Base<Card>& operator[](int i);
	void buyThirdChain();
	void printHand(std::ostream&, bool) const;
};


