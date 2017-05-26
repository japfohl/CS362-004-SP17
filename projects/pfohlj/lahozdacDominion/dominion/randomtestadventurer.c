#include "randomTest.h"

void randomTestAdventurer(unsigned long count) {
	
	struct gameState state;
	struct gameState snapshot;
	srand(time(NULL));
	unsigned long i;
	int player;
	int flag;
	struct test t;

	for (i = 0; i < count; ++i) {
		int j,k;
		int seed = rand();
		randomizeGameState(&state,seed);
		player = state.whoseTurn;

		/*Give the player an adventurer; randomizeGameState ensures the current player
		has at least one card in hand*/
		state.hand[player][0] = adventurer;

		snapshot = state;

		t.preCond = &snapshot;

		flag = playAdventurer(&state);

		t.postCond = &state;
		t.err = 0;
		t.errCount = 0;
		t.testNo = i + 1;

		//Function returned an error
		if (flag == -1) {
			addError(&t,"Function returned an error.");
		}
		//Check various state variables that should not have changed
		if (state.numPlayers != snapshot.numPlayers) {
			addError(&t,"State error: numPlayers changed.");
		}
		if (state.outpostPlayed != snapshot.outpostPlayed) {
			addError(&t,"State error: outpostPlayed changed.");
		}
		if (state.whoseTurn != snapshot.whoseTurn) {
			addError(&t,"State error: whoseTurn changed.");
		}
		if (state.outpostTurn != snapshot.outpostTurn) {
			addError(&t,"State error: outpostTurn changed.");
		}
		if (state.phase != snapshot.phase) {
			addError(&t,"State error: whoseTurn changed.");
		}
		if (state.numActions != snapshot.numActions) {
			addError(&t,"State error: numActions changed.");
		}
		if (state.coins != snapshot.coins) {
			addError(&t,"State error: coins changed.");
		}
		if (state.numBuys != snapshot.numBuys) {
			addError(&t,"State error: numBuys changed.");
		}
		for (j = 0; j < treasure_map; ++j) {
			if (state.supplyCount[j] != snapshot.supplyCount[j]) {
				addError(&t,"State error: supplyCount(s) changed.");
			}
			if (state.embargoTokens[j] != snapshot.embargoTokens[j]) {
				addError(&t,"State error: embargoTokens changed.");
			}
		}
		//Check the status of other players
		for (j = 0; j < state.numPlayers; ++j) {
			if (j != state.whoseTurn) {
				if (state.handCount[j] != snapshot.handCount[j]) {
					addError(&t,"State error: other player handCount changed.");
				}
				for (k = 0; k < state.handCount[j]; ++k) {
					if (state.hand[j][k] != snapshot.hand[j][k]) {
						addError(&t,"State error: other player hand changed.");
						break;
					}
				}
				if (state.deckCount[j] != snapshot.deckCount[j]) {
					addError(&t,"State error: other player deckCount changed.");
				}
				for (k = 0; k < state.deckCount[j]; ++k) {
					if (state.deck[j][k] != snapshot.deck[j][k]) {
						addError(&t,"State error: other player deck changed.");
						break;
					}
				}
				if (state.discardCount[j] != snapshot.discardCount[j]) {
					addError(&t,"State error: other player discardCount changed.");
				}
				for (k = 0; k < state.discardCount[j]; ++k) {
					if (state.discard[j][k] != snapshot.discard[j][k]) {
						addError(&t,"State error: other player discard changed.");
						break;
					}
				}
			}
		}
		//Check for things we know should have changed
		checkTreasures(&t);

		if (t.err == 1)
			printErr(&t);
		else
			printf("Test %d successful.\n",t.testNo);
	}
}

void checkTreasures(struct test* t) {
	enum CARDSOURCE {
		hand = 0,
		deck,
		discard,
		played
	};
	
	int preTreasure[played + 1][treasure_map + 1];
	int postTreasure[played + 1][treasure_map + 1];
	int player = t->preCond->whoseTurn;

	preTreasure[hand][copper] = getCardHandCount(player,copper,t->preCond);
	preTreasure[hand][silver] = getCardHandCount(player,silver,t->preCond);
	preTreasure[hand][gold] = getCardHandCount(player,gold,t->preCond);

	preTreasure[deck][copper]= getCardDeckCount(player,copper,t->preCond);
	preTreasure[deck][silver] = getCardDeckCount(player,silver,t->preCond);
	preTreasure[deck][gold] = getCardDeckCount(player,gold,t->preCond);

	preTreasure[discard][copper] = getCardDiscardCount(player,copper,t->preCond);
	preTreasure[discard][silver] = getCardDiscardCount(player,silver,t->preCond);
	preTreasure[discard][gold] = getCardDiscardCount(player,gold,t->preCond);

	postTreasure[hand][copper] = getCardHandCount(player,copper,t->postCond);
	postTreasure[hand][silver] = getCardHandCount(player,silver,t->postCond);
	postTreasure[hand][gold] = getCardHandCount(player,gold,t->postCond);

	postTreasure[deck][copper]= getCardDeckCount(player,copper,t->postCond);
	postTreasure[deck][silver] = getCardDeckCount(player,silver,t->postCond);
	postTreasure[deck][gold] = getCardDeckCount(player,gold,t->postCond);

	postTreasure[discard][copper] = getCardDiscardCount(player,copper,t->postCond);
	postTreasure[discard][silver] = getCardDiscardCount(player,silver,t->postCond);
	postTreasure[discard][gold] = getCardDiscardCount(player,gold,t->postCond);

	int preHand = preTreasure[hand][copper] + preTreasure[hand][silver] + preTreasure[hand][gold];
	int preDeck = preTreasure[deck][copper] + preTreasure[deck][silver] + preTreasure[deck][gold];
	int preDiscard = preTreasure[discard][copper] + preTreasure[discard][silver] + preTreasure[discard][gold];

	int postHand = postTreasure[hand][copper] + postTreasure[hand][silver] + postTreasure[hand][gold];
	int postDeck = postTreasure[deck][copper] + postTreasure[deck][silver] + postTreasure[deck][gold];
	int postDiscard = postTreasure[discard][copper] + postTreasure[discard][silver] + postTreasure[discard][gold];

	//Get how many treasures we drew; could be less than 2
	int draw = preDeck + preDiscard;
	if (draw > 2)
		draw = 2;

	//Check if we had to shuffle the discard
	int shuffleFlag = preDeck - 2;
	if (shuffleFlag < 0)
		shuffleFlag = 1;
	else
		shuffleFlag = 0;

	//Check hand status
	if (postHand < preHand + draw) {
		addError(t,"Error: Not enough treasures in hand.");
	}
	if (postHand > preHand + draw) {
		addError(t,"Error: Too many treasures in hand.");
	}
	if (t->postCond->handCount[player] > (t->preCond->handCount[player] + draw - 1)) {
		addError(t,"Error: Too many cards in hand.");
	}
	if (t->postCond->handCount[player] < (t->preCond->handCount[player] + draw - 1)) {
		addError(t,"Error: Not enough cards in hand.");
	}

	//Check deck status
	if (shuffleFlag == 0) {
		if (t->postCond->deckCount[player] > (t->preCond->deckCount[player] - draw)) {
			addError(t,"Error: Too many cards in draw deck, no shuffle scenario.");
		}
		if (postDeck < preDeck - draw) {
			addError(t,"Error: Not enough treasures in deck, no shuffle scenario.");
		}
		if (postDeck > preDeck - draw) {
			addError(t,"Error: Too many treasures in deck, no shuffle scenario.");
		}
	}
	else if (draw < 2) {
		if (t->postCond->deckCount[player] > 0) {
			addError(t,"Error: Too many cards in draw deck, insufficient treasure scenario.");
		}
	}

	//Check discard status
	if (shuffleFlag == 0) {
		int revealed = t->preCond->deckCount[player] - t->postCond->deckCount[player] - draw;

		if (t->postCond->discardCount[player] > (t->preCond->discardCount[player] + revealed)) {
			addError(t,"Error: Too many cards in discard, no shuffle scenario.");
		}
		if (t->postCond->discardCount[player] < (t->preCond->discardCount[player] + revealed)) {
			addError(t,"Error: Not enough cards in discard, no shuffle scenario.");
		}
	}
	else if (draw < 2) {
		if (t->postCond->discardCount[player] > (t->preCond->discardCount[player] + t->preCond->deckCount[player] - draw)) {
			addError(t,"Error: Too many cards in discard, insufficient treasure scenario");
		}
		if (t->postCond->discardCount[player] < (t->preCond->discardCount[player] + t->preCond->deckCount[player] - draw)) {
			addError(t,"Error: Not enough cards in discard, insufficient treasure scenario.");
		}
	}
	else {
		if (postDiscard > 0) {
			addError(t,"Error: Too many treasure cards in discard, reshuffle scenario.");
		}
	}

	//Check played cards
	if (t->postCond->playedCardCount < t->preCond->playedCardCount + 1) {
		addError(t,"Error: playedCardCount not incremented.");
	}
	if (t->postCond->playedCardCount > t->preCond->playedCardCount + 1) {
		addError(t,"Error: playedCardCount increased by more than 1.");
	}
	if (t->postCond->playedCards[t->postCond->playedCardCount - 1] != adventurer) {
		addError(t,"Error: Last played card is not adventurer");
	}

}



