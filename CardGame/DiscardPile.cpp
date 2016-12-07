#include "DiscardPile.h"
using namespace std;

DiscardPile::DiscardPile(std::istream& is, const CardFactory* cf) {

}

const DiscardPile& DiscardPile::operator+=(Card* card) {
	push_back(card);
	return *this;
}

const ostream& DiscardPile::operator<<(ostream& os) {
	const Card* topCard = back();
	os << topCard->getName();
	return os;
}

Card* DiscardPile::pickUp() {
	Card* topCard = back();
	pop_back();
	return topCard;
}

Card* DiscardPile::top() {
	return back();
}

void DiscardPile::print(ostream& os) {
	for (Card* c : *this) {
		os << c->getName()[0] << " ";
	}
	os << endl;
}



