#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "Chain.h"
#include "Hand.h"
using namespace std;
class Player {
private:
	string name;
	int numCoins;
	vector<Chain_Base*> chains;
	string chain1Type;
	Hand* hand;
public:
	Player(const string& s);
	const Player& operator+=(int i);
	ostream& operator<<(ostream& os) const;
	Hand* const getHand() const;
	const string getName() const;
	vector<Chain_Base*> getChains() const;
	const int getNumCoins() const;
	const int getMaxNumChains() const;
	const int getNumChains() const;
	const Chain_Base& operator[](int i);
	void buyThirdChain();
	void printHand(ostream&, bool) const;
};


