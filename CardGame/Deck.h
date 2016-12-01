#pragma once
#include <vector>
#include "Card.h"

using namespace std;
class CardFactory;

class Deck : public vector<Card*> {
public:
	Deck() {};
	Deck(istream& os, const CardFactory* cf);
	Card* draw();
};