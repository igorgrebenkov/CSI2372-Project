#include <string>
#include <iostream>
#include <queue>

#include "Card.h"
#include "CardFactory.h"
#include "DiscardPile.h"
#include "TradeArea.h"
#include "Player.h"
#include "Chain.h"
#include "Hand.h"
#include "Table.h"

#define NUM_PLAYERS 2

using namespace std;

int main() {
	Table t("John", "Ruddiger");

	Player* arr[NUM_PLAYERS];
	t.getPlayers(arr);

	/*
	Deck d = t.getDeck();

	Card* b = d[0];
	Chain<Emerald> ch;
	ch += b;
	ch << cout;
	*/

	for (Player* p : arr) {
		// Option for buying third chain
		if (p->getNumCoins() >= 3 &&
			p->getMaxNumChains() == 2) {

			char chainChoice = 0;

			cout << "Buy an extra chain? (y/n): ";
			cin >> chainChoice;
			
			switch (tolower(chainChoice)) {
				case 'y':
					p->buyThirdChain();
					break;
				default:
					break;
			}
		}

		// Draw card from deck to player
		*(p->getHand()) += t.getDeck().draw();

		if ((t.getTradeArea())->empty()) {
			Card* play = p->getHand()->play();
			string cardName = play->getName();
			vector<Chain_Base*> playerChains;
			playerChains = p->getChains();
			Chain<Ruby*>* c = static_cast<Chain<Ruby*>*>(playerChains[0]);
			Deck d = t.getDeck();
			//d << cout;
			*c += d[7];
			*c += d[42];
		}

	}

	
	return 0;
}