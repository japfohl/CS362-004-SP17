/*****************************************************************************************
* NAME:         Joseph A Pfohl
* DATE:         5/26/2017
* ASSIGNMENT:   Assignment #5 - Unit Tests for partner's code
* DESCRIPTION:  Unit tests for the fullDeckCount function from dominion.c
*****************************************************************************************/

#include "../../dominion/dominion.h"
#include "../../dominion/dominion_helpers.h"
#include "../../dominion/rngs.h"
#include "../helpers/test_helpers.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// FUNCTION DECLARATIONS

void TestFullDeckCount();

// GLOBALS

int NEG_ONE = -1;
int ZERO = 0;
int ONE = 1;

// MAIN

int main(int argc, char ** argv)
{
    TestFullDeckCount();
    return 0;
}

// FUNCTION DEFINITIONS

void TestFullDeckCount()
{
    // variable declarations
    GameState *game;
    Cards deck;
    int result, handCount, deckCount, discardCount, numRemaining, index, i, expectedCount;

    // allocate some memory
    game = newGame();
    deck = CreateKingdom(GoodNoVictory);

    // initialize the game
    initializeGame(2, deck, 42, game);

    // TEST invalid player number (-1)

    result = fullDeckCount(-1, copper, game);

    AssertEqual(&result, &NEG_ONE, CompareInt)
        ? printf("PASS: fullDeckCount() returned error result (-1) on player number '-1'.\n")
        : printf("** FAIL: fullDeckCount() did not return error result (-1) on player number '-1'.\n");

    // TEST invalid player number (10)

    result = fullDeckCount(10, copper, game);

    AssertEqual(&result, &NEG_ONE, CompareInt)
        ? printf("PASS: fullDeckCount() returned error result (-1) on player number '10'.\n")
        : printf("** FAIL: fullDeckCount() did not return error result (-1) on player number '10'.\n");

    // TEST invalid card number

    result = fullDeckCount(0, 1000, game);

    AssertEqual(&result, &NEG_ONE, CompareInt)
        ? printf("PASS: fullDeckCount() returned error result (-1) on invalid card (1000).\n")
        : printf("** FAIL: fullDeckCount() did not return error result (-1) on invalid card (1000).\n");

    // TEST count for small deck
    
    // set up random number generator
    srand(time(NULL));
    
    // create the new deck
    free(deck);
    deck = CreateDeck(SmallCountDeck);

    // pick random numbers for the amount in each counted section

    numRemaining = SMALL;

    handCount = rand() % 10 + 1; // 1-10 cards in hand
    numRemaining -= handCount;

    deckCount = rand() % numRemaining + 1; // 1-numRemaining in deck
    numRemaining -= deckCount;

    discardCount = numRemaining; // remaining cards in discard

    // copy deck parts into player's hand, deck, and discard
    
    i = 0;
    index = 0;

    while (i < handCount)
    {
        game->hand[1][i] = deck[index];
        i++;
        index++;
    }

    game->handCount[1] = handCount;

    i = 0;

    while (i < deckCount)
    {
        game->deck[1][i] = deck[index];
        i++;
        index++;
    }

    game->deckCount[1] = deckCount;

    i = 0;

    while (i < discardCount)
    {
        game->discard[1][i] = deck[index];
        i++;
        index++;
    }

    game->discardCount[1] = discardCount;

    result = fullDeckCount(1, copper, game);

    expectedCount = SMALL / 2;
    AssertEqual(&result, &expectedCount, CompareInt)
        ? printf("PASS: returned count 10 of copper for SMALL deck (20 cards).\n")
        : printf("** FAIL: returned incorrect count of %d for SMALL deck (20 cards).\n", result);

    // TEST count for medium deck

    // create the new deck
    free(deck);
    deck = CreateDeck(MediumCountDeck);

    // pick random numbers for the amount in each counted section

    numRemaining = MEDIUM;

    handCount = rand() % 10 + 1; // 1-10 cards in hand
    numRemaining -= handCount;

    deckCount = rand() % numRemaining + 1; // 1-numRemaining in deck
    numRemaining -= deckCount;

    discardCount = numRemaining; // remaining cards in discard

    // copy deck parts into player's hand, deck, and discard
    
    i = 0;
    index = 0;

    while (i < handCount)
    {
        game->hand[1][i] = deck[index];
        i++;
        index++;
    }

    game->handCount[1] = handCount;

    i = 0;

    while (i < deckCount)
    {
        game->deck[1][i] = deck[index];
        i++;
        index++;
    }

    game->deckCount[1] = deckCount;

    i = 0;

    while (i < discardCount)
    {
        game->discard[1][i] = deck[index];
        i++;
        index++;
    }

    game->discardCount[1] = discardCount;

    result = fullDeckCount(1, copper, game);

    expectedCount = MEDIUM / 2;
    AssertEqual(&result, &expectedCount, CompareInt)
        ? printf("PASS: returned count of 15 copper for MEDIUM deck (30 cards).\n")
        : printf("** FAIL: returned incorrect count of %d for MEDIUM deck (30 cards).\n", result);

    // TEST count for large deck

    // create the new deck
    free(deck);
    deck = CreateDeck(LargeCountDeck);

    // pick random numbers for the amount in each counted section

    numRemaining = LARGE;

    handCount = rand() % 10 + 1; // 1-10 cards in hand
    numRemaining -= handCount;

    deckCount = rand() % numRemaining + 1; // 1-numRemaining in deck
    numRemaining -= deckCount;

    discardCount = numRemaining; // remaining cards in discard

    // copy deck parts into player's hand, deck, and discard
    
    i = 0;
    index = 0;

    while (i < handCount)
    {
        game->hand[1][i] = deck[index];
        i++;
        index++;
    }

    game->handCount[1] = handCount;

    i = 0;

    while (i < deckCount)
    {
        game->deck[1][i] = deck[index];
        i++;
        index++;
    }

    game->deckCount[1] = deckCount;

    i = 0;

    while (i < discardCount)
    {
        game->discard[1][i] = deck[index];
        i++;
        index++;
    }

    game->discardCount[1] = discardCount;

    result = fullDeckCount(1, copper, game);

    expectedCount = LARGE / 2;
    AssertEqual(&result, &expectedCount, CompareInt)
        ? printf("PASS: returned count of 20 copper for LARGE deck (40 cards).\n")
        : printf("** FAIL: returned incorrect count of %d for LARGE deck (40 cards).\n", result);

    // cleanup
    free(game);
    free(deck);
}