#include "dominion.h"
#include "unitTestUtilities.h"
#include <stdio.h>

void testFullDeckCount(struct gameState* state) {
	int i;
	int count = -1;
	int flag = 0;
	int who = state->whoseTurn;

	//Set deck, hand and discard to copper
	for (i = 0; i < 5; ++i) {
		state->hand[who][i] = copper;
		state->deck[who][i] = copper;
		state->discard[who][i] = copper;
	}
	state->deckCount[who] = 5;
	state->handCount[who] = 4;
	state->discardCount[who] = 3;

	struct gameState snapshot = *state;
	count = fullDeckCount(who,copper,state);

	if(count != 12) {
		printf("fullDeckCount() test: FAIL to get the correct count of 12 copper.\n");
		flag = -1;
	}
	if(cmpGameState(state,&snapshot) == 0) {
		printf("fullDeckCount() test: FAIL to maintain game state after function call.\n");
		flag = -1;
	}
	if(flag != -1)
		printf("fullDeckCount() test: PASS counting 12 copper.\n");

	flag = 0;
	count = fullDeckCount(who,province,state);

	if(count != 0) {
		printf("fullDeckCount() test: FAIL to get the correct count of 0 provinces.\n");
		flag = -1;
	}
	if(cmpGameState(state,&snapshot) == 0) {
		printf("fullDeckCount() test: FAIL to maintain game state after function call.\n");
		flag = -1;
	}
	if(flag != -1)
		printf("fullDeckCount() test: PASS counting 0 provinces.\n");
}