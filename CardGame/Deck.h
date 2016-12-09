#pragma once
#include <vector>
#include "Card.h"

using namespace std;
class CardFactory;

class Deck : public vector<Card*> {
public:
	Deck() {};
	ostream& operator<<(ostream& os);
	Card* draw();
};