/*****************************************************************************************
* NAME:         Joseph A Pfohl
* DATE:         4/26/2017
* ASSIGNMENT:   Assignment #3 - Unit Tests
* DESCRIPTION:  Unit tests for Feast()
*****************************************************************************************/

#include "../../dominion/dominion.h"
#include "../../dominion/dominion_helpers.h"
#include "../../dominion/rngs.h"
#include "../helpers/test_helpers.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// FUNCTION DECLARATIONS

void TestFeast();

// GLOBALS

int NEG_ONE = -1;
int ZERO = 0;
int ONE = 1;

// MAIN

int main(int argc, char ** argv)
{
    TestFeast();
    return 0;
}

// FUNCTION DEFINITIONS

void TestFeast()
{
    // variables
    GameState *game;
    Card kingdom[10] = {smithy, adventurer, council_room, treasure_map, village,
                        mine, feast, gardens, minion, tribute};

    Card oneFeast[5] = {feast, copper, copper, copper, copper},
         fiveFeasts[5] = {feast, feast, feast, feast, feast};

    Player player;

    int backupCount,
        result,
        feastHandCount,
        discardCount,
        supplyPileCount,
        i;

    // allocate memory
    game = newGame();

    // initialize the state
    initializeGame(2, kingdom, 42, game);
    player = whoseTurn(game);
    memcpy(game->hand[player], oneFeast, START_HAND_SIZE);

    // TEST try buy where supply count < 0

    // set smithy pile to 0
    backupCount = supplyCount(smithy, game);
    game->supplyCount[smithy] = 0;

    /* NOTE: this function doesn't correctly handle feast regardless so this
    will **PROBABLY** infinitely loop.  Also, the user can't re-chose anywhere
    in the loop, the function doesn't discard the played Feast, and finally, it
    appears to leave any "unspent" treasures (which by the way is a patently false
    way of implementing the Feast card.  Feast **GAINS**, but does not **BUY** a
    card.) One of the later expansions (Hinterlands I believe) makes a clear 
    distinction between buying and gaining.  I digress... */

    feastHandCount = HandCount(feast, player, game);
    
    printf("** FAIL: Tests commented out due to infinite loop in Feast(). Fix and uncomment!\n");

    // result = Feast(game, smithy);

    // AssertEqual(&result, &NEG_ONE, CompareInt)
    //     ? printf("PASS: Feast() handled an invalid choice where no cards available (returned -1).\n")
    //     : printf("** FAIL: Feast() did not handle an invlaid choice where no cards available (return -1)\n");

    // AssertTrue(HandCount(feast, player, game) == feastHandCount)
    //     ? printf("PASS: Invalid choice did not count as 'play' for Feast().\n")
    //     : printf("** FAIL: Invalid choice incorrectly counted as 'play' for Feast()\n");
    
    game->supplyCount[smithy] = backupCount;

    // TEST try buy where cost > 5

    feastHandCount = HandCount(feast, player, game);

    printf("** FAIL: Tests commented out due to infinite loop in Feast(). Fix and uncomment!\n");

    // result = Feast(game, province);

    // AssertEqual(&result, &NEG_ONE, CompareInt)
    //     ? printf("PASS: Feast() handled an invalid choice where cost > 5 (returned -1).\n")
    //     : printf("** FAIL: Feast() did not handle an invlaid choice where choice > 5 (return -1)\n");

    // AssertTrue(HandCount(feast, player, game) == feastHandCount)
    //     ? printf("PASS: Invalid choice did not count as 'play' for Feast().\n")
    //     : printf("** FAIL: Invalid choice incorrectly counted as 'play' for Feast()\n");

    // TEST single play
    feastHandCount = HandCount(feast, player, game);
    discardCount = game->discardCount[player];
    supplyPileCount = supplyCount(duchy, game);

    result = Feast(game, duchy);

    AssertEqual(&result, &ZERO, CompareInt)
        ? printf("PASS: Feast() returned 0 on successful play.\n")
        : printf("** FAIL: Feast() did not return 0 on successful play.\n");

    AssertTrue(HandCount(feast, player, game) == (feastHandCount - 1))
        ? printf("PASS: One less feast in hand.\n")
        : printf("** FAIL: Feast count in hand did not change.\n");

    AssertTrue(game->discardCount[player] == (discardCount + 1))
        ? printf("PASS: User gained one card to their discard pile as expected.\n")
        : printf("** FAIL: User did not gain a card to their discard pile as expected.\n");

    AssertTrue(supplyCount(duchy, game) == (supplyPileCount - 1))
        ? printf("PASS: supply count for duchy decreased by 1 as expected.\n")
        : printf("** FAIL: supply count for duchy did not decrease by 1.\n");

    // TEST multiple plays

    // reset everything for clean start
    free(game);
    game = newGame();
    initializeGame(2, kingdom, 42, game);

    // reset the player
    player = whoseTurn(game);
    memcpy(game->hand[player], fiveFeasts, START_HAND_SIZE);

    // get our starting values
    feastHandCount = HandCount(feast, player, game);
    discardCount = game->discardCount[player];
    supplyPileCount = supplyCount(duchy, game);

    // play all 5 feasts in hand
    for (i = 0; i < 5; i++)
    {
        Feast(game, duchy);
    }

    AssertTrue(HandCount(feast, player, game) == 0)
        ? printf("PASS: No feasts remaininging in hand (all 5 played).\n")
        : printf("** FAIL: Feasts still remaining in hand after all played.\n");

    AssertTrue(game->discardCount[player] == (discardCount + 5))
        ? printf("PASS: User gained 5 cards to their discard pile as expected.\n")
        : printf("** FAIL: User did not gain 5 cards to their discard pile as expected.\n");

    AssertTrue(supplyCount(duchy, game) == (supplyPileCount - 5))
        ? printf("PASS: supply count for duchy decreased by 5 as expected.\n")
        : printf("** FAIL: supply count for duchy did not decrease by 5.\n");

    // cleanup
    free(game);
}