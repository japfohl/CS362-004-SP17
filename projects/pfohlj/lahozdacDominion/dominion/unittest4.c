#include "dominion.h"
#include "unitTestUtilities.h"
#include <stdio.h>

void testNumHandCards(struct gameState* state) {
	int flag = 0;
	int count = -1;

	//Set testing parameters
	state->numPlayers = 3;
	state->whoseTurn = 0;
	state->handCount[0] = 3;
	state->handCount[1] = -10;
	state->handCount[2] = 0;

	struct gameState snapshot = *state;
	count = numHandCards(state);

	if(count != 3) {
		printf("numHandCards() test: FAIL to get the correct count of 3 for first player.\n");
		flag = -1;
	}
	if(cmpGameState(state,&snapshot) == 0) {
		printf("numHandCards() test: FAIL to maintain game state after function call.\n");
		flag = -1;
	}
	if(flag != -1)
		printf("numHandCards() test: PASS counting 3 cards in first player's hand.\n");

	state->whoseTurn = 2;
	snapshot = *state;
	flag = 0;
	count = numHandCards(state);

	if(count != 0) {
		printf("numHandCards() test: FAIL to get the correct count of 0 for third player.\n");
		flag = -1;
	}
	if(cmpGameState(state,&snapshot) == 0) {
		printf("numHandCards() test: FAIL to maintain game state after function call.\n");
		flag = -1;
	}
	if(flag != -1)
		printf("numHandCards() test: PASS counting 0 cards in third player's hand.\n");

	//Here we're testing an invalid value to see if anything odd happens.
	state->whoseTurn = 1;
	snapshot = *state;
	flag = 0;
	count = numHandCards(state);

	if(count != -10) {
		printf("numHandCards() test: FAIL to get the correct count of -10 for second player.\n");
		flag = -1;
	}
	if(cmpGameState(state,&snapshot) == 0) {
		printf("numHandCards() test: FAIL to maintain game state after function call.\n");
		flag = -1;
	}
	if(flag != -1)
		printf("numHandCards() test: PASS counting -10 cards in second player's hand.\n");
}