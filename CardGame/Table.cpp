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

Table::Table(istream& is, const CardFactory* cf) {
	string p1Str, p2Str, deckStr, discardStr, tradeStr;
	// Split file content into discrete strings for various program object states
	splitFileToStrings(is, p1Str, p2Str, deckStr, discardStr, tradeStr);

	is.clear();
	istringstream iss(p1Str);
	p1 = new Player(iss, cf);
	iss.clear();
	iss.str(p2Str);
	p2 = new Player(iss, cf);
	iss.clear();
	iss.str(deckStr);

	// Create temporary deck to re-create deck from save file
	Deck tmp = cf->getDeck();
	deck = *new Deck();
	for (char c : deckStr) {
		if (c != ' ') {
			vector<Card*>::iterator it = tmp.begin();
			while (it != tmp.end()) {
				Card* card = *it;
				char firstLetter = card->getName().at(0);
				if (firstLetter == c) {
					deck.push_back(card);
					break;
				}
				it++;
			}
		}
	}

	iss.clear();
	iss.str(discardStr);
	discardPile = new DiscardPile(iss, cf);

	iss.clear();
	iss.str(tradeStr);
	tradeArea = new TradeArea(iss, cf);
}

Table::~Table() {
	delete p1;
	delete p2;
	delete discardPile;
	delete tradeArea;
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
	os << "Discard Top: ";
	*discardPile << os;
	os << "Trade Area: ";
	*tradeArea << os;
	os << "Cards in Deck: ";
	os << deck.size() << endl;
	os << "------------------------------------------------------------" << endl;
	os << endl;
	return os;
}

/**
* Function: getPlayers
* Description: getter for the players
* Returns: an array containing a pointer to each player
**/
Player* const Table::getPlayers(Player* arr[]) const {
	arr[0] = p1;
	arr[1] = p2;
	return *arr;
}

/**
* Function: getDeck
* Description: getter for the deck
* Returns: a reference to the deck
**/
Deck& Table::getDeck() {
	return deck;
}

/**
* Function: getDiscardPile
* Description: getter for the discard pile
* Returns: a pointer to the discard pile
**/
DiscardPile* const Table::getDiscardPile() const {
	return discardPile;
}

/**
* Function: getTradeArea
* Description: getter for the trade area
* Returns: a pointer to the trade area
**/
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

/**
* Function: splitFileToStrings
* Description: splits a save game file into discrete strings
* Returns: the various strings by reference
**/
void Table::splitFileToStrings(istream& is, string& p1Str, string& p2Str, 
	string& deckStr, string& discardStr, string& tradeStr) {

	string line;
	bool haveP1 = false; // flag to indicate we have player1's string
	bool haveP2 = false; // flag to indicate we have player2's string
	// counter for last three lines to get 
	//string for deck/discard pile/ trade area
	int fileReadCnt = 0; 

	while (getline(is, line)) {
		if (!haveP1) { // get player1 string
			int find = line.find("p1:");
			int find2 = line.find("p2:");
			if (find == string::npos && find2 == string::npos) {
				p1Str += line + "\n";

			}
			else if (!(find2 == string::npos)) {
				haveP1 = true;
			}
		}
		else if (!haveP2) { // get player2 string
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
					deckStr += line + "\n";    // get deck str
					fileReadCnt++;
					break;
				case 1:
					discardStr += line + "\n"; // get discard pile str
					fileReadCnt++;
					break;
				case 2:
					tradeStr += line + "\n";   // get trade area str
					fileReadCnt++;
					break;
			}
		}
	}
}
