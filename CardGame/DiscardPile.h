#pragma once
#include <vector>
#include "Card.h"
#include "CardFactory.h"

using namespace std;
class CardFactory;

class DiscardPile : public vector<Card*> {
public:
	DiscardPile() {};
	DiscardPile(istream& os, const CardFactory* cf);
	const DiscardPile& operator+=(Card* card);
	const ostream& operator<<(ostream& os);
	Card* pickUp();
	Card* top();
	void print(ostream& os);
};