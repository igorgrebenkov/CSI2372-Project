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

void printPlayerHand(const Table& t, Player* const player);
void askToBuyChain(const Table& t, Player* const player);
bool tryPlayTopCard(const Table& t, Player* const player, Card*, const string);
void sellChain(const Table& t, Player* const player,
	vector<Chain_Base*>*, Card*, const string);
void askToDiscard(const Table& t, Player* const player);


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
		for (Player* const player : arr) {
			// Print table
			t << cout;

			// Ask the player if they want to buy another chain.
			askToBuyChain(t, player);

			// Draw card from deck to player's hand
			*(player->getHand()) += t.getDeck().draw();

			if (!t.getTradeArea()->empty()) {

			}
			/* Plays topmost card, adds to a chain, ties & sells chains if necessary,
			and plays the next topmost card if the user chooses to.*/
			bool playAgain = true;
			int askCount = 0;
			while (playAgain) {
				// Print player's top card for the turn
				cout << player->getName() << "'s turn." << endl;
				player->printHand(cout, false);

				// get topmost card from hand 
				vector<Chain_Base*>* playerChains = player->getChains();
				Card* cardToPlay = player->getHand()->play();
				const string ctpName = cardToPlay->getName();

				// If a card hasn't been added, a chain must be tied & sold 
				if (!tryPlayTopCard(t, player, cardToPlay, ctpName)) {
					sellChain(t, player, playerChains, cardToPlay, ctpName);
				}

				// Print table again to show updated chains
				t << cout;

				// After the first played card, ask if the user wants to play another card
				if (askCount == 0) {
					cout << "Would you like to play another card? (y/n): " << endl;

					char playAgainChoice = 0;
					cin >> playAgainChoice;

					switch (tolower(playAgainChoice)) {
						case 'y':
							break;
						default:
							playAgain = false;
							break;
					}
				}
				else {
					break;
				}
				askCount++;
			}

			/* Asks the user if they would like to discard an arbitrary card.*/
			askToDiscard(t, player);

			/* Draw three cards from the deck and add to trade area*/
			for (int i = 0; i < 3; i++) {
				if (!t.getDeck().empty()) {
					Card* toTradeArea = t.getDeck().draw();
					*t.getTradeArea() += toTradeArea;
				}
				else {
					break;
				}			
			}

			/* While top card of discard pile matches card in trade area,
			   draw top card of discard pile to trade area*/
			bool matchFound = true;
			while (matchFound) {
				if (!t.getTradeArea()->empty() && !t.getDiscardPile()->empty()) {
					Card* topDiscard = t.getDiscardPile()->top();
					for (Card* c : *t.getTradeArea()) {
						if (topDiscard->getName() == c->getName()) {
							*t.getTradeArea() += t.getDiscardPile()->pickUp();
							break;
						}
						else {
							matchFound = false;
						}
					}

				}
				else {
					break;
				}
			}

			cout << "GAME OVER" << endl;


		}
	}
	return 0;
}

/**
* Function: printPlayerHand
* Description: prints the current player's top card and hand
* Returns: n/a
**/
void printPlayerHand(const Table& t, Player* const player) {
	cout << player->getName() << "'s turn." << endl;
	player->printHand(cout, false);
	player->printHand(cout, true);
}


/**
 * Function: askToBuyChain
 * Description: checks if the user has 2 chains and enough coins
 *              to purchase a third one, and if so, asks them if
 *              they would like to purchase one.
 * Returns: n/a
 **/
void askToBuyChain(const Table& t, Player* const player) {
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
}

/**
* Function: tryPlayTopCard
* Description: attempts to play the top card by looking for
*			   a matching chain first, and failing that,
*			   an empty chain
* Returns: whether the card was added to a chain
**/
bool tryPlayTopCard(const Table& t, Player* const player,
	Card* cardToPlay, const string ctpName) {
	bool isCardAdded = false;
	const vector<string> chainTypes = player->getChainTypes();

	// Check for a chain with matching card type
	for (int i = 0; i < 3; i++) {
		if (chainTypes[i] == ctpName) {
			player->addCardToChain(i, ctpName, cardToPlay);
			isCardAdded = true;
			cout << "Card added to chain " << i + 1 << "." << endl;
		}
	}
	// Check for an available empty chain and add to first one found
	if (!isCardAdded) {
		for (int i = 0; i < 3; i++) {
			if (chainTypes[i] == " ") {
				player->createChain(i, ctpName);
				player->addCardToChain(i, ctpName, cardToPlay);
				isCardAdded = true;
				cout << "Card added to chain " << i + 1 << "." << endl;
				break;
			}
		}
	}
	return isCardAdded;
}

/**
* Function: sellChain
* Description: asks the player which chain they would like to tie and sell
*              and performs the operation
* Returns: n/a
**/
void sellChain(const Table& t, Player* const player,
	vector<Chain_Base*>* playerChains, Card* cardToPlay, const string ctpName) {
	char sellChoice = 0;
	const vector<string> chainTypes = player->getChainTypes();

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
			case '1': {
				Chain<Card*>* ch = static_cast<Chain<Card*>*>((*playerChains)[0]);
				*player += ch->sell();
				for (Card* c : *ch) {
					*t.getDiscardPile() += c;
				}
				player->createChain(0, ctpName);
				player->addCardToChain(0, ctpName, cardToPlay);
				cout << "Chain 1 sold." << endl;
				isChoiceValid = true;
			}
					  break;
			case '2': {
				Chain<Card*>* ch = static_cast<Chain<Card*>*>((*playerChains)[1]);
				*player += ch->sell();
				for (Card* c : *ch) {
					*t.getDiscardPile() += c;
				}
				player->createChain(1, ctpName);
				player->addCardToChain(1, ctpName, cardToPlay);
				cout << "Chain 2 sold." << endl;
				isChoiceValid = true;
			}
					  break;
			case '3':
				if (player->getMaxNumChains() == 3 && chainTypes[3] != "noChain") {
					Chain<Card*>* ch = static_cast<Chain<Card*>*>((*playerChains)[2]);
					*player += ch->sell();
					for (Card* c : *ch) {
						*t.getDiscardPile() += c;
					}
					player->createChain(2, ctpName);
					player->addCardToChain(2, ctpName, cardToPlay);
					cout << "Chain 3 sold." << endl;
					isChoiceValid = true;
				}
				else {
					cout << "You do not currently have a third chain." << endl;
				}
				break;
			default:
				cout << "Please enter a valid number in the range." << endl;
				break;
		}
	}
}

/**
* Function: askToDiscard
* Description: asks the player if they would like to discard one
*              arbitrary card and performs the operation
* Returns: n/a
**/
void askToDiscard(const Table& t, Player* const player) {
char discardCardChoice = 0;
	cout << "Would you like to discard one of your cards? (y/n): " << endl;
	cin >> discardCardChoice;

	if (tolower(discardCardChoice) == 'y') {
		player->printHand(cout, true);
		int handUpperRange = (player->getHand()->size() - 1);
		int cardDiscardIndex = 0;
		bool isCardAdded = false;
		while (!isCardAdded) {
			cout << "Which card would you like to discard? (1 - " << handUpperRange + 1 << "): ";
			cin >> cardDiscardIndex;

			// Check for valid numeric input
			if (cin.fail()) {
				cout << "Please enter a valid card index." << endl;
				cin.clear();
				cin.ignore();
			}
			else {
				// If valid index, discard selected card from hand
				if (cardDiscardIndex >= 1 && cardDiscardIndex <= handUpperRange + 1) {
					*(t.getDiscardPile()) += (*player->getHand())[cardDiscardIndex - 1];
					isCardAdded = true;
				}
			}
		}
	}
}



