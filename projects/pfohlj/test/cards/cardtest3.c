/*****************************************************************************************
* NAME:         Joseph A Pfohl
* DATE:         4/26/2017
* ASSIGNMENT:   Assignment #3 - Unit Tests
* DESCRIPTION:  Unit tests for CouncilRoom()
*****************************************************************************************/

#include "../../dominion/dominion.h"
#include "../../dominion/dominion_helpers.h"
#include "../../dominion/rngs.h"
#include "../helpers/test_helpers.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// FUNCTION DECLARATIONS

void Test();

// GLOBALS

int NEG_ONE = -1;
int ZERO = 0;
int ONE = 1;

// MAIN

int main(int argc, char ** argv)
{
    Test();
    return 0;
}

// FUNCTION DEFINITIONS

void Test()
{
    // variables
    GameState *state;
    Cards kingdom;
    Cards deck;

    int i,
        startNumBuys,
        newNumBuys;

    int startHandSizes[4],
        startDeckSizes[4],
        newHandSizes[4],
        newDeckSizes[4];

    Card oneCouncilRoom[5] = {council_room, copper, copper, copper, copper};
    Card fiveCouncilRooms[5] = {council_room, council_room, council_room, council_room, council_room};

    // allocate memory
    state = newGame();
    kingdom = CreateKingdom(GoodNoCouncilRoom);
    deck = CreateDeck(LargeNoCouncilRoom);

    // initialize game
    initializeGame(4, kingdom, 42, state);

    // copy in deck, set decksize, and shuffle
    for (i = 0; i < 4; i++)
    {
        memcpy(state->deck[i], deck, LARGE_DECK_SIZE);
        state->deckCount[i] = LARGE;
        shuffle(i, state);

        memcpy(state->hand[i], oneCouncilRoom, START_HAND_SIZE);
        state->handCount[i] = 5;
    }

    // save our starting values
    startNumBuys = state->numBuys;

    for (i = 1; i < 4; i++)
    {
        startHandSizes[i] = state->handCount[i];
        startDeckSizes[i] = state->deckCount[i];
    }

    CouncilRoom(state, 0);

    // save the results
    newNumBuys = state->numBuys;

    for (i = 0; i < 4; i++)
    {
        newHandSizes[i] = state->handCount[i];
        newDeckSizes[i] = state->deckCount[i];
    }

    AssertTrue(newHandSizes[0] == (startHandSizes[0] + 3))
        ? printf("PASS: Player handsize increased by 3.\n")
        : printf("** FAIL: Player handsize did not increase by 3.\n");

    AssertTrue(newDeckSizes[0] == (startDeckSizes[0] - 4))
        ? printf("PASS: decksize decreased by 4.\n")
        : printf("** FAIL: deck size did not decrease by 4.\n");

    AssertTrue(newNumBuys == (startNumBuys + 1))
        ? printf("PASS: buys increased by 1.\n")
        : printf("** FAIL: buys did not increase by 1.");

    AssertTrue(HandCount(council_room, 0, state) == 0)
        ? printf("PASS: Player has no Council Rooms remaining in hand (started with one, played one).\n")
        : printf("PASS: Player still has Council Rooms in hand.\n");

    for (i = 1; i < 4; i++)
    {
        AssertTrue(newHandSizes[i] == (startHandSizes[i] + 1))
            ? printf("PASS: player %d hand size is one larger.\n", i+1)
            : printf("** FAIL: player %d hand size is not one larger.\n", i+1);

        AssertTrue(newDeckSizes[i] == (startDeckSizes[i] - 1))
            ? printf("PASS: player %d deck size is one less.\n", i+1)
            : printf("** FAIL: player %d deck size is not one less.\n", i+1);
    }

    // TEST multiple plays of Council Room

    // copy in deck, set decksize, and shuffle
    for (i = 0; i < 4; i++)
    {
        memcpy(state->deck[i], deck, LARGE_DECK_SIZE);
        state->deckCount[i] = LARGE;
        shuffle(i, state);

        memcpy(state->hand[i], fiveCouncilRooms, START_HAND_SIZE);
        state->handCount[i] = 5;
    }

    // save starting values
    startNumBuys = state->numBuys;

    for (i = 0; i < 4; i++)
    {
        startHandSizes[i] = state->handCount[i];
        startDeckSizes[i] = state->deckCount[i];
    }

    for (i = 0; i < 5; i++)
    {
        CouncilRoom(state, i);
    }

    // save the results
    newNumBuys = state->numBuys;

    for (i = 0; i < 4; i++)
    {
        newHandSizes[i] = state->handCount[i];
        newDeckSizes[i] = state->deckCount[i];
    }

    AssertTrue(newHandSizes[0] == (startHandSizes[0] + 15))
        ? printf("PASS: Player handsize increased by 15.\n")
        : printf("** FAIL: Player handsize did not increase by 15.\n");

    AssertTrue(newDeckSizes[0] == (startDeckSizes[0] - 20))
        ? printf("PASS: decksize decreased by 20.\n")
        : printf("** FAIL: deck size did not decrease by 20.\n");

    AssertTrue(newNumBuys == (startNumBuys + 5))
        ? printf("PASS: buys increased by 1.\n")
        : printf("** FAIL: buys did not increase by 1.");

    AssertTrue(HandCount(council_room, 0, state) == 0)
        ? printf("PASS: Player has no Council Rooms remaining in hand (started with 5, played 5).\n")
        : printf("PASS: Player still has Council Rooms in hand.\n");

    for (i = 1; i < 4; i++)
    {
        AssertTrue(newHandSizes[i] == (startHandSizes[i] + 5))
            ? printf("PASS: player %d hand size is 5 larger.\n", i+1)
            : printf("** FAIL: player %d hand size is not 5 larger.\n", i+1);

        AssertTrue(newDeckSizes[i] == (startDeckSizes[i] - 5))
            ? printf("PASS: player %d deck size is 5 less.\n", i+1)
            : printf("** FAIL: player %d deck size is not 5 less.\n", i+1);
    }

    // TEST Council room where all players have deck & discard size of 0

    for (i = 0; i < 4; i++)
    {
        // reset the deck, no need to shuffle (in theory...)
        memcpy(state->deck[i], deck, LARGE_DECK_SIZE);

        // explicitly set deckcount and discard count to 0
        state->deckCount[i] = 0;
        state->discardCount[i] = 0;

        // reset players hand
        memcpy(state->hand[i], oneCouncilRoom, 5 * sizeof(Card));
        state->handCount[i] = 5;
    }
    
    // get starting values
    startNumBuys = state->numBuys;

    for (i = 0; i < 4; i++)
    {
        startHandSizes[i] = state->handCount[i];
        startDeckSizes[i] = state->deckCount[i];
    }
    

    CouncilRoom(state, 0);

    // get the resultant values
    newNumBuys = state->numBuys;

    for (i = 0; i < 4; i++)
    {
        newHandSizes[i] = state->handCount[i];
        newDeckSizes[i] = state->deckCount[i];
    }

    AssertTrue(newHandSizes[0] == (startHandSizes[0] - 1))
        ? printf("PASS: Player handsize decreased by 1 (no cards to draw).\n")
        : printf("** FAIL: Player handsize did not decrease by 1 (change in some other way).\n");

    AssertTrue(newDeckSizes[0] == 0)
        ? printf("PASS: decksize did not change.\n")
        : printf("** FAIL: decksize changed.\n");

    AssertTrue(newNumBuys == (startNumBuys + 1))
        ? printf("PASS: buys increased by 1.\n")
        : printf("** FAIL: buys did not increase by 1.");

    AssertTrue(HandCount(council_room, 0, state) == 0)
        ? printf("PASS: Player has no Council Rooms remaining in hand (started with one, played one).\n")
        : printf("PASS: Player still has Council Rooms in hand.\n");

    for (i = 1; i < 4; i++)
    {
        AssertEqual(&newHandSizes[i], &startHandSizes[i], CompareInt)
            ? printf("PASS: player %d hand size is unchanged.\n", i+1)
            : printf("** FAIL: player %d hand size different.\n", i+1);

        AssertEqual(&newDeckSizes[i], &startDeckSizes[i], CompareInt)
            ? printf("PASS: player %d deck size unchanged.\n", i+1)
            : printf("** FAIL: player %d deck size different.\n", i+1);
    }

    // cleanup
    free(state);
    free(kingdom);
    free(deck);
}