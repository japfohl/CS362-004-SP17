/*****************************************************************************************
* NAME:         Joseph A Pfohl
* DATE:         4/26/2017
* ASSIGNMENT:   Assignment #3 - Unit Tests
* DESCRIPTION:  Unit tests for the shuffle() function from dominion.c
*****************************************************************************************/

#include "../../dominion/dominion.h"
#include "../../dominion/dominion_helpers.h"
#include "../../dominion/rngs.h"
#include "../helpers/test_helpers.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// FUNCTION DECLARATIONS

void TestShuffle();

// GLOBALS

int NEG_ONE = -1;
int ZERO = 0;
int ONE = 1;

// MAIN

int main(int argc, char ** argv)
{
    TestShuffle();
    return 0;
}

// FUNCTION DEFINITIONS

void TestShuffle()
{   
    // variable declarations
    int result, saveCount;
    GameState *game, *blankState;
    Cards deck;

    // allocate some memory
    game = newGame();
    blankState = newGame();
    deck = CreateKingdom(GoodNoVictory);

    // initialize the state
    initializeGame(4, deck, 42, game);

    // TEST deck count < 1 - EXPECT -1
    saveCount = game->deckCount[0];
    game->deckCount[0] = 0;

    result = shuffle(0, game);

    AssertEqual(&result, &NEG_ONE, CompareInt)
        ? printf("PASS: shuffle() returned -1 for empty deck.\n")
        : printf("** FAIL: shuffle() did not return -1 for empty deck.\n");

    game->deckCount[0] = saveCount;

    // TEST invalid player numbers (-1)

    result = shuffle(-1, game);

    AssertNotEqual(&result, &ZERO, CompareInt)
        ? printf("PASS: shuffle() caught and handled incorrect player number '-1'.\n")
        : printf("** FAIL: shuffle() did not catch and handle invalid player number '-1'.\n");

    // TEST invalid player number (4)

    result = shuffle(10, game);

    AssertNotEqual(&result, &ZERO, CompareInt)
        ? printf("PASS: shuffle() caught and handled incorrect player number '10'.\n")
        : printf("** FAIL: shuffle() did not catch and handle invalid player number '10'.\n");

    // TEST valid player number but not enough players (2 players, player number 2)

    memcpy(game, blankState, sizeof(GameState));
    initializeGame(2, deck, 42, game);

    result = shuffle(2, game);

    AssertNotEqual(&result, &ZERO, CompareInt)
        ? printf("PASS: shuffle() caught player number (2) larger than largest player number (1).\n")
        : printf("** FAIL: shuffle() did not catch player number (2) larger than largest player number (1).\n");

    // TEST shuffle small deck

    // create a new deck
    free(deck);
    deck = CreateDeck(SmallDeck);

    // copy small deck to a players deck and shuffle
    memcpy(game->deck[0], deck, SMALL_DECK_SIZE);
    shuffle(0, game);

    AssertArraysNotEqual(game->deck[0], SMALL_DECK_SIZE, deck, SMALL_DECK_SIZE)
        ? printf("PASS: shuffle() successfully shuffled a small deck.\n")
        : printf("** FAIL: suffle() unsuccessfully shuffled a small deck.\n");

    // TEST shuffle medium sized deck

    // create a new deck
    free(deck);
    deck = CreateDeck(MediumDeck);

    // copy small deck to a players deck and shuffle
    memcpy(game->deck[0], deck, MEDIUM_DECK_SIZE);
    shuffle(0, game);

    AssertArraysNotEqual(game->deck[0], MEDIUM_DECK_SIZE, deck, MEDIUM_DECK_SIZE)
        ? printf("PASS: shuffle() successfully shuffled a medium deck.\n")
        : printf("** FAIL: suffle() unsuccessfully shuffled a medium deck.\n");

    // TEST shuffle large deck

    // create a new deck
    free(deck);
    deck = CreateDeck(LargeDeck);

    // copy small deck to a players deck and shuffle
    memcpy(game->deck[0], deck, LARGE_DECK_SIZE);
    result = shuffle(0, game);

    AssertArraysNotEqual(game->deck[0], LARGE_DECK_SIZE, deck, LARGE_DECK_SIZE)
        ? printf("PASS: shuffle() successfully shuffled a large deck.\n")
        : printf("** FAIL: suffle() unsuccessfully shuffled a large deck.\n");

    // TEST shuffle returns 0 on normal run w/ no anomalous input

    AssertEqual(&result, &ZERO, CompareInt)
        ? printf("PASS: shuffle() returned 0 on normal run.\n")
        : printf("** FAIL: shuffle() did not return 0 on normal run.\n");

    // cleanup
    free(game);
    free(blankState);
    free(deck);
}