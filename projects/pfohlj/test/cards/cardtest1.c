/*****************************************************************************************
* NAME:         Joseph A Pfohl
* DATE:         4/26/2017
* ASSIGNMENT:   Assignment #3 - Unit Tests
* DESCRIPTION:  Unit tests for Adventurer() card implementation
*****************************************************************************************/

#include "../../dominion/dominion.h"
#include "../../dominion/dominion_helpers.h"
#include "../../dominion/rngs.h"
#include "../helpers/test_helpers.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// FUNCTION DECLARATIONS

void TestAdventurer();

// GLOBALS

int NEG_ONE = -1;
int ZERO = 0;
int ONE = 1;

// MAIN

int main(int argc, char ** argv)
{
    TestAdventurer();
    return 0;
}

// FUNCTION DEFINITIONS

void TestAdventurer()
{
    // variables
    GameState *game;
    Cards kingdom;
    Cards testDeck;
    Player currentPlayer;

    int startHandCount,
        newHandCount,
        startDeckAndDiscardCount,
        newDeckAndDiscardCount,
        secondPlayerDeckCount,
        secondPlayerHandCount,
        secondPlayerDiscardCount,
        i;

    // allocate memory
    game = newGame();
    kingdom = CreateKingdom(GoodNoVictory);

    // create deck w/ size 40 and 20 treasures
    testDeck = CreateDeck(WithTreasures); 

    // initialize the state
    initializeGame(2, kingdom, 42, game);

    // copy test deck into currentPlayer and shuffle
    currentPlayer = whoseTurn(game);
    memcpy(game->deck[currentPlayer], testDeck, LARGE_DECK_SIZE);
    game->deckCount[currentPlayer] = LARGE;
    shuffle(currentPlayer, game);

    // get secondPlayerCardCount
    secondPlayerDeckCount = game->deckCount[1];
    secondPlayerHandCount = game->handCount[1];
    secondPlayerDiscardCount = game->discardCount[1];

    // get starting values
    startHandCount = HandCount(copper, currentPlayer, game);
    startDeckAndDiscardCount = DeckAndDiscardCount(copper, currentPlayer, game);

    // play adventurer once
    Adventurer(game);

    // get new counts
    newHandCount = HandCount(copper, currentPlayer, game);
    newDeckAndDiscardCount = DeckAndDiscardCount(copper, currentPlayer, game);

    // TESTS: test single draw effects on hand / deck & discard

    AssertTrue(newHandCount == (startHandCount + 2))
        ? printf("PASS: player handcount increased by two.\n")
        : printf("** FAIL: player handcount did NOT increase by two.\n");

    AssertTrue(newDeckAndDiscardCount == (startDeckAndDiscardCount - 2))
        ? printf("PASS: player deckcount + discardcount decreased by two.\n")
        : printf("** FAIL: player deckcount + discardcount did not decrease by two.\n");

    // perform consecutive plays of adventurer

    startHandCount = newHandCount;
    startDeckAndDiscardCount = newDeckAndDiscardCount;

    for (i = 0; i < 5; i++)
    {
        Adventurer(game);
    }

    newHandCount = HandCount(copper, currentPlayer, game);
    newDeckAndDiscardCount = DeckAndDiscardCount(copper, currentPlayer, game);

    // TESTS: test multiple draw effects on hand / deck & discard

    AssertTrue(newHandCount == (startHandCount + 10))
        ? printf("PASS: player handcount increased by 10.\n")
        : printf("** FAIL: player handcount did NOT increase by 10.\n");

    AssertTrue(newDeckAndDiscardCount == (startDeckAndDiscardCount - 10))
        ? printf("PASS: player deckcount + discardcount decreased by 10.\n")
        : printf("** FAIL: player deckcount + discardcount did not decrease by 10.\n");

    // create deck with no treasures
    free(testDeck);
    testDeck = CreateDeck(WithoutTreasures);

    // replace player's deck with treasure-less deck and shuffle
    memcpy(game->deck[currentPlayer], testDeck, LARGE_DECK_SIZE);
    shuffle(currentPlayer, game);

    // get starting values
    startHandCount = HandCount(copper, currentPlayer, game);
    startDeckAndDiscardCount = DeckAndDiscardCount(copper, currentPlayer, game);

    // play adventurer once
    Adventurer(game);

    // get new counts
    newHandCount = HandCount(copper, currentPlayer, game);
    newDeckAndDiscardCount = DeckAndDiscardCount(copper, currentPlayer, game);

    // TESTS: test single draw effects on hand / deck & discard

    AssertTrue(newHandCount == startHandCount)
        ? printf("PASS: player handcount did not change.\n")
        : printf("** FAIL: player handcount changed.\n");

    AssertTrue(newDeckAndDiscardCount == startDeckAndDiscardCount)
        ? printf("PASS: player deckcount did not change.\n")
        : printf("** FAIL: player deckcount changed.\n");

    // perform consecutive plays of adventurer

    startHandCount = newHandCount;
    startDeckAndDiscardCount = newDeckAndDiscardCount;

    for (i = 0; i < 5; i++)
    {
        Adventurer(game);
    }

    newHandCount = HandCount(copper, currentPlayer, game);
    newDeckAndDiscardCount = DeckAndDiscardCount(copper, currentPlayer, game);

    // TESTS: test multiple draw effects on hand / deck & discard

    AssertTrue(newHandCount == startHandCount)
        ? printf("PASS: player handcount did not change.\n")
        : printf("** FAIL: player handcount changed.\n");

    AssertTrue(newDeckAndDiscardCount == startDeckAndDiscardCount)
        ? printf("PASS: player deckcount did not change.\n")
        : printf("** FAIL: player deckcount changed.\n");

    // TEST: make sure second player's deck / hand / discard were not affected

    AssertEqual(&secondPlayerDeckCount, &game->deckCount[1], CompareInt)
        ? printf("PASS: second player deck count not affected.\n")
        : printf("FAIL: second player deck count affected.\n");

    AssertEqual(&secondPlayerHandCount, &game->handCount[1], CompareInt)
        ? printf("PASS: second player hand count not affected.\n")
        : printf("FAIL: second player hand count affected.\n");

    AssertEqual(&secondPlayerDiscardCount, &game->discardCount[1], CompareInt)
        ? printf("PASS: second player discard count not affected.\n")
        : printf("FAIL: second player discard count affected.\n");

    // cleanup
    free(game);
    free(kingdom);
    free(testDeck);
}