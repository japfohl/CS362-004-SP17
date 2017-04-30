/*****************************************************************************************
* NAME: Joseph A Pfohl
* DATE: 4/30/2017
* ASSIGNMENT: Assignment #3
* DESCRIPTION: Helper functions for writing unit tests.
*****************************************************************************************/

#include "test_helpers.h"
#include "../../dominion/dominion.h"
#include <string.h>
#include <stdlib.h>

// CUSTOM ASSERT FUNCTIONS

int AssertEqual(void *val1, void *val2, COMP_PTR comparator)
{
    if (comparator(val1, val2) == 0)
    {
        return 1;
    }
    return 0;
}

int AssertNotEqual(void *val1, void *val2, COMP_PTR comparator)
{
    if (comparator(val1, val2) != 0)
    {
        return 1;
    }
    return 0;
}

int AssertArraysNotEqual(void *arr1, size_t size1, void *arr2, size_t size2)
{
    if (size1 != size2)
    {
        return TRUE;
    }
    else
    {
        return memcmp(arr1, arr2, size1) != 0;
    }
}

int AssertGreaterThan(void *val1, void *val2, COMP_PTR comparator)
{
    if (comparator(val1, val2) > 0)
    {
        return 1;
    }
    return 0;
}

int AssertLessThan(void *val1, void *val2, COMP_PTR comparator)
{
    if (comparator(val1, val2) < 0)
    {
        return 1;
    }
    return 0;
}

int AssertTrue(Bool expression)
{
    return expression == TRUE;
}

int AssertFalse(Bool expression)
{
    return expression == FALSE;
}

// COMPARATORS

int CompareGameState(void *val1, void *val2)
{
    GameState *state1 = (GameState *)val1;
    GameState *state2 = (GameState *)val2;

    return memcmp(state1, state2, sizeof(GameState));
}

int CompareInt(void *val1, void *val2)
{
    int *int1 = (int *)val1;
    int *int2 = (int *)val2;

    if (*int1 < *int2)
    {
        return -1;
    }
    else if (*int1 == *int2)
    {
        return 0;
    }

    return 1;
}

// HELPER FUNCTIONS

Cards CreateKingdom(KingdomType type)
{
    int *cards, i;
    int tempCards[12] = {adventurer, council_room, feast, mine, gardens, remodel,
                         smithy, baron, mine, village, great_hall, minion};

    switch (type)
    {
    case GoodNoVictory:

        return kingdomCards(adventurer, council_room, feast, mine, remodel,
                            smithy, village, baron, minion, steward);

    case GoodNoSmithy:

        return kingdomCards(adventurer, council_room, feast, mine, remodel,
                            gardens, village, baron, minion, steward);

    case GoodNoCouncilRoom:

        return kingdomCards(adventurer, smithy, feast, mine, remodel,
                            gardens, village, baron, minion, steward);

    case GoodWithVictory:

        return kingdomCards(adventurer, council_room, great_hall, mine, remodel,
                            smithy, village, baron, minion, gardens);

    case BadDuplicate:

        return kingdomCards(adventurer, adventurer, great_hall, mine, remodel,
                            smithy, village, baron, gardens, gardens);

    case BadNotEnough:

        cards = malloc(8 * sizeof(int));
        for (i = 0; i < 8; i++)
        {
            cards[i] = tempCards[i];
        }
        return cards;

    case BadTooMany:

        cards = malloc(12 * sizeof(int));
        for (i = 0; i < 12; i++)
        {
            cards[i] = tempCards[i];
        }
        return cards;

    case BadWithInvalidSupplyCard:

        return kingdomCards(estate, copper, curse, silver, gold,
                            smithy, duchy, baron, province, steward);

    case CountKingdom:

        return kingdomCards(copper, copper, copper, copper, copper,
                            smithy, duchy, baron, adventurer, village);

    default:
        return CreateKingdom(GoodNoVictory);
    }
}

Cards Reset(Cards cards, KingdomType type, GameState *state, GameState *blank)
{
    if (cards != NULL)
    {
        free(cards);
        cards = NULL;
    }

    memcpy(state, blank, sizeof(GameState));

    return CreateKingdom(type);
}

Cards CreateDeck(DeckType deck)
{   
    int i;
    Cards tempDeck;
    Cards tempCards;
    
    if (deck == SmallCountDeck
        || deck == MediumCountDeck
        || deck == LargeCountDeck
        || deck == WithTreasures)
    {
        tempCards = CreateKingdom(CountKingdom);
    }
    else if (deck == LargeNoSmithy)
    {
        tempCards = CreateKingdom(GoodNoSmithy);
    }
    else if (deck == LargeNoCouncilRoom)
    {
        tempCards = CreateKingdom(GoodNoCouncilRoom);
    }
    else
    {
        tempCards = CreateKingdom(GoodNoVictory);
    }

    switch (deck)
    {
    case StartingDeck:

        tempDeck = malloc(10 * sizeof(Card));

        for (i = 0; i < 3; i++)
        {
            tempDeck[i] = estate;
        }
        for (i = 3; i < 10; i++)
        {
            tempDeck[i] = copper;
        }

        free(tempCards);
        return tempDeck;

    case SmallDeck:
    case SmallCountDeck:

        tempDeck = malloc(20 * sizeof(Card));

        for (i = 0; i < 10; i++)
        {
            tempDeck[i] = tempCards[i];
            tempDeck[i+10] = tempCards[i];
        }

        free(tempCards);
        return tempDeck;

    case MediumDeck:
    case MediumCountDeck:    

        tempDeck = malloc(30 * sizeof(Card));

        for (i = 0; i < 10; i++)
        {
            tempDeck[i] = tempCards[i];
            tempDeck[i+10] = tempCards[i];
            tempDeck[i+20] = tempCards[i];
        }

        free(tempCards);
        return tempDeck;

    case LargeDeck:
    case LargeNoSmithy:
    case LargeNoCouncilRoom:
    case LargeCountDeck:
    case WithTreasures:
    case WithoutTreasures:

        tempDeck = malloc(40 * sizeof(Card));

        for (i = 0; i < 10; i++)
        {
            tempDeck[i] = tempCards[i];
            tempDeck[i+10] = tempCards[i];
            tempDeck[i+20] = tempCards[i];
            tempDeck[i+30] = tempCards[i];
        }

        free(tempCards);
        return tempDeck;

    default:

        free(tempCards);
        return CreateDeck(StartingDeck);
    }
}

int DeckAndDiscardCount(Card card, Player player, GameState *game)
{
    // variable declarations
    int i, count = 0;

    // find the deck count for card
    for (i = 0; i < game->deckCount[player]; i++)
    {
        if (game->deck[player][i] == card)
        {
            count++;
        }
    }

    // find the discard count for the card
    for (i = 0; i < game->discardCount[player]; i++)
    {
        if (game->discard[player][i] == card)
        {
            count++;
        }
    }

    return count;
}

int HandCount(Card card, Player player, GameState *game)
{
    // variables
    int i, count = 0;

    // find the hand count
    for (i = 0; i < game->handCount[player]; i++)
    {
        if (game->hand[player][i] == card)
        {
            count++;
        }
    }

    return count;
}