#pragma once
#include <list>
#include "Card.h"
#include "CardFactory.h"

using namespace std;
class CardFactory;

class TradeArea : public list<Card*> {
public:
	TradeArea() {};
	TradeArea(istream& is, const CardFactory* cf);
	const TradeArea& operator+=(Card* card);
	const ostream& operator<<(ostream& os);
	bool legal(Card* card);
	Card* trade(string s);
	int numCards();
};