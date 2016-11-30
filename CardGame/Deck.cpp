using namespace std;
#include "Deck.h"

Deck::Deck(std::istream& is, const CardFactory* cf) {

}

const Card* Deck::draw() {
	const Card* drawnCard = back();
	pop_back();
	return drawnCard;
}