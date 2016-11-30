using namespace std;
#include "DiscardPile.h"

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

const Card* DiscardPile::pickUp() {
	const Card* topCard = back();
	pop_back();
	return topCard;
}

const Card* DiscardPile::top() {
	return back();
}

void DiscardPile::print(ostream& os) {
	for (Card* c : *this) {
		os << c->getName()[0] << " ";
	}
	os << endl;
}



