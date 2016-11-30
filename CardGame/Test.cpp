#include <string>
#include <iostream>

#include "Card.h"
#include "CardFactory.h"
#include "DiscardPile.h"

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