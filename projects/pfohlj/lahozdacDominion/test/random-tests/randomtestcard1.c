/*****************************************************************************************
*        NAME:  Joseph A Pfohl
*        DATE:  5/26/2016
*       CLASS:  CS362-400 Software Engineering II
*  ASSIGNMENT:  Assignment #5 - Random Testing for partner's code
* DESCRIPTION:  Random tests for playSmithy() card implementation.
*****************************************************************************************/

#include "../../dominion/dominion.h"
#include "../../dominion/dominion_helpers.h"
#include "../../dominion/rngs.h"
#include "../helpers/test_helpers.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

void RandomTestSmithy();

int main()
{
    int i;

    SelectStream(0);
    PutSeed(42);

    for (i = 0; i < 2000; i++)
    {
        RandomTestSmithy();
    }

    return 0;
}

void RandomTestSmithy()
{
    // 1. create our randomly generated game state
    GameState state;

    int i;

    for (i = 0; i < sizeof(GameState); i++)
    {
        ((char*)&state)[i] = floor(Random() * 256);
    }

    /*      
    **  Smithy Requires:
    **      - whoseTurn
    **      - deckCount[whoseTurn]
    **      - discardCount[whoseTurn]
    **      - handCount[whoseTurn]
    **      - playedCardsCount
    **      - deck[whoseTurn]
    **      - discard[whoseTurn]
    **      - hand[whoseTurn]
    **      - playedCards[0:playedCardsCount]
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

    // 7. Make sure one of the players cards in hand is Smithy

    int smithyPosition = (int)floor(Random() * handCount);
    state.hand[player][smithyPosition] = smithy;

    // 8. Set the number of played cards (0 - 10)

    int numPlayedCards = (int)floor(Random() * 10);
    state.playedCardCount = numPlayedCards;

    // 9. Fill Played cards with random cards from all possible cards

    for (i = 0; i < numPlayedCards; i++)
    {
        state.playedCards[i] = (int)floor(Random() * treasure_map);
    }

    /*
    **  Following Smithy, the following should be true:
    **      - Player handCount should be +2
    **      - player deck and discard count (sum) should be -2
    */

    // 10. Play Smithy

   playSmithy(&state, smithyPosition);

    // 11. Get new results for validation

    int newPlayerHandCount = state.handCount[player];
    int newDeckAndDiscardCount = state.deckCount[player] + state.discardCount[player];

    // 12. Validate Results

    Bool allTestsPassed = TRUE;

    if (newPlayerHandCount != (handCount + 2))
    {
        allTestsPassed = FALSE;

        printf("FAIL: expected new hand count to be %d but it was %d.\n",
            (handCount + 2), newPlayerHandCount);
    }

    if (newDeckAndDiscardCount != ((deckCount + discardCount) - 2))
    {
        allTestsPassed = FALSE;

        printf("FAIL: expected deck and discard count to be %d, but it was %d.\n",
            ((deckCount + discardCount) - 2), newDeckAndDiscardCount);
    }

    if (allTestsPassed)
    {
        printf("PASS: all tests for Smithy() passed.\n");
    }
}