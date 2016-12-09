#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

#include "Chain.h"
#include "Hand.h"
#include "CardFactory.h"
using namespace std;

class Player {
private:
	string name;
	int numCoins;
	vector<Chain_Base*>* chains;
	vector<string> chainTypes;
	Hand* hand;
	void parseInputStream(istream& is, string& name, string& hand);
public:
	Player(const string& s);
	Player(istream& is, const CardFactory* cf);
	const Player& operator+=(int i);
	ostream& operator<<(ostream& os) const;
	const Chain_Base& operator[](int i);
	void createChain(int index, string cardType);
	void addCardToChain(int index, string cardType, Card* c);
	vector<Chain_Base*>* getChains() const;
	const vector<string> getChainTypes() const;
	Hand* const getHand() const;
	const string getName() const;
	const int getNumCoins() const;
	const int getMaxNumChains() const;
	const int getNumChains() const;
	void buyThirdChain();
	void printHand(ostream&, bool) const;
};

class NotEnoughCoins : public exception {
	virtual const char* what() const throw() {
		return "NotEnoughCoinsException";
	}
};


