#include "dominion.h"
#include "unitTestUtilities.h"
#include <stdio.h>

void testVillage (struct gameState* state) {
	int i;
	int flag = 0;
	int who = state->whoseTurn;

	//Make sure hand is not empty
	if(state->handCount[who] < 1)
		state->handCount[who] = 1;

	//Add village to hand
	state->hand[who][0] = village;

	//Make sure deck has at least 1 cards
	if(state->deckCount[who] < 1) {
		state->deck[who][0] = copper;
		state->deckCount[who] = 1;
	}

	printf("Testing playVillage() with sufficient cards in draw deck\n");
	printf("\n");
	struct gameState snapshot = *state;
	flag = playVillage(state,0);

	if(flag == -1) {
		printf("playVillage() test: FAIL to play card.\n");
		flag = -1;
	}
	//Since playing village costs 1 action, net gain should be +1
	if(state->numActions != snapshot.numActions + 1) {
		printf("playVillage() test: FAIL, incorrect number of actions.\n");
		flag = -1;
	}
	//Note that handCount should only be the same since village is discarded after drawing 1
	if(state->handCount[who] < snapshot.handCount[who]) {
		printf("playVillage() test: FAIL, not enough cards in hand.\n");
		flag = -1;
	}
	if(state->handCount[who] > snapshot.handCount[who]) {
		printf("playVillage() test: FAIL, too many cards in hand.\n");
		flag = -1;
	}
	if(state->deckCount[who] != (snapshot.deckCount[who] - 1)) {
		printf("playVillage() test: FAIL to decrease deckCount after playing village.\n");
		flag = -1;
	}
	if(state->playedCardCount != (snapshot.playedCardCount + 1)) {
		printf("playVillage() test: FAIL to increase playedCardCount after playing village.\n");
		flag = -1;
	}
	if(state->playedCards[state->playedCardCount - 1] != village) {
		printf("playVillage() test: FAIL to put village on top of the played cards pile.\n");
		flag = -1;
	}
	if(flag != -1)
		printf("playVillage() test: PASS when playing village with 1+ cards in draw deck.\n");

	*state = snapshot;

	//Empty deck into discard
	for (i = 0; i < state->deckCount[who]; ++i) {
		state->discard[who][state->discardCount[who]] = state->deck[who][i];
		state->discardCount[who]++;
	}
	state->deckCount[who] = 0;

	printf("\n");
	printf("Testing playVillage() with empty draw deck.\n");
	printf("\n");
	snapshot = *state;
	flag = playVillage(state,0);

	if(flag == -1) {
		printf("playVillage() test: FAIL to play card.\n");
		flag = -1;
	}
	//Since playing village costs 1 action, net gain should be +1
	if(state->numActions != snapshot.numActions + 1) {
		printf("playVillage() test: FAIL, incorrect number of actions.\n");
		flag = -1;
	}
	//Note that handCount should only the same since village is discarded after drawing 1
	if(state->handCount[who] < snapshot.handCount[who]) {
		printf("playVillage() test: FAIL, not enough cards in hand.\n");
		flag = -1;
	}
	if(state->handCount[who] > snapshot.handCount[who]) {
		printf("playVillage() test: FAIL, too many cards in hand.\n");
		flag = -1;
	}
	//Draw deck should now have cards = previous discardCount - 1
	if(state->deckCount[who] != (snapshot.discardCount[who] - 1)) {
		printf("playVillage() test: FAIL to have correct deckCount.\n");
		flag = -1;
	}
	//village should be the only thing in the played cards
	if(state->playedCardCount != (snapshot.playedCardCount + 1)) {
		printf("playVillage() test: FAIL to increase playedCardCount after playing village.\n");
		flag = -1;
	}
	if(state->playedCards[state->playedCardCount - 1] != village) {
		printf("playVillage() test: FAIL to put village on top of the played cards pile.\n");
		flag = -1;
	}
	if(flag != -1)
		printf("playVillage() test: PASS when playing village with no cards in draw deck.\n");

	printf("\n");
}