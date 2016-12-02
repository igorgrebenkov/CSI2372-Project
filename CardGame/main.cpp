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
		cout << p->getName();
	}

	
	return 0;
}