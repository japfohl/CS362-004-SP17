/*****************************************************************************************
*        NAME:  Joseph A Pfohl
*        DATE:  5/26/2016
*       CLASS:  CS362-400 Software Engineering II
*  ASSIGNMENT:  Assignment #5 - Random Testing for partner's code
* DESCRIPTION:  Random tests for the playAdventurer() card implemented in dominion.c
*****************************************************************************************/

#include "../../dominion/dominion.h"
#include "../../dominion/dominion_helpers.h"
#include "../../dominion/rngs.h"
#include "../helpers/test_helpers.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

void RandomTestAdventurer();

int main()
{
    int i;

    SelectStream(0);
    PutSeed(42);

    for (i = 0; i < 2000; i++)
    {
        RandomTestAdventurer();
    }

    return 0;
}

void RandomTestAdventurer()
{
    // 1. create our randomly generated game state
    GameState state;

    int i;

    for (i = 0; i < sizeof(GameState); i++)
    {
        ((char*)&state)[i] = floor(Random() * 256);
    }

    /*      
    **      Adventurer requires:
    **          - whoseTurn
    **          - deckCount[whoseTurn]
    **          - deck[whoseTurn]
    **          - discardCount[whoseTurn]
    **          - discard[whoseTurn]
    **          - handCount[whoseTurn]
    **          - hand[whoseTurn]
    */

    // 2. Select and set a random player as the active player (whoseTurn)

    int player = (int)floor(Random() * 4);
    state.whoseTurn = player;

    // 3. Determine player's total card count (50 - 500) 

    int totalCardCount = (int)floor(Random() * 450) + 50;

    // 4. Divide totalCardCount between the hand (5 - 15), the discard, and the deck

    // hand
    int handCount = (int)floor(Random() * 10) + 5;
    state.handCount[player] = handCount;

    // discard
    int discardCount = (int)floor(Random() * (totalCardCount - handCount));
    state.discardCount[player] = discardCount;
       
    
    // deck gets remainder
    int deckCount = totalCardCount - handCount - discardCount;
    state.deckCount[player] = deckCount;

    // 5. Create a random set of kingdom cards
    
    Card deck[totalCardCount];

    // assign a random card from all possible cards to each spot in deck
    for (i = 0; i < totalCardCount; i++)
    {
        deck[i] = (int)floor(Random() * treasure_map);
    }

    // 6. Divvy up the random deck

    int currentCard = 0;

    // hand
    for (i = 0; i < handCount; i++)
    {
        state.hand[player][i] = deck[currentCard];
        currentCard++;
    }

    //discard
    for (i = 0; i < discardCount; i++)
    {
        state.discard[player][i] = deck[currentCard];
        currentCard++;
    }

    // deck
    for (i = 0; i < deckCount; i++)
    {
        state.deck[player][i] = deck[currentCard];
        currentCard++;
    }

    /*
    **  Following Adventurer, the following should be true:
    **      - Player hand count should be +1
    **      - Player hand treasure count should be +2
    **      - Player deck & discard treasure count (sum) should be -2
    */

    // 7. Store values needed for validation

    int handTreasureCount = TreasureCount(Hand, &state, player);
    int deckAndDiscardTreasureCount
        = TreasureCount(Deck, &state, player) + TreasureCount(Discard, &state, player);

    // 8. Play Adventurer

    playAdventurer(&state);

    // 9. Get new results for validation

    int newPlayerHandCount = state.handCount[player];
    int newPlayerHandTreasureCount = TreasureCount(Hand, &state, player);
    int newDeckAndDiscardTreasureCount
        = TreasureCount(Deck, &state, player) + TreasureCount(Discard, &state, player);

    // 10. Validate Results

    Bool allTestsPassed = TRUE;

    if (newPlayerHandCount != (handCount + 1))
    {
        allTestsPassed = FALSE;

        printf("FAIL: expected newPlayerHandCount to be %d but it was %d.\n",
            (handCount +1), newPlayerHandCount);
    }

    if (newPlayerHandTreasureCount != (handTreasureCount + 2))
    {
        allTestsPassed = FALSE;

        printf("FAIL: expected newPlayerHandTreasureCount to be %d, but it was %d.\n",
            (handTreasureCount + 2), newPlayerHandTreasureCount);
    }

    if (newDeckAndDiscardTreasureCount != (deckAndDiscardTreasureCount - 2))
    {
        allTestsPassed = FALSE;

        printf("FAIL: expected newDeckAndDiscardTreasureCount to be %d, but it was %d.\n",
            (deckAndDiscardTreasureCount - 2), newDeckAndDiscardTreasureCount);
    }

    if (allTestsPassed)
    {
        printf("PASS: all tests for Adventure() passed.\n");
    }
}