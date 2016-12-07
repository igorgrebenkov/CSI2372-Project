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

void askBuyChain(Table t);

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
			// Print table
			t << cout;
			// Option for buying third chain
			if (player->getNumCoins() >= 3 &&
				player->getMaxNumChains() == 2) {

				char chainBuyChoice = 0;

				cout << "Buy an extra chain? (y/n): ";
				cin >> chainBuyChoice;

				switch (tolower(chainBuyChoice)) {
					case 'y':
						player->buyThirdChain();
						break;
				}
			}

			// Draw card from deck to player
			*(player->getHand()) += t.getDeck().draw();

			if ((t.getTradeArea())->empty()) {
				// Print top card, then hand
				cout << player->getName() << "'s turn." << endl;
				player->printHand(cout, false);
				player->printHand(cout, true);

				// get topmost card from hand
				Card* cardToPlay = player->getHand()->play();
				string ctpName = cardToPlay->getName();

				
					
				vector<Chain_Base*>* playerChains = player->getChains();

				int i = 0;
				bool isCardAdded = false;
				const vector<string> chainTypes = player->getChainTypes();

				// Check for a chain with matching card type
				for (int i = 0; i < 3; i++) {
					if (chainTypes[i] == ctpName) {
						player->addCardToChain(i, ctpName, cardToPlay);
						isCardAdded = true;
					}
				}
				// Check for an available empty chain
				if (!isCardAdded) {
					for (int i = 0; i < 3; i++) {
						if (chainTypes[i] == " ") {
							player->createChain(i, ctpName);
							player->addCardToChain(i, ctpName, cardToPlay);
							isCardAdded = true;
							break;
						}
					}
				}
				// If a card hasn't been added, chains must be tied/sold 
				// or player must buy a third chain (if possible)
				if (!isCardAdded) {
					int sellChoice = 0;
					if (player->getMaxNumChains() == 2) {
						cout << "Chain ended. Which chain would you like to sell? (1-2)" << endl;
					}
					else {
						cout << "Chain ended. Which chain would you like to sell? (1-3)" << endl;
					}
					
					bool isChoiceValid = false;
					while (!isChoiceValid) {
						cin >> sellChoice;
						switch (sellChoice) {
							case 1: {
								Chain<Card*>* ch = static_cast<Chain<Card*>*>((*playerChains)[0]);
								*player += ch->sell();
								for (Card* c : *ch) {
									*t.getDiscardPile() += c;
								}
								player->createChain(0, ctpName);
								player->addCardToChain(0, ctpName, cardToPlay);
								isChoiceValid = true;
							}
								break;
							case 2: {
								Chain<Card*>* ch = static_cast<Chain<Card*>*>((*playerChains)[1]);
								*player += ch->sell();
								for (Card* c : *ch) {
									*t.getDiscardPile() += c;
								}
								player->createChain(1, ctpName);
								player->addCardToChain(1, ctpName, cardToPlay);
								isChoiceValid = true;
							}
								break;
							case 3: 
								if (player->getMaxNumChains() == 3 && chainTypes[3] != "noChain") {
									Chain<Card*>* ch = static_cast<Chain<Card*>*>((*playerChains)[2]);
									*player += ch->sell();
									for (Card* c : *ch) {
										*t.getDiscardPile() += c;
									}
									player->createChain(2, ctpName);
									player->addCardToChain(2, ctpName, cardToPlay);
									isChoiceValid = true;
								}
								break;
						}
						if (!isChoiceValid) {
							cout << "Please enter a valid number in the range." << endl;
						}
					}
				}
				
			}
		}
	}


	return 0;
}

void askBuyChain(Table t) {

}
