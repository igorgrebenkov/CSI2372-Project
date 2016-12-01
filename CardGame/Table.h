#pragma once
#include <string>
#include <iostream>
#include "Player.h"
#include "Deck.h"
#include "DiscardPile.h"
#include "TradeArea.h"
class CardFactory;

class Table {
private:
	Player* p1;
	Player* p2;
	Deck deck;
	DiscardPile* discardPile;
	TradeArea* tradeArea;
public:
	Table(string& p1Name, string& p2Name);
	Table(istream& os, const CardFactory* cf);
	ostream& operator<<(ostream&);
	const bool win(string& s) const;
	void print(ostream&);
};