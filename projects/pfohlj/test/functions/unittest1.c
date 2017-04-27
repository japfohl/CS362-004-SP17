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

// FUNCTION DECLARATIONS

void TestInitializeGame();

// GLOBALS

int NEG_ONE = -1;
int ZERO = 0;
int ONE = 1;

// MAIN

int main(int argc, char ** argv)
{
    TestInitializeGame();
    return 0;
}

// FUNCTION DEFINITIONS

void TestInitializeGame()
{
    // variable declarations
    GameState *game, *blankState;
    int i, j, result;
    Cards testKingdom = NULL;

    // create our test game object and a copy of that object
    game = newGame();
    blankState = newGame();
    memcpy(blankState, game, sizeof(GameState));

    printf("BEGIN TESTS: initializeGame() from \"dominion.c\"\n\n");

    // TEST: states copied correctly
    AssertEqual(game, blankState, CompareGameState)
        ? printf("PASS: Testing states copied successfully.\n")
        : printf("** FAIL: Copying testing states was unsuccessfull.\n");

    // TEST: passing in too many players
    testKingdom = Reset(testKingdom, GoodNoVictory, game, blankState);
    result = initializeGame(5, testKingdom, 42, game);
    
    AssertEqual(&result, &NEG_ONE, CompareInt)
        ? printf("PASS: Correctly returned -1 for too many players.\n")
        : printf("** FAIL: Incorrectly returned !(-1) for too many players\n");


    // TEST: passing in too few players
    testKingdom = Reset(testKingdom, GoodNoVictory, game, blankState);
    result = initializeGame(1, testKingdom, 42, game);
    
    AssertEqual(&result, &NEG_ONE, CompareInt)
        ? printf("PASS: Correctly returned -1 for too few players.\n")
        : printf("** FAIL: Incorrectly returned !(-1) for too many players\n");


    // TEST: Good set of kingdom cards, no victory cards
    testKingdom = Reset(testKingdom, GoodNoVictory, game, blankState);
    result = initializeGame(2, testKingdom, 42, game);

    AssertEqual(&result, &ZERO, CompareInt)
        ? printf("PASS: Correctly returned 0 with good kingdom cards & no victory cards.\n")
        : printf("** FAIL: Did not return 0 for good set of kingdom cards & no victory cards\n");

    // TEST: Good set of kingdom cards, with victory cards
    testKingdom = Reset(testKingdom, GoodWithVictory, game, blankState);
    result = initializeGame(2, testKingdom, 42, game);

    AssertEqual(&result, &ZERO, CompareInt)
        ? printf("PASS: Correctly returned 0 with good kingdom cards including victory cards.\n")
        : printf("** FAIL: Did not return 0 for good set of kingdom cards including victory cards\n");

    // TEST: Bad set of kingdom cards, with duplicates
    testKingdom = Reset(testKingdom, BadDuplicate, game, blankState);
    result = initializeGame(2, testKingdom, 42, game);

    AssertNotEqual(&result, &ZERO, CompareInt)
        ? printf("PASS: Function caught and handled duplicate cards in kingdom.\n")
        : printf("** FAIL: Function did not catch and handle duplicate cards in kingdom.\n");

    // TEST: Bad set of kingdom cards, < 10
    testKingdom = Reset(testKingdom, BadNotEnough, game, blankState);
    result = initializeGame(2, testKingdom, 42, game);

    AssertNotEqual(&result, &ZERO, CompareInt)
        ? printf("PASS: Function caught and handled < 10 kingdom cards.\n")
        : printf("** FAIL: Function did not catch and handle < 10 kingdom cards.\n");

    // TEST: Bad set of kingdom cards, > 10
    testKingdom = Reset(testKingdom, BadTooMany, game, blankState);
    result = initializeGame(2, testKingdom, 42, game);

    AssertNotEqual(&result, &ZERO, CompareInt)
        ? printf("PASS: Function caught and handled > 10 kingdom cards.\n")
        : printf("** FAIL: Function did not catch and handle > 10 kingdom cards.\n");

    // TEST: Bad set of kingdom cards, invalid cards for supply
    testKingdom = Reset(testKingdom, BadWithInvalidSupplyCard, game, blankState);
    result = initializeGame(2, testKingdom, 42, game);

    AssertNotEqual(&result, &ZERO, CompareInt)
        ? printf("PASS: Function caught and handled invalid supply cards.\n")
        : printf("** FAIL: Function did not catch and handle invalid supply cards.\n");

    for (i = 2; i <= 4; i++)
    {
        // expected values
        int expectedCurses = 10 * (i - 1);
        int expectedVictory = (i == 2) ? 8 : 12;
        int expectedSupply = 10;
        int expectedCopper = 60 - (7 * i);
        int expectedSilver = 40;
        int expectedGold = 30;

        // reset
        testKingdom = Reset(testKingdom, GoodWithVictory, game, blankState);
        result = initializeGame(i, testKingdom, 42, game);

        // TEST for correct number of curse cards
        AssertEqual(&expectedCurses, &game->supplyCount[curse], CompareInt)
            ? printf("PASS: Correct number of curses for a %d player game.\n", i)
            : printf("** FAIL: Incorrect number of curses for a %d player game.\n", i);

        // TEST for correct number of victory cards
        AssertEqual(&expectedVictory, &game->supplyCount[estate], CompareInt)
            ? printf("PASS: Correct number of estates for a %d player game.\n", i)
            : printf("** FAIL: Incorrect number of estates for a %d player game.\n", i);

        AssertEqual(&expectedVictory, &game->supplyCount[duchy], CompareInt)
            ? printf("PASS: Correct number of duchys for a %d player game.\n", i)
            : printf("** FAIL: Incorrect number of duchys for a %d player game.\n", i);

        AssertEqual(&expectedVictory, &game->supplyCount[province], CompareInt)
            ? printf("PASS: Correct number of provinces for a %d player game.\n", i)
            : printf("** FAIL: Incorrect number of provinces for a %d player game.\n", i);
       
        // TEST for correct number of treasure cards
         AssertEqual(&expectedCopper, &game->supplyCount[copper], CompareInt)
            ? printf("PASS: Correct number of coppers for a %d player game.\n", i)
            : printf("** FAIL: Incorrect number of coppers for a %d player game.\n", i);

        AssertEqual(&expectedSilver, &game->supplyCount[silver], CompareInt)
            ? printf("PASS: Correct number of silvers for a %d player game.\n", i)
            : printf("** FAIL: Incorrect number of silvers for a %d player game.\n", i);

        AssertEqual(&expectedGold, &game->supplyCount[gold], CompareInt)
            ? printf("PASS: Correct number of gold for a %d player game.\n", i)
            : printf("** FAIL: Incorrect number of gold for a %d player game.\n", i);

        // TEST supply pile counts
        for (j = 0; j < 10; j++)
        {
            int card = testKingdom[j];
            
            if (card == great_hall || card == gardens)
            {
                AssertEqual(&expectedVictory, &game->supplyCount[card], CompareInt)
                    ? printf("PASS: Supply victory card count correct for a %d player game\n", i)
                    : printf("** FAIL: Supply victory card count incorrect for a %d player game\n", i);
            }
            else
            {
                AssertEqual(&expectedSupply, &game->supplyCount[card], CompareInt)
                    ? printf("PASS: Supply card count correct for a %d player game\n", i)
                    : printf("** FAIL: Supply card count incorrect for a %d player game\n", i);
            }
        }
    }

    // test players deck counts correct
    testKingdom = Reset(testKingdom, GoodNoVictory, game, blankState);
    result = initializeGame(4, testKingdom, 42, game);

    Bool deckCountsCorrect = TRUE;

    for (i = 0; i < 4 && deckCountsCorrect; i++)
    {
        if (i == 0)
        {
            if (game->deckCount[i] != 5)
            {
                deckCountsCorrect = FALSE;
            }
        }
        else
        {
            if (game->deckCount[i] != 10)
            {
                deckCountsCorrect = FALSE;
            }
        }
    }

    AssertTrue(deckCountsCorrect)
        ? printf("PASS: All player deck counts correct\n")
        : printf("** FAIL: Player %d's deck count was not correct\n", i);

    // test all players got 3 estates & 7 coppers
    Bool estateCountCorrect = TRUE;
    Bool copercountCorrect = TRUE;

    for (i = 0; i < 4; i++)
    {
        int copperCount = 0;
        int estateCount = 0;

        if (i == 0)
        {
            for (j = 0; j < 5; j++)
            {
                game->hand[i][j] == copper ? copperCount++ : estateCount++;
                game->deck[i][j] == copper ? copperCount++ : estateCount++;

            }
        }
        else
        {
            for (j = 0; j < 10; j++)
            {
                game->deck[i][j] == copper ? copperCount++ : estateCount++;
            }
        }

        if (copperCount != 7)
        {
            copercountCorrect = FALSE;
        }

        if (estateCount != 3)
        {
            estateCountCorrect = FALSE;
        }
    }

    AssertTrue(copercountCorrect)
        ? printf("PASS: copper count correct for all decks.\n")
        : printf("FAIL: incorrect copper count found.\n");

    // test all players decks shuffled

    int unshuffledDeck[10] = {estate, estate, estate, copper, copper,
                              copper, copper, copper, copper, copper};

    int firstPlayerDeck[10];
    for (i = 0; i < 5; i++)
    {
        firstPlayerDeck[i] = game->hand[0][i];
        firstPlayerDeck[i+5] = game->deck[0][i];
    }

    for (i = 0; i < 4; i++)
    {
        if (i == 0)
        {
            AssertArraysNotEqual(firstPlayerDeck, sizeof(firstPlayerDeck),
                                 unshuffledDeck, sizeof(unshuffledDeck))
                                 ? printf("PASS: Player %d's deck is shuffled\n", i+1)
                                 : printf("FAIL: Player %d's deck is not shuffled\n", i+1);
        }
        else
        {
            AssertArraysNotEqual(game->deck[i], 10 * sizeof(int),
                                 unshuffledDeck, sizeof(unshuffledDeck))
                                 ? printf("PASS: Player %d's deck is shuffled\n", i+1)
                                 : printf("FAIL: Player %d's deck is not shuffled\n", i+1);
        }
    }

    // test number of actions for starting player
    AssertEqual(&game->numActions, &ONE, CompareInt)
        ? printf("PASS: Starting player action count correct.\n")
        : printf("FAIL: Starting player action count incorrect.\n");

    // test number of buys for starting player
    AssertEqual(&game->numBuys, &ONE, CompareInt)
        ? printf("PASS: Starting player buy count correct.\n")
        : printf("FAIL: Starting player buy count incorrect.\n");

    // cleanup!
    free(testKingdom);
    free(game);
    free(blankState);
}