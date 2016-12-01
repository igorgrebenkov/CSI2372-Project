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

	p1->printHand(cout, false);
	p2->printHand(cout, false);

	discardPile = new DiscardPile();
	tradeArea = new TradeArea();
}

Table::Table(istream& os, const CardFactory* cf) {

}

ostream& Table::operator<<(ostream& os) {
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

void Table::print(ostream&) {

}