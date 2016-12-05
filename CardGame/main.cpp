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

	
	Deck d = t.getDeck();
	/*
	Card* b = d[0];
	Chain<Emerald> ch;
	ch += b;
	ch << cout;
	*/
	while (!t.getDeck().empty()) {
		for (Player* player : arr) {
			// Option for buying third chain
			if (player->getNumCoins() >= 3 &&
				player->getMaxNumChains() == 2) {

				char chainChoice = 0;

				cout << "Buy an extra chain? (y/n): ";
				cin >> chainChoice;

				switch (tolower(chainChoice)) {
					case 'y':
						player->buyThirdChain();
						break;
					default:
						break;
				}
			}

			// Draw card from deck to player
			*(player->getHand()) += t.getDeck().draw();

			if ((t.getTradeArea())->empty()) {
				// get topmost card from hand
				Card* cardToPlay = player->getHand()->play();
				string ctpName = cardToPlay->getName();

				vector<Chain_Base*>* playerChains = player->getChains();

				int i = 0;
				bool cardAddedToChain = false;
				const vector<string> chainTypes = player->getChainTypes();

				// Check for a chain with matching card type
				for (int i = 0; i < 3; i++) {
					if (chainTypes[i] == ctpName) {
						player->addCardToChain(i, ctpName, cardToPlay);
					}
				}
				// Check for an available empty chain
				if (!cardAddedToChain) {
					for (int i = 0; i < 3; i++) {
						if (chainTypes[i] == " ") {
							player->createChain(i, ctpName);
							player->addCardToChain(i, ctpName, cardToPlay);
							break;
						}
					}
				}
				*player << cout;


				// If a card hasn't been added, chains must be tied/sold 
				// or player must buy a third chain (if possible)
				if (!cardAddedToChain) {
					if (chainTypes[2] == "empty") {
						cout << "\nmust sell or buy a chain!\n" << endl;
					}
					else {
						cout << "must sell a chain!" << endl;
					}
				}
				else {

				}
			}
		}
	}


	return 0;
}