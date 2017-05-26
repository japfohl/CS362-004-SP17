#include "dominion.h"
#include "unitTestUtilities.h"
#include <stdio.h>

void testSmithy(struct gameState* state) {
	int i;
	int flag = 0;
	int who = state->whoseTurn;

	//Make sure hand is not empty
	if(state->handCount[who] < 1)
		state->handCount[who] = 1;

	//Add smithy to hand
	state->hand[who][0] = smithy;

	//Make sure deck has at least 3 cards
	if(state->deckCount[who] < 3) {
		for (i = state->deckCount[who]; i <= 3; ++i) {
			state->deck[who][i] = copper;
		}
		state->deckCount[who] = 3;
	}

	struct gameState snapshot = *state;
	printf("playSmithy() test: Testing with sufficient cards to draw\n");
	printf("\n");
	flag = playSmithy(state,0);

	if(flag == -1) {
		printf("playSmithy() test: FAIL to play card.\n");
	}
	//Note that handCount should only be +2 since smithy is discarded after drawing 3
	if(state->handCount[who] < (snapshot.handCount[who] + 2)) {
		printf("playSmithy() test: FAIL, not enough cards in hand.\n");
		flag = -1;
	}
	if(state->handCount[who] > (snapshot.handCount[who] + 2)) {
		printf("playSmithy() test: FAIL, too many cards in hand.\n");
		flag = -1;
	}
	if(state->deckCount[who] != (snapshot.deckCount[who] - 3)) {
		printf("playSmithy() test: FAIL to decrease deckCount after playing smithy.\n");
		flag = -1;
	}
	if(state->playedCardCount != (snapshot.playedCardCount + 1)) {
		printf("playSmithy() test: FAIL to increase playedCardCount after playing smithy.\n");
		flag = -1;
	}
	if(state->playedCards[state->playedCardCount - 1] != smithy) {
		printf("playSmithy() test: FAIL to put smithy on top of the played cards pile.\n");
		flag = -1;
	}
	if(flag != -1)
		printf("playSmithy() test: PASS when playing smithy with 3+ cards in draw deck.\n");

	*state = snapshot;

	//Empty deck into discard
	for (i = 0; i < state->deckCount[who]; ++i) {
		state->discard[who][state->discardCount[who]] = state->deck[who][i];
		state->discardCount[who]++;
	}
	state->deckCount[who] = 0;

	snapshot = *state;

	printf("\n");
	printf("playSmithy() test: Testing with empty draw deck\n");
	printf("\n");

	flag = playSmithy(state,0);

	if(flag == -1) {
		printf("playSmithy() test: FAIL to play card.\n");
		flag = -1;
	}
	//Note that handCount should only be +2 since smithy is discarded after drawing 3
	if(state->handCount[who] < (snapshot.handCount[who] + 2)) {
		printf("playSmithy() test: FAIL, not enough cards in hand.\n");
		flag = -1;
	}
	if(state->handCount[who] > (snapshot.handCount[who] + 2)) {
		printf("playSmithy() test: FAIL, too many cards in hand.\n");
		flag = -1;
	}
	//Draw deck should now have cards = previous discardCount - 3
	if(state->deckCount[who] != (snapshot.discardCount[who] - 3)) {
		printf("playSmithy() test: FAIL to have correct deckCount.\n");
		flag = -1;
	}
	if(state->playedCardCount != (snapshot.playedCardCount + 1)) {
		printf("playSmithy() test: FAIL to increase playedCardCount after playing smithy.\n");
		flag = -1;
	}
	if(state->playedCards[state->playedCardCount - 1] != smithy) {
		printf("playSmithy() test: FAIL to put smithy on top of the played cards pile.\n");
		flag = -1;
	}
	if(flag != -1)
		printf("playSmithy() test: PASS when playing smithy with no cards in draw deck.\n");

	printf("\n");

}