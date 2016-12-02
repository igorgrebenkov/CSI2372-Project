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
	Table(const string& p1Name, const string& p2Name);
	Table(istream& os, const CardFactory* cf);
	ostream& operator<<(ostream&);
	const Player* const getPlayers(Player* arr[]) const;
	const bool win(string& s) const;
	void print(ostream&);
};