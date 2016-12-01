#include "Table.h"
#include "CardFactory.h"

Table::Table(string& p1Name, string& p2Name) {
	p1 = new Player(p1Name);
	p2 = new Player(p2Name);
	const CardFactory* cf = CardFactory::getFactory();
	deck = cf->getDeck();
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