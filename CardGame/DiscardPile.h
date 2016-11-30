#pragma once

#include <vector>
#include "Card.h"

using namespace std;
class CardFactory;

class DiscardPile : public vector<Card*> {
public:
	using vector<Card*>::vector;
	DiscardPile() {};
	const DiscardPile& operator+=(Card* card);
	const ostream& operator<<(ostream& os);
	DiscardPile(istream& os, const CardFactory* cf);
	const Card* pickUp();
	const Card* top();
	void print(ostream& os);
};