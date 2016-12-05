#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "Chain.h"
#include "Hand.h"
using namespace std;

enum class cardTypes {
	Null, Quartz, Hematite, Obsidian, Malachite,
	Turquoise, Ruby, Amethyst, Emerald
};

class Player {
private:
	string name;
	int numCoins;
	vector<Chain_Base*>* chains;
	vector<string> chainTypes;
	Hand* hand;
public:
	Player(const string& s);
	const Player& operator+=(int i);
	ostream& operator<<(ostream& os) const;
	void createChain(int index, string cardType);
	void addCardToChain(int index, string cardType, Card* c);
	Hand* const getHand() const;
	const string getName() const;
	vector<Chain_Base*>* getChains() const;
	const vector<string> getChainTypes() const;
	const int getNumCoins() const;
	const int getMaxNumChains() const;
	const int getNumChains() const;
	const Chain_Base& operator[](int i);
	void buyThirdChain();
	void printHand(ostream&, bool) const;
};


