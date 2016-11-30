#pragma once
#include <vector>
#include "Card.h"

using namespace std;
class CardFactory;

class Deck : public vector<Card*> {
public:
	using vector<Card*>::vector;
	Deck() {};
	Deck(istream& os, const CardFactory* cf);
	const Card* draw();
};