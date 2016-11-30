#pragma once

#include <vector>
#include "Card.h"

using namespace std;
class CardFactory;

class DiscardPile : public vector<Card*> {
public:
	using vector<Card*>::vector;
	DiscardPile() {};
	DiscardPile& operator+=(Card*);
	DiscardPile(istream& os, const CardFactory* cf);

};