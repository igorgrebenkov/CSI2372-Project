#pragma once
#include <vector>
#include "Card.h"

using namespace std;
class CardFactory;

class Deck : public vector<Card*> {
public:
	Deck() {};
	Deck(istream& is, const CardFactory* cf);
	ostream& operator<<(ostream& os);
	Card* draw();
};