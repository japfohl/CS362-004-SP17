/*****************************************************************************************
* NAME:         Joseph A Pfohl
* DATE:         4/26/2017
* ASSIGNMENT:   Assignment #3 - Unit Tests
* DESCRIPTION:  Unit tests for the isGameOver() function from dominion.c
*****************************************************************************************/

// INCLUDES

#include "../../dominion/dominion.h"
#include "../../dominion/dominion_helpers.h"
#include "../../dominion/rngs.h"
#include "../helpers/test_helpers.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// FUNCTION DECLARATIONS

void TestIsGameOver();

// GLOBALS

int NEG_ONE = -1;
int ZERO = 0;
int ONE = 1;

// MAIN

int main(int argc, char ** argv)
{
    TestIsGameOver();
    return 0;
}

// FUNCTION DEFINITIONS

void TestIsGameOver()
{
    // variable declaration
    GameState *game;
    Cards deck;
    int count1, count2, count3;

    // allocate memory
    game = newGame();
    deck = CreateKingdom(GoodNoVictory);

    // initialize the game
    initializeGame(2, deck, 42, game);

    // TEST: province count = 0 returns true
    count1 = game->supplyCount[province];
    game->supplyCount[province] = 0;

    AssertTrue(isGameOver(game))
        ? printf("PASS: returned TRUE when province count = 0.\n")
        : printf("** FAIL: did not return TRUE when province count = 0.\n");

    game->supplyCount[province] = count1;

    // TEST: three supply piles empty returns true
    count1 = game->supplyCount[feast];
    game->supplyCount[feast] = 0;

    count2 = game->supplyCount[adventurer];
    game->supplyCount[adventurer] = 0;

    count3 = game->supplyCount[remodel];
    game->supplyCount[remodel] = 0;

    AssertTrue(isGameOver(game))
        ? printf("PASS: returned TRUE when 3 piles empty.\n")
        : printf("** FAIL: did not return TRUE when 3 piles empty.\n");

    game->supplyCount[feast] = count1;
    game->supplyCount[adventurer] = count2;
    game->supplyCount[remodel] = count3;

    // TEST: everything full returns false

    AssertFalse(isGameOver(game))
        ? printf("PASS: returned FALSE when all piles not empty.\n")
        : printf("** FAIL: returned TRUE when all piles not empty.\n");

    // TEST: all money's empty returns true
    count1 = game->supplyCount[copper];
    game->supplyCount[copper] = 0;

    count2 = game->supplyCount[silver];
    game->supplyCount[silver] = 0;

    count3 = game->supplyCount[gold];
    game->supplyCount[gold] = 0;

    AssertTrue(isGameOver(game))
        ? printf("PASS: returned TRUE when all money piles empty.\n")
        : printf("** FAIL: did not return TRUE when all money piles empty.\n");

    game->supplyCount[copper] = count1;
    game->supplyCount[silver] = count2;
    game->supplyCount[gold] = count3;

    // TEST: curse, estate, and duchy empty return true
    count1 = game->supplyCount[curse];
    game->supplyCount[curse] = 0;

    count2 = game->supplyCount[estate];
    game->supplyCount[estate] = 0;

    count3 = game->supplyCount[duchy];
    game->supplyCount[duchy] = 0;

    AssertTrue(isGameOver(game))
        ? printf("PASS: returned TRUE when curse, estate, and duchy empty.\n")
        : printf("** FAIL: did not return TRUE when curse, estate, and duchy empty.\n");

    // cleanup
    free(game);
    free(deck);
}