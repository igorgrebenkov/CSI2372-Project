#pragma once

#include <vector>
#include "Card.h"

using namespace std;
class CardFactory;

class DiscardPile : public vector<Card*> {
public:
	DiscardPile() {};
	DiscardPile(istream& os, const CardFactory* cf);
	const DiscardPile& operator+=(Card* card);
	const ostream& operator<<(ostream& os);
	const Card* pickUp();
	const Card* top();
	void print(ostream& os);
};