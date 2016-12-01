#include <string>
#include <iostream>
#include <queue>

#include "Card.h"
#include "CardFactory.h"
#include "DiscardPile.h"
#include "TradeArea.h"
#include "Player.h"
#include "Chain.h"
#include "Hand.h"

using namespace std;

int main() {
	
	// CardFactory tests
	const CardFactory* cf = CardFactory::getFactory();

	Deck d = cf->getDeck();

	for (Card* c : d) {
		c->print(cout);
	}
	cout << endl;

	// Chain tests
	Chain<Turquoise> a;

	a += d[1]; 
	a += d[1]; // 1 coin
	a += d[1];
	a += d[1]; // 2 coins
	a += d[1];
	a += d[1]; // 3 coins
	a += d[1]; // 4 coins

	a << cout;
	cout << a.sell() << endl;

	// Hand tests
	Hand h;

	h += d[0];
	h += d[1];
	h += d[2];

	h[0]->print(cout);
	h[1]->print(cout);
	h[2]->print(cout);

	h << cout;

	const Card* play = h.play();
	const Card* top = h.top();

	cout << "Play: ";
	play->print(cout);
	cout << "Top: ";
	top->print(cout);
	h << cout;


	/*
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

	//Player tests
	Player p("Igor");
	p += 4;
	cout << p;
	*/
	


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