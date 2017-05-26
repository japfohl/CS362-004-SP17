#include "dominion.h"
#include "unitTestUtilities.h"
#include <stdio.h>

void testIsGameOver(struct gameState* state) {
	int flag = 0;

	struct gameState snapshot = *state;

	flag = isGameOver(state);

	if(flag == -1)
		printf("isGameOver() test: FAIL, error flag.\n");
	if(flag == 1) {
		printf("isGameOver() test: FAIL, game flagged as over when it is not.\n");
		flag = -1;
	}
	if(cmpGameState(state,&snapshot) == 0) {
		printf("isGameOver() test: FAIL to maintain game state after function call.\n");
		flag = -1;
	}
	if(flag != -1)
		printf("isGameOver() test: PASS when evaluating a game that's not over.\n");

	*state = snapshot;

	//Empty 1 pile
	state->supplyCount[gold] = 0;
	snapshot = *state;

	flag = isGameOver(state);

	if(flag == -1)
		printf("isGameOver() test: FAIL, error flag.\n");
	if(flag == 1) {
		printf("isGameOver() test: FAIL, game flagged as over when it is not - only 1 pile is empty.\n");
		flag = -1;
	}
	if(cmpGameState(state,&snapshot) == 0) {
		printf("isGameOver() test: FAIL to maintain game state after function call.\n");
		flag = -1;
	}
	if(flag != -1)
		printf("isGameOver() test: PASS when evaluating a game that's not over with 1 empty pile.\n");

	*state = snapshot;

	//Empty 2nd pile
	state->supplyCount[silver] = 0;
	snapshot = *state;

	flag = isGameOver(state);

	if(flag == -1)
		printf("isGameOver() test: FAIL, error flag.\n");
	if(flag == 1) {
		printf("isGameOver() test: FAIL, game flagged as over when it is not - only 2 piles are empty.\n");
		flag = -1;
	}
	if(cmpGameState(state,&snapshot) == 0) {
		printf("isGameOver() test: FAIL to maintain game state after function call.\n");
		flag = -1;
	}
	if(flag != -1)
		printf("isGameOver() test: PASS when evaluating a game that's not over with 2 empty piles.\n");

	*state = snapshot;

	//Empty 3rd pile
	state->supplyCount[estate] = 0;
	snapshot = *state;

	flag = isGameOver(state);

	if(flag == -1)
		printf("isGameOver() test: FAIL, error flag.\n");
	if(flag != 1) {
		printf("isGameOver() test: FAIL, game not flagged as over when it is - 3 piles are empty.\n");
		flag = -1;
	}
	if(cmpGameState(state,&snapshot) == 0) {
		printf("isGameOver() test: FAIL to maintain game state after function call.\n");
		flag = -1;
	}
	if(flag != -1)
		printf("isGameOver() test: PASS when evaluating a game that's over with 3 empty piles.\n");

	*state = snapshot;

	//Refill pther piles and empty provinces
	state->supplyCount[estate] = 1;
	state->supplyCount[silver] = 1;
	state->supplyCount[gold] = 1;
	state->supplyCount[province] = 0;
	
	snapshot = *state;
	flag = isGameOver(state);

	if(flag == -1)
		printf("isGameOver() test: FAIL, error flag.\n");
	if(flag != 1) {
		printf("isGameOver() test: FAIL, game not flagged as over when province supply empty.\n");
		flag = -1;
	}
	if(cmpGameState(state,&snapshot) == 0) {
		printf("isGameOver() test: FAIL to maintain game state after function call.\n");
		flag = -1;
	}
	if(flag != -1)
		printf("isGameOver() test: PASS when evaluating a game that's over because the province supply is empty.\n");

}