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

Table::Table(istream& is) {
	//const CardFactory* cf = CardFactory::getFactory();
	const CardFactory* cf = CardFactory::getFactory();

	string p1Str, p2Str, deckStr, discardStr, tradeStr;
	splitFileToStrings(is, p1Str, p2Str, deckStr, discardStr, tradeStr);

	is.clear();
	istringstream iss(p1Str);
	p1 = new Player(iss, cf);
	iss.clear();
	iss.str(p2Str);
	p2 = new Player(iss, cf);
	
	
	//cout << p1Str << endl;
	//cout << p2Str << endl;
	//cout << deckStr << endl;
	//cout << discardStr << endl;
	//cout << tradeStr << endl;
	

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
	os << "p1:" << endl;
	*p1 << os;
	*p1->getHand() << os;
	os << "p2:" << endl;
	*p2 << os;
	*p2->getHand() << os;
	deck << os;
	discardPile->print(os);
	*tradeArea << os;
}

void Table::splitFileToStrings(istream& is, string& p1Str, string& p2Str, 
	string& deckStr, string& discardStr, string& tradeStr) {

	string line;
	bool haveP1 = false;
	bool haveP2 = false;
	int fileReadCnt = 0;

	while (getline(is, line)) {
		if (!haveP1) {
			int find = line.find("p1:");
			int find2 = line.find("p2:");
			if (find == string::npos && find2 == string::npos) {
				p1Str += line + "\n";

			}
			else if (!(find2 == string::npos)) {
				haveP1 = true;
			}
		}
		else if (!haveP2) {
			int find = line.find("Hand: ");
			if (find == string::npos) {
				p2Str += line + "\n";
			}
			else {
				p2Str += line + "\n";
				haveP2 = true;
			}
		}
		else {
			switch (fileReadCnt) {
				case 0:
					deckStr += line + "\n";
					fileReadCnt++;
				case 1:
					discardStr += line + "\n";
					fileReadCnt++;
					break;
				case 2:
					tradeStr += line + "\n";
					fileReadCnt++;
					break;
			}
		}
	}
}
