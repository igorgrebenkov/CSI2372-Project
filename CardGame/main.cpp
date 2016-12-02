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
			const Card* play = p->getHand()->play();
			vector<Chain_Base<Card*>*> playerChains;
			playerChains = p->getChains();
			Chain_Base<Card*>* chain = playerChains[0];
			*chain += play;
		}

	}

	
	return 0;
}