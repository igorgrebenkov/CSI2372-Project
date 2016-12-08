#include "Hand.h"

Hand::Hand(istream & is, const CardFactory* cf) {
	string handStr;
	getline(is, handStr);
	Deck tmp = cf->getDeck();
	for (char c : handStr) {
		if (c != ' ') {
			for (Card* card : tmp) {
				char firstLetter = card->getName().at(0);
				if (firstLetter == c) {
					*this += card;
					break;
				}
			}
		}
	}
}

const Hand& Hand::operator+=(Card* c) {
	this->push(c);
	return *this;
}

Card* Hand::operator[](int i) {
	size_t j = 0;
	Card* saved = NULL;
	Card* ret = NULL;
	while (j != this->size()) {
		saved = front();
		if (j == i) {
			ret = saved;
		}
		this->pop();
		this->push(saved);
		j++;
	}
	return ret;
}

ostream& Hand::operator<<(ostream& os) {
	size_t j = 0;
	os << "Hand: ";
	while (j != this->size()) {
		os << (*this)[j]->getName()[0] << " ";
		j++;
	}
	os << endl;
	return os;
}

Card* Hand::play() {
	Card* ret = this->front();
	this->pop();
	return ret;
}

const Card* Hand::top() const {
	return this->front();
}


