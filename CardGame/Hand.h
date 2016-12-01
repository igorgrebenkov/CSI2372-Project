#pragma once
#include <queue>
#include <deque>
#include <vector>
#include "Card.h"

using namespace std;
class CardFactory;

class Hand : public queue<Card*,deque<Card*>> {
public:
	Hand() {};
	Hand(istream& os, const CardFactory* cf);
	const Hand& operator+=(Card* c);
	const Card* operator[](int);
	ostream& operator<<(ostream& os);
	const Card* play();
	const Card* top() const;
};