#include <string>
#include <iostream>

#include "Card.h"
#include "CardFactory.h"
#include "DiscardPile.h"
#include "TradeArea.h"

using namespace std;

int main() {
	// CardFactory tests
	const CardFactory* cf = CardFactory::getFactory();

	Deck d = cf->getDeck();

	for (Card* c : d) {
		c->print(cout);
	}
	cout << endl;
	const Card* drawn = d.draw();
	cout << "Drawn: " << *drawn;
	cout << endl;

	
	// DiscardPile tests
	DiscardPile pile;
	pile += d[0]; // test overloaded operators
	pile += d[1];
	cout << endl;
	const Card* pickedUp = pile.pickUp();
	const Card* top = pile.top();
	cout << *pickedUp;
	cout << *top;
	cout << endl;
	pile += d[0];
	pile += d[1];
	pile += d[2];
	pile += d[3];
	pile.print(cout);
	cout << endl;

	//TradeArea tests
	TradeArea t;
	// Add cards to trade area
	t += d[0];
	t += d[1];
	t += d[2];
	t += d[3];
	t += d[4];
	t += d[5];
	t += d[6];
	t << cout;
	cout << t.legal(d[0]) << endl; // should be true;
	cout << t.legal(d[7]) << endl; // should be false
	cout << t.numCards() << endl;

	


	/*
	Quartz a("Quartz");
	Ruby b("Ruby");
	const int aCoins = 0;
	const int bCoins = 0;



	a.print(cout);
	cout << a.getCardsPerCoin(aCoins) << endl;
	b.print(cout);
	cout << b.getCardsPerCoin(bCoins) << endl;
	*/


	return 0;
}