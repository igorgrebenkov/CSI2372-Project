#pragma once
#include <vector>
#include <iostream>
#include "Card.h"
using namespace std;
class CardFactory;


class Chain_Base {
public:
	Chain_Base() {};
};

template <typename T>
class Chain : public Chain_Base, public vector<T> {
public:
	Chain() : Chain_Base() {};
	Chain& operator+=(Card* c);
	const ostream& operator<<(ostream& os);
	int sell();
};

class IllegalType : public exception {
	virtual const char* what() const throw() {
		return "IllegalType Exception";
	}
};

template <typename T>
inline Chain<T>& Chain<T>::operator+=(Card* c) {
	T cast = dynamic_cast<T> (c);
	if (cast != 0) {
		push_back(cast);
	} else {
		throw new IllegalType();
	}
	return *this;
}

template <typename T>
inline const ostream& Chain<T>::operator<<(ostream& os) {
	os.width(12);
	if (this->size() != 0) {	// prevents crash with empty vector
		os << (*this)[0]->getName() << left;
		for (T c : *this) {
			os << c->getName()[0] << " ";
		}
	}
	os << "\n";
	return os;
}
template <typename T>
inline int Chain<T>::sell() {
	int numCards = this->size();
	if (numCards != 0) {
		T card = (*this)[0];

		if (numCards >= card->getCardsPerCoin(1) &&
			numCards < card->getCardsPerCoin(2)) {
			return 1;
		}
		else if (numCards >= card->getCardsPerCoin(2) &&
			numCards < card->getCardsPerCoin(3)) {
			return 2;
		}
		else if (numCards >= card->getCardsPerCoin(3) &&
			numCards < card->getCardsPerCoin(4)) {
			return 3;
		}
		else if (numCards >= card->getCardsPerCoin(4)) {
			return 4;
		}
	}
	return 0;
}
