/*****************************************************************************************
* NAME:         Joseph A Pfohl
* DATE:         4/26/2017
* ASSIGNMENT:   Assignment #3 - Unit Tests
* DESCRIPTION:  Unit tests for Smithy()
*****************************************************************************************/

#include "../../dominion/dominion.h"
#include "../../dominion/dominion_helpers.h"
#include "../../dominion/rngs.h"
#include "../helpers/test_helpers.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// FUNCTION DECLARATIONS

void TestSmithy();

// GLOBALS

int NEG_ONE = -1;
int ZERO = 0;
int ONE = 1;

// MAIN

int main(int argc, char ** argv)
{
    TestSmithy();
    return 0;
}

// FUNCTION DEFINITIONS

void TestSmithy()
{
    // variables
    GameState *state;
    Cards kingdom;
    Cards deck;

    int playerDeckSize = LARGE,
        currentPlayer,
        startHandSize,
        newHandSize,
        startDeckSize,
        newDeckSize,
        i;

    Card oneSmithy[5] = {smithy, copper, copper, copper, copper};
    Card fiveSmithys[5] = {smithy, smithy, smithy, smithy, smithy};

    // allocate memory
    state = newGame();
    kingdom = CreateKingdom(GoodNoSmithy);
    deck = CreateDeck(LargeNoSmithy);

    // initialize game
    initializeGame(2, kingdom, 42, state);

    // get the current player
    currentPlayer = whoseTurn(state);

    // copy in deck, set decksize, and shuffle
    memcpy(state->deck[currentPlayer], deck, LARGE_DECK_SIZE);
    state->deckCount[currentPlayer] = playerDeckSize;
    shuffle(currentPlayer, state);

    // copy first hand to player
    memcpy(state->hand[currentPlayer], oneSmithy, 5 * sizeof(Card));
    state->handCount[currentPlayer] = 5;

    // TEST single play of Smithy
    startHandSize = state->handCount[currentPlayer];
    startDeckSize = state->deckCount[currentPlayer];

    playSmithy(state, 0);

    newHandSize = state->handCount[currentPlayer];
    newDeckSize = state->deckCount[currentPlayer];

    AssertTrue(newHandSize == (startHandSize + 2))
        ? printf("PASS: Player handsize increased by 2.\n")
        : printf("** FAIL: Player handsize did not increase by 2.\n");

    AssertTrue(newDeckSize == (startDeckSize - 3))
        ? printf("PASS: decksize decreased by 3.\n")
        : printf("** FAIL: deck size did not decrease by 3.\n");

    AssertTrue(HandCount(smithy, currentPlayer, state) == 0)
        ? printf("PASS: Player has no smithys remaining in hand (started with one, played one).\n")
        : printf("PASS: Player still has smithys in hand.\n");

    // TEST multiple plays of smithy

    // reset the deck, decksize, player hand, and player handsize
    memcpy(state->deck[currentPlayer], deck, LARGE_DECK_SIZE);
    state->deckCount[currentPlayer] = LARGE;
    shuffle(currentPlayer, state);

    memcpy(state->hand[currentPlayer], fiveSmithys, 5 * sizeof(Card));
    state->handCount[currentPlayer] = 5;

    startHandSize = state->handCount[currentPlayer];
    startDeckSize = state->deckCount[currentPlayer];

    for (i = 0; i < 5; i++)
    {
        playSmithy(state, i);
    }

    newHandSize = state->handCount[currentPlayer];
    newDeckSize = state->deckCount[currentPlayer];

    AssertTrue(newHandSize == (startHandSize + 10))
        ? printf("PASS: Player handsize increased by 10.\n")
        : printf("** FAIL: Player handsize did not increase by 10.\n");

    AssertTrue(newDeckSize == (startDeckSize - 15))
        ? printf("PASS: decksize decreased by 15.\n")
        : printf("** FAIL: deck size did not decrease by 15.\n");

    AssertTrue(HandCount(smithy, currentPlayer, state) == 0)
        ? printf("PASS: Player has no smithys remaining in hand (started with 5, played 5).\n")
        : printf("PASS: Player still has smithys in hand.\n");

    // TEST smithy w/ deck & discard size of 0

    // reset the deck, no need to shuffle (in theory...)
    memcpy(state->deck[currentPlayer], deck, LARGE_DECK_SIZE);

    // explicitly set deckcount and discard count to 0
    state->deckCount[currentPlayer] = 0;
    state->discardCount[currentPlayer] = 0;

    // reset players hand
    memcpy(state->hand[currentPlayer], oneSmithy, 5 * sizeof(Card));
    state->handCount[currentPlayer] = 5;

    startHandSize = state->handCount[currentPlayer];
    startDeckSize = state->deckCount[currentPlayer];

    playSmithy(state, 0);

    newHandSize = state->handCount[currentPlayer];
    newDeckSize = state->deckCount[currentPlayer];

    AssertTrue(newHandSize == (startHandSize - 1))
        ? printf("PASS: Player handsize decreased by 1 (no cards to draw).\n")
        : printf("** FAIL: Player handsize did not decrease by 1 (change in some other way).\n");

    AssertTrue(newDeckSize == 0)
        ? printf("PASS: decksize did not change.\n")
        : printf("** FAIL: decksize changed.\n");

    AssertTrue(HandCount(smithy, currentPlayer, state) == 0)
        ? printf("PASS: Player has no smithys remaining in hand (started with one, played one).\n")
        : printf("PASS: Player still has smithys in hand.\n");

    // cleanup
    free(state);
    free(kingdom);
    free(deck);
}