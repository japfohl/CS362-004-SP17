#include "dominion.h"
#include "unitTestUtilities.h"
#include <stdio.h>

void testCouncilRoom(struct gameState* state) {
	int i, j;
	int flag = 0;
	int who = state->whoseTurn;

	//Make sure hand is not empty
	if(state->handCount[who] < 1)
		state->handCount[who] = 1;

	//Add council room to hand
	state->hand[who][0] = council_room;

	//Make sure all decks have at least 1 card
	for (i = 0; i < state->numPlayers; ++i) {
		if (state->deckCount[i] < 1) {
			state->deck[i][0] = copper;
			state->deckCount[i] = 1;
		}
	}

	//Make sure player deck has at least 4 cards
	if(state->deckCount[who] < 4) {
		for (i = state->deckCount[who]; i <= 3; ++i) {
			state->deck[who][i] = copper;
		}
		state->deckCount[who] = 4;
	}

	printf("Testing playCouncil_Room() with sufficient cards in all draw decks\n");
	printf("\n");
	struct gameState snapshot = *state;
	flag = playCouncil_Room(state,0);

	//Check other player's hands
	int otherPlayerHandFlag = 0;
	for (i = 0; i < state->numPlayers; ++i) {
		if (i != who && state->handCount[i] != (snapshot.handCount[i] + 1)) {
			otherPlayerHandFlag = 1;
		}
	}

	//Check other player's decks
	int otherPlayerDeckFlag = 0;
	for (i = 0; i < state->numPlayers; ++i) {
		if (i != who && state->deckCount[i] != (snapshot.deckCount[i] - 1)) {
			otherPlayerDeckFlag = 1;
		}
	}

	if(flag == -1) {
		printf("playCouncil_Room() test: FAIL to play card.\n");
		flag = -1;
	}
	//Note that handCount should only be +3 since council room is discarded after drawing 4
	if(state->handCount[who] < (snapshot.handCount[who] + 3)) {
		printf("playCouncil_Room() test: FAIL, not enough cards in hand.\n");
		flag = -1;
	}
	if(state->handCount[who] > (snapshot.handCount[who] + 3)) {
		printf("playCouncil_Room() test: FAIL, too many cards in hand.\n");
		flag = -1;
	}
	if(state->deckCount[who] != (snapshot.deckCount[who] - 4)) {
		printf("playCouncil_Room() test: FAIL to decrease player deckCount after playing council room.\n");
		flag = -1;
	}
	if(state->numBuys != (snapshot.numBuys + 1)) {
		printf("playCouncil_Room() test: FAIL to increase numBuys.\n");
		flag = -1;
	}
	if(state->playedCardCount != (snapshot.playedCardCount + 1)) {
		printf("playCouncil_Room() test: FAIL to increase playedCardCount after playing council room.\n");
		flag = -1;
	}
	if(state->playedCards[state->playedCardCount - 1] != council_room) {
		printf("playCouncil_Room() test: FAIL to put council room on top of the played cards pile.\n");
		flag = -1;
	}
	//All other players should have hand + 1
	if(otherPlayerHandFlag == 1) {
		printf("playCouncil_Room() test: FAIL, one or more other players doesn't have enough cards in their hand(s).\n");
		flag = -1;
	}
	//All other players should have deck - 1
	if(otherPlayerDeckFlag == 1) {
		printf("playCouncil_Room() test: FAIL, one or more other players has too many cards in their deck(s).\n");
		flag = -1;
	}
	if(flag != -1)
		printf("playCouncil_Room() test: PASS when playing council room with 4+ cards in draw deck.\n");

	*state = snapshot;

	//Empty all decks into discard
	for (i = 0; i < state->numPlayers; ++i) {
		for (j = 0; j < state->deckCount[i]; ++j) {
			state->discard[i][state->discardCount[i]] = state->deck[i][j];
			state->discardCount[i]++;
		}
		state->deckCount[i] = 0;
	}

	printf("\n");
	printf("Testing playCouncil_Room() with empty draw decks\n");
	printf("\n");
	snapshot = *state;
	flag = playCouncil_Room(state,0);

	//Check other players' hands
	otherPlayerHandFlag = 0;
	for (i = 0; i < state->numPlayers; ++i) {
		if (i != who && state->handCount[i] != (snapshot.handCount[i] + 1)) {
			otherPlayerHandFlag = 1;
		}
	}

	//Check other players' decks
	otherPlayerDeckFlag = 0;
	for (i = 0; i < state->numPlayers; ++i) {
		if (i != who && state->deckCount[i] != (snapshot.discardCount[i] - 1)) {
			otherPlayerDeckFlag = 1;
		}
	}

	//Check other players' discards
	int otherPlayerDiscardFlag = 0;
	for (i = 0; i < state->numPlayers; ++i) {
		if (i != who && state->discardCount[i] != 0) {
			otherPlayerDiscardFlag = 1;
		}
	}

	if(flag == -1) {
		printf("playCouncil_Room() test: FAIL to play card.\n");
		flag = -1;
	}
	//Note that handCount should only be +3 since council room is discarded after drawing 4
	if(state->handCount[who] < (snapshot.handCount[who] + 3)) {
		printf("playCouncil_Room() test: FAIL, not enough cards in hand.\n");
		flag = -1;
	}
	if(state->handCount[who] > (snapshot.handCount[who] + 3)) {
		printf("playCouncil_Room() test: FAIL, too many cards in hand.\n");
		flag = -1;
	}
	//Draw deck should now have cards = previous discardCount - 4
	if(state->deckCount[who] != (snapshot.discardCount[who] - 4)) {
		printf("playCouncil_Room() test: FAIL to have correct deckCount.\n");
		flag = -1;
	}
	if(state->numBuys != (snapshot.numBuys + 1)) {
		printf("playCouncil_Room() test: FAIL to increase numBuys.\n");
		flag = -1;
	}
	if(state->playedCardCount != (snapshot.playedCardCount + 1)) {
		printf("playCouncil_Room() test: FAIL to increase playedCardCount after playing council room.\n");
		flag = -1;
	}
	if(state->playedCards[state->playedCardCount - 1] != council_room) {
		printf("playCouncil_Room() test: FAIL to put council room on top of the played cards pile.\n");
		flag = -1;
	}
	//All other players should have hand + 1
	if(otherPlayerHandFlag == 1) {
		printf("playCouncil_Room() test: FAIL, one or more other players doesn't have enough cards in their hand(s).\n");
		flag = -1;
	}
	//All other players should have deck = previous discardCount -1
	if(otherPlayerDeckFlag == 1) {
		printf("playCouncil_Room() test: FAIL, one or more other players has too many cards in their deck(s).\n");
		flag = -1;
	}
	//All other players should have no cards in discard
	if(otherPlayerDiscardFlag == 1) {
		printf("playCouncil_Room() test: FAIL, one or more other players has too many cards in their discard(s).\n");
		flag = -1;
	}
	if(flag != -1)
		printf("playCouncil_Room() test: PASS when playing council room with no cards in draw deck.\n");

	printf("\n");
	
}