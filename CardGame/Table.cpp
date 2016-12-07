#include "Table.h"
#include "CardFactory.h"

Table::Table(const string& p1Name, const string& p2Name) {
	p1 = new Player(p1Name);
	p2 = new Player(p2Name);
	const CardFactory* cf = CardFactory::getFactory();
	deck = cf->getDeck();
	
	Hand* p1Hand = p1->getHand();
	Hand* p2Hand = p2->getHand();

	// Draw 5 cards from the deck to each player's hand
	for (int i = 0; i < 5; i++) {
		*p1Hand += deck.draw();
		*p2Hand += deck.draw();
	}

	discardPile = new DiscardPile();
	tradeArea = new TradeArea();
}

Table::Table(istream& os, const CardFactory* cf) {

}

ostream& Table::operator<<(ostream& os) {
	os << "------------------------------------------------------------" << endl;
	os << "Player 1: " << endl;
	os << "------------------------------------------------------------" << endl;
	*p1 << os;
	os << "------------------------------------------------------------" << endl;
	os << "Player 2: " << endl;
	os << "------------------------------------------------------------" << endl;
	*p2 << os;
	os << endl;
	os << "Discard Pile: ";
	discardPile->print(cout);
	os << "Trade Area: ";
	*tradeArea << os;
	os << "Cards in Deck: ";
	os << deck.size() << endl;
	os << "------------------------------------------------------------" << endl;
	os << endl;
	return os;
} 

Player* const Table::getPlayers(Player* arr[]) const {
	arr[0] = p1;
	arr[1] = p2;
	return *arr;
}

Deck& Table::getDeck() {
	return deck;
}

DiscardPile* const Table::getDiscardPile() const {
	return discardPile;
}

TradeArea* const Table::getTradeArea() const {
	return tradeArea;
}


const bool Table::win(string& s) const {
	if (deck.empty()) {
		s = p1->getNumCoins() > p2->getNumCoins() ?
			p1->getName() : p2->getName();
		return true;
	}
	return false;
}

void Table::print(ostream& os) {
	os << "Player 1: "; 
	*p1 << os;
	os << "Player 2: ";
	*p2 << os;
	os << "Deck: ";
	deck << os;
	os << "Discard Pile:";
	discardPile->print(cout);
	os << "Trade Area:";
	*tradeArea << os;
}