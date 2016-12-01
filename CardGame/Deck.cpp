using namespace std;
#include "Deck.h"

Deck::Deck(std::istream& is, const CardFactory* cf) {

}

Card* Deck::draw() {
	Card* drawnCard = back();
	pop_back();
	return drawnCard;
}