#include "Player.h"

using namespace std;

Player::Player(const string& s) : name(s), numCoins(0),
chainTypes{ " ", " ", "noChain" } {
	chains = new vector<Chain_Base*>();
	chains->push_back(new Chain_Base());
	chains->push_back(new Chain_Base());
	chains->push_back(new Chain_Base());

	hand = new Hand();
}

Player::Player(istream& is, const CardFactory* cf) {
	string line;
	int chainTypeIndex = 0;
	vector<int> cardsPerChain;
	string pName;
	string pHand;

	while (!is.eof()) {
		getline(is, line);
		int find = line.find("coins");
		int find2 = line.find("Hand:");
		if (!(find == string::npos)) {
			char nc = line.at(find - 2);
			numCoins = nc - '0';
			for (char c : line) {
				if (c != ' ') {
					pName += c;
				}
				else {
					break;
				}			 

			}
		}
		else if (find2 == string::npos) {
			bool haveChainName = false;
			string chainName;
			int numCardsInChain = 0;
			for (char c : line) {
				if (c != ' ' && !haveChainName) {
					chainName += c;
				}
				else if (c == ' ' && !haveChainName) {
					haveChainName = true;
				}
				else if (c != ' ' && haveChainName) {
					numCardsInChain++;
				}
			}
			if (numCardsInChain != 0 && !chainName.empty()) {
				cardsPerChain.push_back(numCardsInChain);
				chainTypes.push_back(chainName);
				chainTypeIndex++;
			}
		}
		else if (!(find2 == string::npos)) {
			for (char c : line) {

			}
			pHand = line.substr(find + 7);
		}
	}

	name = pName;

	if (chainTypes.size() == 2) {
		chainTypes.push_back("noChain");
	}

	chains = new vector<Chain_Base*>();
	chains->push_back(new Chain_Base());
	chains->push_back(new Chain_Base());
	chains->push_back(new Chain_Base());

	Deck tmp = cf->getDeck();
	for (size_t i = 0; i < cardsPerChain.size(); i++) {
		string cardName = chainTypes[i];
		Card* toAdd;
		for (Card* c : tmp) {
			if (c->getName() == cardName) {
				toAdd = c;
				break;
			}
		}

		createChain(i, chainTypes[i]);
		int cardCnt = 0;
		while (cardCnt < cardsPerChain[i]) {
			addCardToChain(i, chainTypes[i], toAdd);
			cardCnt++;
		}
	}

	istringstream iss(pHand);
	hand = new Hand(iss, cf);
	*this << cout;
	*this->getHand() << cout;
}


const Player& Player::operator+=(int i) {
	numCoins += i;
	return *this;
}

ostream& Player::operator<<(std::ostream& os) const {
	// Print Player name & number of coins
	os.width(12);
	os << left << name <<
		left << numCoins << " coins" << endl;

	// Need to cast Chain_Base* to the appropriate Chain template type
	// so we may put the chain in the output stream
	for (int i = 0; i < 3; i++) {
		string chainType = chainTypes[i];
		Chain_Base* chain = (*chains)[i];
		switch (chainType.at(0)) {
			case 'Q': {
				Chain<Quartz*>* q = static_cast<Chain<Quartz*>*> (chain);
				*q << os;
			}
					  break;
			case 'H': {
				Chain<Hematite*>* h = static_cast<Chain<Hematite*>*> (chain);
				*h << os;
			}
					  break;
			case 'O': {
				Chain<Obsidian*>* o = static_cast<Chain<Obsidian*>*> (chain);
				*o << os;
			}
					  break;
			case 'M': {
				Chain<Malachite*>* m = static_cast<Chain<Malachite*>*> (chain);
				*m << os;
			}
					  break;
			case 'T': {
				Chain<Turquoise*>* t = static_cast<Chain<Turquoise*>*> (chain);
				*t << os;
			}
					  break;
			case 'R': {
				Chain<Ruby*>* r = static_cast<Chain<Ruby*>*> (chain);
				*r << os;
				break;
			}
			case 'A': {
				Chain<Amethyst*>* a = static_cast<Chain<Amethyst*>*> (chain);
				*a << os;
			}
					  break;
			case 'E': {
				Chain<Emerald*>* e = static_cast<Chain<Emerald*>*> (chain);
				*e << os;
			}
					  break;
		}
	}
	return os;
}

const Chain_Base& Player::operator[](int i) {
	return *(*chains)[i];
}

void Player::createChain(int index, string cardType) {
	// save pointer to previous chain so we can delete it
	Chain_Base* toDelete = (*chains)[index];

	// Need to cast Chain_Base* to the appropriate Chain template type
	// so we may create a new Chain of that type
	switch (cardType.at(0)) {
		case 'Q':
			(*chains)[index] = new Chain<Quartz*>();
			break;
		case 'H':
			(*chains)[index] = new Chain<Hematite*>();
			break;
		case 'O':
			(*chains)[index] = new Chain<Obsidian*>();
			break;
		case 'M':
			(*chains)[index] = new Chain<Malachite*>();
			break;
		case 'T':
			(*chains)[index] = new Chain<Turquoise*>();
			break;
		case 'R':
			(*chains)[index] = new Chain<Ruby*>();
			break;
		case 'A':
			(*chains)[index] = new Chain<Amethyst*>();
			break;
		case 'E':
			(*chains)[index] = new Chain<Emerald*>();
			break;
	}
	chainTypes[index] = cardType;	// update chainType
	//delete toDelete;				// delete old chain
}

void Player::addCardToChain(int index, string cardType, Card* card) {
	Chain_Base* cb = (*chains)[index];
	switch (cardType.at(0)) {
		case 'Q': {
			Chain<Quartz*>* q = static_cast<Chain<Quartz*>*> (cb);
			*q += card;
		}
				  break;
		case 'H': {
			Chain<Hematite*>* h = static_cast<Chain<Hematite*>*> (cb);
			*h += card;
		}
				  break;
		case 'O': {
			Chain<Obsidian*>* o = static_cast<Chain<Obsidian*>*> (cb);
			*o += card;
		}
				  break;
		case 'M': {
			Chain<Malachite*>* m = static_cast<Chain<Malachite*>*> (cb);
			*m += card;
		}
				  break;
		case 'T': {
			Chain<Turquoise*>* t = static_cast<Chain<Turquoise*>*> (cb);
			*t += card;
		}
				  break;
		case 'R': {
			Chain<Ruby*>* r = static_cast<Chain<Ruby*>*> (cb);
			*r += card;
			break;
		}
		case 'A': {
			Chain<Amethyst*>* a = static_cast<Chain<Amethyst*>*> (cb);
			*a += card;
		}
				  break;
		case 'E': {
			Chain<Emerald*>* e = static_cast<Chain<Emerald*>*> (cb);
			*e += card;
		}
				  break;
	}
}

vector<Chain_Base*>* Player::getChains() const {
	return chains;
}

const vector<string> Player::getChainTypes() const {
	return chainTypes;
}

Hand* const Player::getHand() const {
	return hand;
}


const string Player::getName() const {
	return name;
}

const int Player::getNumCoins() const {
	return numCoins;
}

const int Player::getMaxNumChains() const {
	return (chainTypes)[2] == "noChain" ? 2 : 3;
}

const int Player::getNumChains() const {
	int maxNumChains = 0;
	for (size_t i = 0; i < chainTypes.size(); i++) {
		if (chainTypes[i] != " " && chainTypes[i] != "noChain") {
			maxNumChains++;
		}
	}
	return maxNumChains;
}

void Player::buyThirdChain() {
	// Must have 3 coins and two active chains
	if (numCoins >= 3) {
		chainTypes[2] = " ";
	}
	else {
		throw new NotEnoughCoins();
	}
}

void Player::printHand(std::ostream& os, bool b) const {
	os.width(6);
	if (b) {
		*hand << cout;
	}
	else {
		os << "Top: " << (hand->front())->getName() << endl;
	}
}


