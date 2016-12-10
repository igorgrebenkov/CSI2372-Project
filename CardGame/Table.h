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
	void splitFileToStrings(istream&, string& p1, string& p2,
		string& deck, string& discard, string& trade);
public:
	Table(const string& p1Name, const string& p2Name);
	Table(istream& os, const CardFactory* cf);
	ostream& operator<<(ostream&);
	Player* const getPlayers(Player* arr[]) const;
	Deck& getDeck();
	DiscardPile* const getDiscardPile() const;
	TradeArea* const getTradeArea() const;
	const bool win(string& s) const;
	void print(ostream&);
};
