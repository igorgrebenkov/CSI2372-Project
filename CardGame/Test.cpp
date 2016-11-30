#include "Card.h"
#include <string>
#include <iostream>

using namespace std;

int main() {
	Quartz a("Quartz");
	Ruby b("Ruby");
	const int aCoins = 0;
	const int bCoins = 0;



	a.print(cout);
	cout << a.getCardsPerCoin(aCoins) << endl;
	b.print(cout);
	cout << b.getCardsPerCoin(bCoins) << endl;


	return 0;
}