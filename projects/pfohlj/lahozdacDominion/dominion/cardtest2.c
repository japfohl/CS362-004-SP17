#include "dominion.h"
#include "unitTestUtilities.h"
#include <stdio.h>

void testAdventurer (struct gameState* state) {
	int i;
	int flag = 0;
	int who = state->whoseTurn;

	//Make sure hand is not empty
	if(state->handCount[who] < 1)
		state->handCount[who] = 1;

	//Add adventurer to hand
	state->hand[who][0] = adventurer;

	//Make sure deck has at least 2 treasures
	for (i = 0; i < 3; ++i) {
		state->deck[who][i] = copper;
	}
	if(state->deckCount[who] < 3)
		state->deckCount[who] = 3;

	//Get treasure count in hand
	int treasures_snapshot =0;
	for (i = 0; i < state->handCount[who]; ++i) {
		int card = state->hand[who][i];
		if (card == copper || card == silver || card == gold)
			treasures_snapshot++;
	}

	printf("Testing Adventurer with sufficient treasures in draw deck\n");
	printf("\n");
	struct gameState snapshot = *state;
	flag = playAdventurer(state);

	//Get treasure count in hand
	int treasures = 0;
	for (i = 0; i < state->handCount[who]; ++i) {
		int card = state->hand[who][i];
		if (card == copper || card == silver || card == gold)
			treasures++;
	}

	if(flag == -1)
		printf("playAdventurer() test: FAIL to play card.\n");
	//Note that handCount should only be +1 since adventurer is discarded after adding 2 to hand
	if(state->handCount[who] < (snapshot.handCount[who] + 1)) {
		printf("playAdventurer() test: FAIL, not enough cards in hand.\n");
		flag = -1;
	}
	if(state->handCount[who] > (snapshot.handCount[who] + 1)) {
		printf("playAdventurer() test: FAIL, too many cards in hand.\n");
		flag = -1;
	}
	//At least 2 cards should be drawn from the deck
	if(state->deckCount[who] > (snapshot.deckCount[who] - 2)) {
		printf("playAdventurer() test: FAIL, not enough cards drawn from deck.\n");
		flag = -1;
	}
	if(state->playedCardCount != (snapshot.playedCardCount + 1)) {
		printf("playAdventurer() test: FAIL to increase playedCardCount after playing adventurer.\n");
		flag = -1;
	}
	if(state->playedCards[state->playedCardCount - 1] != adventurer) {
		printf("playAdventurer() test: FAIL to put adventurer on top of the played cards pile.\n");
		flag = -1;
	}
	//Player should now have at least 2 more coins than previously
	if(state->coins < snapshot.coins + 2) {
		printf("playAdventurer() test: FAIL, not enough coins.\n");
		flag = -1;
	}
	//Player should have exactly 2 more treasures than previously
	if(treasures < treasures_snapshot + 2) {
		printf("playAdventurer() test: FAIL, not enough treasures in hand.\n");
		flag = -1;
	}
	if(treasures > treasures_snapshot + 2) {
		printf("playAdventurer() test: FAIL, too many treasures in hand.\n");
		flag = -1;
	}
	if(flag != -1)
		printf("playAdventurer() test: PASS when playing adventurer with 2+ treasures in draw deck.\n");

	*state = snapshot;

	//Empty deck into discard
	for (i = 0; i < state->deckCount[who]; ++i) {
		state->discard[who][state->discardCount[who]] = state->deck[who][i];
		state->discardCount[who]++;
	}
	state->deckCount[who] = 0;

	//Previous treasures_snapshot still valid here

	printf("\n");
	printf("Testing Adventurer with empty draw deck\n");
	printf("\n");
	snapshot = *state;
	flag = playAdventurer(state);

	//Get treasure count in hand
	treasures = 0;
	for (i = 0; i < state->handCount[who]; ++i) {
		int card = state->hand[who][i];
		if (card == copper || card == silver || card == gold)
			treasures++;
	}

	//Get treasure count in discard
	int treasures_discard = 0;
	for (i = 0; i < state->discardCount[who]; ++i) {
		int card = state->discard[who][i];
		if (card == copper || card == silver || card == gold)
			treasures_discard++;
	}

	if(flag == -1)
		printf("playAdventurer() test: FAIL to play card.\n");
	//Note that handCount should only be +1 since adventurer is discarded after adding 2
	if(state->handCount[who] < (snapshot.handCount[who] + 1)) {
		printf("playAdventurer() test: FAIL, not enough cards in hand.\n");
		flag = -1;
	}
	if(state->handCount[who] > (snapshot.handCount[who] + 1)) {
		printf("playAdventurer() test: FAIL, too many cards in hand.\n");
		flag = -1;
	}
	//Draw deck should now have cards = previous discardCount - 2+
	if(state->deckCount[who] > (snapshot.discardCount[who] - 2)) {
		printf("playAdventurer() test: FAIL, too many cards in the deck.\n");
		flag = -1;
	}
	//There should be at least one card in the discard, and adventurer should be on top
	if(state->discardCount[who] < 1) {
		printf("playAdventurer() test: FAIL, not enough cards in discard.\n");
		flag = -1;
	}
	if(state->discard[who][0] != adventurer) {
		printf("playAdventurer() test: FAIL to put adventurer on top of the discard.\n");
		flag = -1;
	}
	//There should be no treasures in the discard
	if(treasures_discard > 0) {
		printf("playAdventurer() test: FAIL, revealed treasures were discarded.\n");
		flag = -1;
	}
	//Player should now have at least 2 more coins than previously
	if(state->coins < snapshot.coins + 2) {
		printf("playAdventurer() test: FAIL, not enough coins.\n");
		flag = -1;
	}
	//Player should have exactly 2 more treasures than previously
	if(treasures < treasures_snapshot + 2) {
		printf("playAdventurer() test: FAIL, not enough treasures in hand.\n");
		flag = -1;
	}
	if(treasures > treasures_snapshot + 2) {
		printf("playAdventurer() test: FAIL, too many treasures in hand.\n");
		flag = -1;
	}
	if(flag != -1)
		printf("playAdventurer() test: PASS when playing adventurer with no cards in draw deck and 2+ treasures in discard.\n");

	printf("\n");

}