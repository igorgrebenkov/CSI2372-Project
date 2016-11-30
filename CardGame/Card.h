#pragma once
#include <string>

using namespace std;

class Card {
public:
	Card(const string name) : cardName(name) {};
	friend ostream& operator<<(ostream& os, const Card& card);
	friend bool operator==(const Card& c1, const Card& c2);
public:
	string cardName;
	virtual int getCardsPerCoin(const int& coins) const = 0;
	virtual string getName() const = 0;
	virtual void print(ostream& out) const = 0;
};

inline std::ostream& operator<<(std::ostream& os, const Card& card) {
	card.print(os);
	return os;
}

inline bool operator==(const Card& c1, const Card& c2) {
	if (c1.cardName == c2.cardName) {
		return true;
	}
	else {
		return false;
	}
}

class Quartz : public Card {
public:
	Quartz(const string name) : Card(name) {};
	int getCardsPerCoin(const int& coins) const;
	string getName() const;
	void print(ostream& out) const;
};

class Hematite : public Card {
public:
	Hematite(const string name) : Card(name) {};
	int getCardsPerCoin(const int& coins) const;
	string getName() const;
	void print(ostream& out) const;
};

class Obsidian : public Card {
public:
	Obsidian(const string name) : Card(name) {};
	int getCardsPerCoin(const int& coins) const;
	string getName() const;
	void print(ostream& out) const;
};

class Malachite : public Card {
public:
	Malachite(const string name) : Card(name) {};
	int getCardsPerCoin(const int& coins) const;
	string getName() const;
	void print(ostream& out) const;
};

class Turquoise : public Card {
public:
	Turquoise(const string name) : Card(name) {};
	int getCardsPerCoin(const int& coins) const;
	string getName() const;
	void print(ostream& out) const;
};

class Ruby : public Card {
public:
	Ruby(const string name) : Card(name) {};
	int getCardsPerCoin(const int& coins) const;
	string getName() const;
	void print(ostream& out) const;
};

class Amethyst : public Card {
public:
	Amethyst(const string name) : Card(name) {};
	int getCardsPerCoin(const int& coins) const;
	string getName() const;
	void print(ostream& out) const;
};

class Emerald : public Card {
public:
	Emerald(const string name) : Card(name) {};
	int getCardsPerCoin(const int& coins) const;
	string getName() const;
	void print(ostream& out) const;
};
