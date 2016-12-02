#include "Table.h"
#include "CardFactory.h"

Table::Table(const string& p1Name, const string& p2Name) {
	p1 = new Player(p1Name);
	p2 = new Player(p2Name);
	const CardFactory* cf = CardFactory::getFactory();
	deck = cf->getDeck();
	
	Hand* p1Hand = p1->getHand();
	Hand* p2Hand = p2->getHand();

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
	os << "Player 1: " << p1->getName() << endl;
	os << "Player 2: " << p2->getName() << endl;
	os << "Discard Pile: ";
	discardPile->print(cout);
	os << "Trade Area:";
	*tradeArea << os;
	return os;
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
	os << "Player 1: " << p1->getName() << endl;
	os << "Player 2: " << p2->getName() << endl;
	os << "Deck:";
	deck << os;
	os << "Discard Pile:";
	discardPile->print(cout);
	os << "Trade Area:";
	*tradeArea << os;
}