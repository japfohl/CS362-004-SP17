/*****************************************************************************************
*        NAME:  Joseph A Pfohl
*        DATE:  5/12/2016
*       CLASS:  CS362-400 Software Engineering II
*  ASSIGNMENT:  Assignment #4 - Random Testing
* DESCRIPTION:  Random tests for Council Room card implementation
*****************************************************************************************/

#include "../../dominion/dominion.h"
#include "../../dominion/dominion_helpers.h"
#include "../../dominion/rngs.h"
#include "../helpers/test_helpers.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

void RandomTestCouncilRoom();

int main()
{
    int i;

    SelectStream(0);
    PutSeed(42);

    for (i = 0; i < 2000; i++)
    {
        RandomTestCouncilRoom();
    }

    return 0;
}

void RandomTestCouncilRoom()
{
    // 1. create our randomly generated game state
    GameState state;

    int i;

    for (i = 0; i < sizeof(GameState); i++)
    {
        ((char*)&state)[i] = floor(Random() * 256);
    }

    /*      
    **  CouncilRoom requires:
    **      - numPlayers
    **      - whoseTurn
    **      - deckCount     (for each player)
    **      - deck          (for each player)
    **      - discardCount  (for each player)
    **      - discard       (for each player)
    **      - handCount     (for each player)
    **      - hand          (for each player)
    **      - numBuys
    **      - playedCardsCount
    **      - playedCards[0:playedCardsCount]
    */

    // 2. pick a number of players (2-4)

    int numPlayers = (int)floor(Random() * 3) + 2;
    state.numPlayers = numPlayers;

    // 3. pick the active player (whoseTurn)

    int player = (int)floor(Random() * numPlayers);
    state.whoseTurn = player;

    // 4. set up each player's deck

    int totalCardCount[numPlayers];
    int handCount[numPlayers];
    int deckCount[numPlayers];
    int discardCount[numPlayers];
    Card decks[numPlayers][MAX_DECK];
    int councilRoomPosition[numPlayers];

    int currentPlayer;

    for (currentPlayer = 0; currentPlayer < numPlayers; currentPlayer++)
    {
        // 4.a get total card count for the current player (50 - 500)
        totalCardCount[currentPlayer] = (int)floor(Random() * 451) + 50;

        // 4.b divide total card count between the hand, discard, and deck

        // hand
        handCount[currentPlayer] = (int)floor(Random() * 11) + 5;
        state.handCount[currentPlayer] = handCount[currentPlayer];

        // discard
        discardCount[currentPlayer] = (int)floor(Random() * (totalCardCount - handCount + 1));
        state.discardCount[currentPlayer] = discardCount[currentPlayer];
        
        // deck gets remainder
        deckCount[currentPlayer]
        = totalCardCount[currentPlayer] - handCount[currentPlayer] - discardCount[currentPlayer];
        state.deckCount[currentPlayer] = deckCount[currentPlayer];

        // 4.c create random sets of cards

        // assign a random card from all possible cards to each spot in deck
        for (i = 0; i < totalCardCount[currentPlayer]; i++)
        {
            decks[currentPlayer][i] = (int)floor(Random() * treasure_map + 1);
        }

        // 4.d divvy up the random deck between hand / deck / discard
        int currentCard = 0;

        // hand
        for (i = 0; i < handCount[currentPlayer]; i++)
        {
            state.hand[currentPlayer][i] = decks[currentPlayer][currentCard];
            currentCard++;
        }

        //discard
        for (i = 0; i < discardCount[currentPlayer]; i++)
        {
            state.discard[currentPlayer][i] = decks[currentPlayer][currentCard];
            currentCard++;
        }

        // deck
        for (i = 0; i < deckCount[currentPlayer]; i++)
        {
            state.deck[currentPlayer][i] = decks[currentPlayer][currentCard];
            currentCard++;
        }

        // 4.e make sure one of the cards in hand is Council Room
        councilRoomPosition[currentPlayer] = (int)floor(Random() * handCount[currentPlayer]);
        state.hand[currentPlayer][councilRoomPosition[currentPlayer]] = council_room;
    }

    // 5. Set the number of buys (1 - 5);

    int numBuys = (int)floor(Random() * 5) + 1;
    state.numBuys = numBuys;

    // 6. Set the number of played cards (0 - 10)

    int numPlayedCards = (int)floor(Random() * 11);
    state.playedCardCount = numPlayedCards;

    // 7. Fill Played cards with random cards from all possible cards

    for (i = 0; i < numPlayedCards; i++)
    {
        state.playedCards[i] = (int)floor(Random() * treasure_map + 1);
    }

    /*
    **  Following Council Room, the following should be true:
    **      - Active player's hand count +3
    **      - Active player's deck and discard count (sum) -3
    **      - Active player's number of buys +1
    **      - Other player's hand count +1
    **      - Other player's deck and discard count (sum) -1
    */

    // 8. Play Council Room

   CouncilRoom(&state, councilRoomPosition[currentPlayer]);

    // 9. Get new results for validation

    int newNumBuys = state.numBuys;

    int newHandCount[numPlayers];
    int newDeckCount[numPlayers];
    int newDiscardCount[numPlayers];

    for (i = 0; i < numPlayers; i++)
    {
        newHandCount[i] = state.handCount[i];
        newDeckCount[i] = state.deckCount[i];
        newDiscardCount[i] = state.discardCount[i];
    }

    // 9. Validate Results

    Bool allTestsPassed = TRUE;

    // verify active player got +1 buy
    if (newNumBuys != (numBuys +1))
    {
        allTestsPassed = FALSE;

        printf("FAIL: ");
    }

    for (i = 0; i < numPlayers; i++)
    {
        if (i == player)
        {
            // verify active player netted +3 cards
            if (newHandCount[i] != (handCount[i] + 3))
            {
                allTestsPassed = FALSE;

                printf("FAIL: expected ACTIVE PLAYER new hand count to be %d but it was %d.\n",
                    (handCount[i] + 3), newHandCount[i]);
            }

            // verify active player discard + deck -3
            if ((newDeckCount[i] + newDiscardCount[i]) != (deckCount[i] + discardCount[i] - 4))
            {
                allTestsPassed = FALSE;

                printf("FAIL: expected ACTIVE PLAYER new deck and discard count to be %d but it was %d.\n",
                    (deckCount[i] + discardCount[i] - 3), (newDeckCount[i] + newDiscardCount[i]));
            }
        }
        else
        {
            // verify other player netted +1 cards
            if (newHandCount[i] != (handCount[i] + 1))
            {
                allTestsPassed = FALSE;

                printf("FAIL: expected player %d new hand count to be %d but it was %d.\n",
                    (i+1), (handCount[i] + 1), newHandCount[i]);
            }

            // verify other player discard + deck -1
            if ((newDeckCount[i] + newDiscardCount[i]) != (deckCount[i] + discardCount[i] - 1))
            {
                allTestsPassed = FALSE;

                printf("FAIL: expected player %d new deck and discard count to be %d but it was %d.\n",
                    (i+1), (deckCount[i] + discardCount[i] - 1), (newDeckCount[i] + newDiscardCount[i]));
            }
        }
    }

    if (allTestsPassed)
    {
        printf("PASS: All tests passed!\n");
    }
}