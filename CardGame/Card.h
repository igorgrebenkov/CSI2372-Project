#pragma once
#include <string>

using namespace std;

class Card {
public:
	Card(const string name) : cardName(name) {};
	friend ostream& operator<<(ostream& os, const Card& card);
protected:
	string cardName;
	virtual int getCardsPerCoin(const int& coins) const = 0;
	virtual string getName() const = 0;
	virtual void print(ostream& out) const = 0;
};

inline std::ostream& operator<<(std::ostream& os, const Card& card) {
	card.print(os);
	return os;
}

class Quartz : protected Card {
public:
	Quartz(const string name) : Card(name) {};
	int getCardsPerCoin(const int& coins) const;
	string getName() const;
	void print(ostream& out) const;
};

class Hematite : protected Card {
public:
	Hematite(const string name) : Card(name) {};
	int getCardsPerCoin(const int& coins) const;
	string getName() const;
	void print(ostream& out) const;
};

class Obsidian : protected Card {
public:
	Obsidian(const string name) : Card(name) {};
	int getCardsPerCoin(const int& coins) const;
	string getName() const;
	void print(ostream& out) const;
};

class Malachite : protected Card {
public:
	Malachite(const string name) : Card(name) {};
	int getCardsPerCoin(const int& coins) const;
	string getName() const;
	void print(ostream& out) const;
};

class Turquoise : protected Card {
public:
	Turquoise(const string name) : Card(name) {};
	int getCardsPerCoin(const int& coins) const;
	string getName() const;
	void print(ostream& out) const;
};

class Ruby : protected Card {
public:
	Ruby(const string name) : Card(name) {};
	int getCardsPerCoin(const int& coins) const;
	string getName() const;
	void print(ostream& out) const;
};

class Amethyst : protected Card {
public:
	Amethyst(const string name) : Card(name) {};
	int getCardsPerCoin(const int& coins) const;
	string getName() const;
	void print(ostream& out) const;
};

class Emerald : protected Card {
public:
	Emerald(const string name) : Card(name) {};
	int getCardsPerCoin(const int& coins) const;
	string getName() const;
	void print(ostream& out) const;
};
