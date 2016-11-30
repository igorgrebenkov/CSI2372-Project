#pragma once
#include <iostream>
#include <string>
using namespace std;

class Player {
private:
	string name;
	int numCoins;
public:
	Player(const string& s) : name(s), numCoins(0) {};
	const Player& operator+=(int i);
	friend ostream& operator<<(ostream& os, const Player&);
	const int getNumCoins() const;
	const int getMaxNumChains() const;
	const int getNumChains() const;
	void buyThirdChain() const;
	void printHand(std::ostream&, bool) const;
};


