#include <string>
#include <iostream>

#include "Card.h"
#include "CardFactory.h"

using namespace std;

int main() {
	const CardFactory* cf = CardFactory::getFactory();
	Deck d = cf->getDeck();

	for (Card* c : d) {
		c->print(cout);
	}


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