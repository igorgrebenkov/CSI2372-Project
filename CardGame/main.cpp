#include <string>
#include <iostream>
#include <queue>
#include <chrono>
#include <random>
#include <algorithm>
#include <fstream>

#include "Card.h"
#include "CardFactory.h"
#include "DiscardPile.h"
#include "TradeArea.h"
#include "Player.h"
#include "Chain.h"
#include "Hand.h"
#include "Table.h"
#include "CardFactory.h"

#define NUM_PLAYERS 2

using namespace std;

void askToPauseGame(Table& t);
void printPlayerHand(const Table& t, Player* const player);
void askToBuyChain(Player* const player);
void playCards(Table& t, Player* const player);
bool tryPlayTopCard(const Table& t, Player* const player, Card*, const string);
void sellChain(const Table& t, Player* const player,
	vector<Chain_Base*>*, Card*, const string);
void askToDiscard(const Table& t, Player* const player);
void drawThreeCardsToTradeArea(Table& t);
void putMatchingDiscardToTradeArea(Table& t);
void askToChainInTradeArea(Table& t, Player* const player);
void displayWinner(const Table& t);

int main() {
	Table* t;

	ifstream infile;
	infile.open("gameSave.dat");
	/* Load game from file if file exists. */
	if (infile) {
		const CardFactory* cf = CardFactory::getFactory();
		t = new Table(infile, cf);
		infile.close();
	}
	else {
		/* Get player names. */
		string p1Name, p2Name = "";
		std::cout << "Player 1 name: ";
		cin >> p1Name;
		std::cout << "Player 2 name: ";
		cin >> p2Name;

		/* Init table. */
		t = new Table(p1Name, p2Name);
	}

	/* Create player array. */
	Player* arr[NUM_PLAYERS];
	t->getPlayers(arr);

	bool firstRun = true; // flag to indicate first run of main loop
	while (!t->getDeck().empty()) {
		for (Player* const player : arr) {

			/* Make sure we don't ask to pause the game on
			the first iteration of the main loop. */
			if (!firstRun) {
				askToPauseGame(*t);
				firstRun = false;
			}
			else {
				firstRun = false;
			}

			/* The last step where two cards are drawn from the deck may result
			   in an empty deck. If this happens during Player 1's turn, Player 2
			   might try to draw from the empty deck. So we break out of this loop
			   in that case. */
			if (t->getDeck().empty()) {
				break;
			}

			/* Print table. */
			*t << std::cout;

			/* Asks the player if they want to buy another chain. */
			askToBuyChain(player);

			/* Draws card from deck to player's hand. */
			*(player->getHand()) += t->getDeck().draw();

			/* Asks user if they want to chain each card in the trade area.*/
			askToChainInTradeArea(*t, player);

			/* Plays one or two cards (if the player chooses to play two cards) */
			playCards(*t, player);

			/* Asks the user if they would like to discard an arbitrary card.*/
			askToDiscard(*t, player);

			/* Draws three cards from the deck to the trade area. */
			drawThreeCardsToTradeArea(*t);

			/* While top card of discard pile matches card in trade area,
			draw top card of discard pile to trade area*/
			putMatchingDiscardToTradeArea(*t);

			/* Asks user if they want to chain each card in the trade area.*/
			askToChainInTradeArea(*t, player);

			// Draw two cards from the deck
			for (int i = 0; i < 1; i++) {
				if (!t->getDeck().empty()) {
					*player->getHand() += t->getDeck().draw();
				}
			}
		}
	}

	/* Display who won the game. */
	displayWinner(*t);

	delete t; // delete table
	return 0;
}

/**
* Function: askToPauseGame
* Description: asks the user if they want to pause the game,
*              and serializes game data to a file if so
* Returns: n/a
**/
void askToPauseGame(Table& t) {
	string pauseChoice = "";
	cout << "Would you like to save the game and exit? (yes/n): " << endl;
	cin >> pauseChoice;
	transform(pauseChoice.begin(), pauseChoice.end(), pauseChoice.begin(), 
	(int(*)(int)) tolower);

	if (pauseChoice == "yes") {
		ofstream outFile;
		outFile.open("gameSave.dat");
		t.print(outFile);
		outFile.close();
		exit(1);
	}
}


/**
* Function: printPlayerHand
* Description: prints the current player's top card and hand
* Returns: n/a
**/
void printPlayerHand(const Table& t, Player* const player) {
	player->printHand(std::cout, false);
}


/**
 * Function: askToBuyChain
 * Description: checks if the user has 2 chains and enough coins
 *              to purchase a third one, and if so, asks them if
 *              they would like to purchase one.
 * Returns: n/a
 **/
void askToBuyChain(Player* const player) {
	if (player->getNumCoins() >= 3 &&
		player->getMaxNumChains() == 2) {

		char chainBuyChoice = 0;

		std::cout << player->getName() << ": Buy an extra chain? (y/n): ";
		cin >> chainBuyChoice;

		switch (tolower(chainBuyChoice)) {
			case 'y':
				player->buyThirdChain();
				break;
		}
	}
}

/**
* Function: playCards
* Description: plays one card, and then plays another card if the user chooses to
* Returns: n/a
**/
void playCards(Table& t, Player* const player) {
	/* Plays topmost card, adds to a chain, ties & sells chains if necessary,
	and plays the next topmost card if the user chooses to.*/
	bool playAgain = true;
	int askCount = 0;
	while (playAgain) {
		cout << "Playing card: ";
		player->printHand(std::cout, false);

		// get topmost card from hand 
		vector<Chain_Base*>* playerChains = player->getChains();
		Card* cardToPlay = player->getHand()->play();
		const string ctpName = cardToPlay->getName();

		// If a card hasn't been added, a chain must be tied & sold 
		if (!tryPlayTopCard(t, player, cardToPlay, ctpName)) {
			sellChain(t, player, playerChains, cardToPlay, ctpName);
		}

		// Print table again to show updated chains
		t << std::cout;

		// After the first played card, ask if the user wants to play another card
		if (askCount == 0) {
			std::cout << player->getName()
				<< ": Would you like to play another card? (y/n): ";

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
			std::cout << "Card added to chain " << i + 1 << "." << endl;
		}
	}
	// Check for an available empty chain and add to first one found
	if (!isCardAdded) {
		for (int i = 0; i < 3; i++) {
			if (chainTypes[i] == " ") {
				player->createChain(i, ctpName);
				player->addCardToChain(i, ctpName, cardToPlay);
				isCardAdded = true;
				std::cout << "Card added to chain " << i + 1 << "." << endl;
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
		std::cout << player->getName()
			<< ": Chain ended. Which chain would you like to sell? (1-2): ";
	}
	else {
		std::cout << player->getName()
			<< ": Chain ended. Which chain would you like to sell? (1-3): ";
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
				std::cout << "Chain 1 sold." << endl;
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
				std::cout << "Chain 2 sold." << endl;
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
					std::cout << "You do not currently have a third chain." << endl;
				}
				break;
			default:
				std::cout << "Please enter a valid number in the range: ";
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
	std::cout << player->getName()
		<< ": Would you like to discard one of your cards? (y/n): ";
	cin >> discardCardChoice;

	if (tolower(discardCardChoice) == 'y') {
		player->printHand(std::cout, true);
		int handUpperRange = (player->getHand()->size() - 1);
		int cardDiscardIndex = 0;
		bool isCardAdded = false;
		while (!isCardAdded) {
			std::cout << "Which card would you like to discard? (1 - "
				<< handUpperRange + 1 << "): ";
			cin >> cardDiscardIndex;

			// Check for valid numeric input
			if (cin.fail()) {
				std::cout << "Please enter a valid card index." << endl;
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

/**
* Function: drawThreeCardsToTradeArea
* Description: draws three cards from the deck and adds them to the trade area
* Returns: n/a
**/
void drawThreeCardsToTradeArea(Table& t) {
	for (int i = 0; i < 3; i++) {
		if (!t.getDeck().empty()) {
			Card* toTradeArea = t.getDeck().draw();
			*t.getTradeArea() += toTradeArea;
		}
		else {
			break;
		}
	}
}

/**
* Function: putMatchingDiscardToTradeArea
* Description: inserts the top card from the discard pile into
*              the trade area while the top card matches any card
*			   in the trade area
* Returns: n/a
**/
void putMatchingDiscardToTradeArea(Table& t) {
	/* If a player sells a chain, they all go on the discard pile.
	   If the next player gets a card in their trade area that matches
	   the card type of the last player's sold chain, they will be able
	   to add that other person's whole chain to theirs.

	   This was pointed out on the CSI2372 Blackboard discussion board
	   by another student.

	   So, to avoid this, we shuffle the discard pile before this step.
	*/
	unsigned seed = chrono::system_clock::now().time_since_epoch().count();
	shuffle(begin(*t.getDiscardPile()),
		end(*t.getDiscardPile()),
		default_random_engine(seed));

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
}

/**
* Function: askToChainInTradeArea
* Description: asks the user if they would like to chain a card
*              in the trade area, one by one.
* Returns: n/a
**/
void askToChainInTradeArea(Table& t, Player* const player) {
	char chainChoice = 0;

	bool doneChaining = false;
	if (!t.getTradeArea()->empty()) {
		while (!doneChaining && !t.getTradeArea()->empty()) {
			t << cout;
			cout << player->getName() << ": "
				<< "Would you like to chain a card in the trade area? (y/n): ";
			cin >> chainChoice;

			if (chainChoice == 'y') {
				string toChain;
				cout << "Enter the full name of the card you'd like to chain: ";
				cin >> toChain;
				Card* card = t.getTradeArea()->trade(toChain);

				if (card != NULL) {
					vector<Chain_Base*>* playerChains = player->getChains();
					const string ctpName = card->getName();

					// If a card hasn't been added, a chain must be tied & sold 
					if (!tryPlayTopCard(t, player, card, ctpName)) {
						sellChain(t, player, playerChains, card, ctpName);
					}
				}
			} else {
				doneChaining = true;
			}
		}
	}
}

/**
* Function: displayWinner
* Description: checks who won the game and displays their name
* Returns: n/a
**/
void displayWinner(const Table& t) {
	string winningPlayer = "";
	t.win(winningPlayer);
	cout << endl;
	cout << "------------------------------------------------------------" << endl;
	std::cout << "\t\t" << winningPlayer << " wins!" << endl;
	cout << "------------------------------------------------------------" << endl;
	cout << endl;

	// Loops until user types exit to quit the game. This prevents the
	// user from accidentally closing the window when a game has ended,
	// which would prevent them from seeing who won.
	string exitChoice;
	while (exitChoice != "exit") {
		cout << "Type \"exit\" to exit the game: ";
		cin >> exitChoice;
		transform(exitChoice.begin(), exitChoice.end(), exitChoice.begin(), 
		(int(*)(int)) tolower);
	}

	remove("gameSave.dat"); // delete the saved game
}







