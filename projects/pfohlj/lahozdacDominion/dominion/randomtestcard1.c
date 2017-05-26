#include "randomTest.h"

void randomTestSmithy(unsigned long count) {
	
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

		/*Give the player a Smithy; randomizeGameState ensures the current player
		has at least one card in hand*/
		state.hand[player][0] = smithy;

		snapshot = state;

		t.preCond = &snapshot;

		flag = playSmithy(&state,0);

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
		//Check for things we know could or should have changed

		int shuffleFlag = snapshot.deckCount[player] - 3;
		if (shuffleFlag < 0)
			shuffleFlag = 1;
		else
			shuffleFlag = 0;

		//Discard should be the same unless we had to shuffle it, in which case it should be zero
		if (shuffleFlag == 0) {
			if (state.discardCount[player] != snapshot.discardCount[player])
				addError(&t,"Error: discardCount changed, no shuffle scenario.");
		}
		else {
			if (state.discardCount[player] != 0)
				addError(&t,"Error: discardCount > 0, shuffle scenario.");
		}

		//Check played cards
		if (state.playedCardCount < snapshot.playedCardCount + 1) {
			addError(&t,"Error: playedCardCount not incremented.");
		}
		if (state.playedCardCount > snapshot.playedCardCount + 1) {
			addError(&t,"Error: playedCardCount increased by more than 1.");
		}
		if (state.playedCards[state.playedCardCount - 1] != smithy) {
			addError(&t,"Error: Last played card is not smithy");
		}

		//Check hand		
		int draw = snapshot.deckCount[player] + snapshot.discardCount[player];
		if (draw > 3)
			draw = 3;

		if (state.handCount[player] < (snapshot.handCount[player] + draw - 1)) {
			addError(&t,"Error: Not enough cards in hand");
		}
		if (state.handCount[player] > (snapshot.handCount[player] + draw - 1)) {
			addError(&t,"Error: Too many cards in hand");
		}

		//Check deck
		if (shuffleFlag == 0) {
			if (state.deckCount[player] > snapshot.deckCount[player] - 3) {
				addError(&t,"Error: Too many cards in draw deck, no shuffle scenario.");
			}
			if (state.deckCount[player] < snapshot.deckCount[player] - 3) {
				addError(&t,"Error: Not enough cards in draw deck, no shuffle scenario.");
			}
		}
		else {
			if (state.deckCount[player] > (snapshot.deckCount[player] + snapshot.discardCount[player] - draw)) {
				addError(&t,"Error: Too many cards in draw deck, shuffle scenario.");
			}
			if (state.deckCount[player] < (snapshot.deckCount[player] + snapshot.discardCount[player] - draw)) {
				addError(&t,"Error: Not enough cards in draw deck, shuffle scenario.");
			}
		}

		if (t.err == 1)
			printErr(&t);
		else
			printf("Test %d successful.\n",t.testNo);
	}
}