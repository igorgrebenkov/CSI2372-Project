#pragma once
#include <vector>
#include <iostream>
#include "Card.h"
using namespace std;
class CardFactory;


template <typename T>
class Chain_Base : public vector<T*> {
public:
	Chain_Base() {};
	T* test() {
		return (*this)[0];
	}
};

template <typename T>
class Chain : public Chain_Base<T> {
public:
	Chain() {};
	Chain(istream& is, const CardFactory* cf) {};
	Chain& operator+=(Card* c);
	const ostream& operator<<(ostream& os);
	int sell();
};


template <typename T>
inline Chain<T>& Chain<T>::operator+=(Card* c) {
	push_back(dynamic_cast<T*> (c));
	return *this;
}

template <typename T>
inline const ostream& Chain<T>::operator<<(ostream& os) {
	if (this->size() != 0) {	// prevents crash with empty vector
		os << (*this)[0]->getName() << "\t";
		for (T* c : *this) {
			os << c->getName()[0] << " ";
		}
		os << endl;
	}
	return os;
}

template <typename T>
inline int Chain<T>::sell() {
	int numCards = this->size();
	if (numCards != 0) {
		T* card = (*this)[0];

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
