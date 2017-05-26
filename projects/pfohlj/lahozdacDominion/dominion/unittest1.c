#include "dominion.h"
#include "unitTestUtilities.h"
#include <stdio.h>

void testBuyCard(struct gameState* state) {
	int flag = 0;
	int who = state->whoseTurn;

	state->coins = 5;
	struct gameState snapshot = *state;
	flag = buyCard(gold,state);
	
	if(flag != -1) {
		printf("buyCard() test: FAIL to stop buying card that is too expensive.\n");
		flag = 0;
	}
	if(cmpGameState(state,&snapshot) == 0) {
		printf("buyCard() test: FAIL to maintain game state after failed action.\n");
		flag = 0;
	}
	if(flag != 0)
		printf("buyCard() test: PASS when trying to buy card that is too expensive.\n");

	state->numBuys = 0;
	snapshot = *state;
	flag = buyCard(copper,state);

	if(flag != -1) {
		printf("buyCard() test: FAIL to stop buying card with no buys left.\n");
		flag = 0;
	}
	if(cmpGameState(state,&snapshot) == 0) {
		printf("buyCard() test: FAIL to maintain game state after failed action.\n");
		flag = 0;
	}
	if(flag != 0)
		printf("buyCard() test: PASS when trying to buy card with no buys left.\n");

	state->numBuys = 1;
	state->supplyCount[copper] = 0;
	snapshot = *state;
	flag = buyCard(copper,state);

	if(flag != -1) {
		printf("buyCard() test: FAIL to stop buying card with none left in supply.\n");
		flag = 0;
	}
	if(cmpGameState(state,&snapshot) == 0) {
		printf("buyCard() test: FAIL to maintain game state after failed action.\n");
		flag = 0;
	}
	if(flag != 0)
		printf("buyCard() test: PASS when trying to buy card with none left in supply.\n");

	flag = buyCard(estate,state);

	if(flag == -1)
		printf("buyCard() test: FAIL to buy card.\n");
	if(state->numBuys != (snapshot.numBuys - 1)) {
		printf("buyCard() test: FAIL to reduce number of buys after buying card.\n");
		flag = -1;
	}
	if(state->coins != (snapshot.coins - 2)) {
		printf("buyCard() test: FAIL to have the right number of coins after buying card.\n");
		flag = -1;
	}
	if(state->supplyCount[estate] != (snapshot.supplyCount[estate] - 1)) {
		printf("buyCard() test: FAIL to reduce the supply of the card that was purchased.\n");
		flag = -1;
	}
	if(state->discardCount[who] != (snapshot.discardCount[who] + 1)) {
		printf("buyCard() test: FAIL to increment discard count.\n");
		flag = -1;
	}
	if(state->discard[who][state->discardCount[who] - 1] != estate) {
		printf("buyCard() test: FAIL to put purchased card into discard.\n");
		flag = -1;
	}
	if(flag != -1)
		printf("buyCard() test: PASS when successfully buying a card.\n");

	printf("\n");
}