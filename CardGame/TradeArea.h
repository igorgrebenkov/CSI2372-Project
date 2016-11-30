#pragma once
#include <list>
#include "Card.h"

using namespace std;
class CardFactory;

class TradeArea : public list<Card*> {
public:
	TradeArea() {};
	TradeArea(istream& os, const CardFactory* cf);
	const TradeArea& operator+=(Card* card);
	const ostream& operator<<(ostream& os);
	bool legal(Card* card);
	const Card* trade(string s);
	int numCards();
};