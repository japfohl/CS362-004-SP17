/*****************************************************************************************
* NAME:         Joseph A Pfohl
* DATE:         4/26/2017
* ASSIGNMENT:   Assignment #3 - Unit Tests
* DESCRIPTION:  Unit tests for the initializeGame function from dominion.c
*****************************************************************************************/

#include "../../dominion/dominion.h"
#include "../../dominion/dominion_helpers.h"
#include "../../dominion/rngs.h"
#include "../helpers/test_helpers.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void TestInitializeGame();

int main(int argc, char ** argv)
{
    TestInitializeGame();
    return 0;
}

void TestInitializeGame()
{
    // variable declarations
    GameState *game, *gameCopy;
    int i;

    // create our test game object and a copy of that object
    game = newGame();
    gameCopy = newGame();
    memcpy(gameCopy, game, sizeof(GameState));

    // make sure our states copied correctly
    AssertEqual(game, gameCopy, CompareGameState)
        ? printf("PASS: Testing states copied successfully.\n")
        : printf("FAIL: Copying testing states was unsuccessfull.\n");

    // test passing in too many players

    // test passing in too few players

    // test passing in duplicate kingdom cards

    // test passing in all same kingdom cards

    for (i = 2; i <= 4; i++)
    {
        // test for correct number of curse cards

        // test for correct number of victory cards

        // test for correct number of treasure cards

        // test number of victory cards in supply piles
    }

    // test number of regular cards in supply piles

    // test players deck counts correct

    // test all players got 3 estates

    // test all players got 7 coppers

    // test all players decks shuffled

    // test all players initial hand size

    // test all players initial discard count

    // test embargo token count on all supply piles

    // test number of actions for starting player

    // test number of buys for starting player

    // test handsize for staring player

    // test decksize for starting player

    // cleanup!
    free(game);
    free(gameCopy);
}