#include "Hand.h"

Hand::Hand(istream & os, const CardFactory* cf) {
}

Hand& Hand::operator+=(Card* c) {
	push(c);
	return *this;
}

Card* Hand::operator[](int i) {
	int j = 0;
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
	int j = 0;
	while (j != this->size()) {
		os << (*this)[j]->getName()[0] << " ";
		j++;
	}
	os << endl;
	return os;
}


Card* Hand::play() {
	return nullptr;
}

Card* Hand::top() {
	return nullptr;
}

const Card* Hand::draw() {
	return nullptr;
}
