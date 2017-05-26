#include "unitTestUtilities.h"

void randomizeGameState (struct gameState* state, int seed) {
	int i, j, cards, deck, discard, hand;
	srand(seed);
	
	state->numPlayers = (rand() % MAX_PLAYERS) + 1;

	//Populate each supply pile with 0-20 cards and 0-2 embargo tokens
	for (i = 0; i < treasure_map; ++i) {
		state->supplyCount[i] = rand() % 21;
		state->embargoTokens[i] = rand() % 3;
	}

	state->outpostPlayed = rand() % 2;
	state->outpostTurn = rand() % 2;
	state->whoseTurn = rand() % state->numPlayers;
	state->phase = 0;
	state->numActions = rand() % 3;
	state->numBuys = rand() % 3;

	for (i = 0; i < state->numPlayers; ++i) {
		cards = rand() % MAX_DECK + 1;
		//Omit a + 1 here so that deck is at most cards - 1
		deck = rand() % cards;
		//Since deck is at most cards - 1, hand is at least 1
		hand = cards - deck;
		//Here discard could equal deck
		discard = rand() % (deck + 1);

		//Randomize draw deck
		state->deckCount[i] = deck - discard;
		for (j = 0; j < state->deckCount[i]; ++j)
			state->deck[i][j] = rand() % (treasure_map + 1);

		//Randomize discard
		state->discardCount[i] = discard;
		for (j = 0; j < state->discardCount[i]; ++j)
			state->discard[i][j] = rand() % (treasure_map + 1);

		//If the current player, randomize played cards
		if (i == state->whoseTurn) {
			//Omit + 1 so that player will have at least one card in hand, for testing
			state->playedCardCount = rand() % hand;
			state->handCount[i] = hand - state->playedCardCount;

			for (j = 0; j < state->playedCardCount; ++j)
				state->playedCards[j] = rand() % (treasure_map + 1);
		}
		else
			state->handCount[i] = hand;

		//Randomize hand
		for(j = 0; j < state->handCount[i]; ++j)
			state->hand[i][j] = rand() % (treasure_map + 1);
	}

	//Get coin count for the current player
	state->coins = updateCoins(state->whoseTurn,state,0);
}

int cmpGameState (struct gameState* gs1, struct gameState* gs2) {
	int i, j, k, l;

	if(gs1->numPlayers != gs2->numPlayers)
		return 0;
	else if(gs1->whoseTurn != gs2->whoseTurn)
		return 0;
	else if(gs1->outpostPlayed != gs2->outpostPlayed)
		return 0;
	else if(gs1->outpostTurn != gs2->outpostTurn)
		return 0;
	else if(gs1->phase != gs2->phase)
		return 0;
	else if(gs1->numActions != gs2->numActions)
		return 0;
	else if(gs1->coins != gs2->coins)
		return 0;
	else if(gs1->numBuys != gs2->numBuys)
		return 0;
	else if(gs1->playedCardCount != gs2->playedCardCount)
		return 0;

	for (i = 0; i <= treasure_map; i++) {
		if(gs1->supplyCount[i] != gs2->supplyCount[i])
			return 0;
		else if(gs1->embargoTokens[i] != gs2->embargoTokens[i])
			return 0;
	}

	for (i = 0; i < MAX_PLAYERS; i++) {
		if(gs1->handCount[i] != gs2->handCount[i])
			return 0;
		else if(gs1->deckCount[i] != gs2->deckCount[i])
			return 0;
		else if(gs1->discardCount[i] != gs2->discardCount[i])
			return 0;

		for (j = 0; j < gs1->handCount[i]; j++) {
			if(gs1->hand[i][j] != gs2->hand[i][j])
				return 0;
		}

		for (k = 0; k < gs1->deckCount[i]; k++) {
			if(gs1->deck[i][k] != gs2->deck[i][k])
				return 0;
		}

		for (l = 0; l < gs1->discardCount[i]; l++) {
			if(gs1->discard[i][l] != gs2->discard[i][l])
				return 0;
		}
	}

	for (i = 0; i < gs1->playedCardCount; i++) {
		if(gs1->playedCards[i] != gs2->playedCards[i])
			return 0;
	}

	return 1;
}

void printTest(struct test* t) {
	printf("GAME STATE:\n");
	printf("\n");
	printf("numPlayers: %d %d\n",t->preCond->numPlayers,t->postCond->numPlayers);
	printf("outpostPlayed: %d %d\n",t->preCond->outpostPlayed,t->postCond->outpostPlayed);
	printf("outpostTurn: %d %d\n",t->preCond->outpostTurn,t->postCond->outpostTurn);
	printf("whoseTurn: %d %d\n",t->preCond->whoseTurn,t->postCond->whoseTurn);
	printf("phase: %d %d\n",t->preCond->phase,t->postCond->phase);
	printf("numActions: %d %d\n",t->preCond->numActions,t->postCond->numActions);
	printf("coins: %d %d\n",t->preCond->coins,t->postCond->coins);
	printf("numBuys: %d %d\n",t->preCond->numBuys,t->postCond->numBuys);
	printf("\n");
	printf("PLAYER STATES:\n");
	printf("\n");

	int i;
	for (i = 0; i < t->postCond->numPlayers; ++i) {
		printf("PLAYER %d:\n",i + 1);
		printf("\n");
		printf("handCount: %d %d\n",t->preCond->handCount[i],t->postCond->handCount[i]);
	}
}

void printErr(struct test* t) {
	int i;

	printf("Test No. %d had %d Errors:\n",t->testNo,t->errCount);
	for(i = 0; i < t->errCount; ++i) {
		printf("%s\n",t->status[i]);
	}
}

int getCardDeckCount (int player, int card, struct gameState* state) {
	int count = 0;
	int i;

	for (i = 0; i < state->deckCount[player]; ++i) {
		if (state->deck[player][i] == card)
			count++;
	}

	return count;
}

int getCardHandCount (int player, int card, struct gameState* state) {
	int count = 0;
	int i;

	for (i = 0; i < state->handCount[player]; ++i) {
		if (state->hand[player][i] == card)
			count++;
	}

	return count;
}

int getCardDiscardCount (int player, int card, struct gameState* state) {
	int count = 0;
	int i;

	for (i = 0; i < state->discardCount[player]; ++i) {
		if (state->discard[player][i] == card)
			count++;
	}

	return count;
}

int getCardPlayedCount (int card, struct gameState* state) {
	int count = 0;
	int i;

	for (i = 0; i < state->playedCardCount; ++i) {
		if (state->playedCards[i] == card)
			count++;
	}

	return count;
}

void addError(struct test* t, const char* s) {
	strcpy(t->status[t->errCount],s);
	t->err = 1;
	t->errCount++;
}



