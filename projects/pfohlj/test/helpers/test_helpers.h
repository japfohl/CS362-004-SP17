/*****************************************************************************************
* NAME: Joseph A Pfohl
* DATE: 4/30/2017
* ASSIGNMENT: Assignment #3
* DESCRIPTION: Header file for helper functions.  Includes important typedefs and defines.
*****************************************************************************************/

#ifndef TEST_HELPERS_H
#define TEST_HELPERS_H

#include <stddef.h>

// DEFINES

#define FALSE 0
#define TRUE 1

#define START_HAND_SIZE (5 * sizeof(Card))
#define SMALL_DECK_SIZE (20 * sizeof(Card))
#define MEDIUM_DECK_SIZE (30 * sizeof(Card))
#define LARGE_DECK_SIZE (40 * sizeof(Card))

#define SMALL 20
#define MEDIUM 30
#define LARGE 40

// ENUMS

typedef enum KingdomType
{
    GoodNoVictory = 0,
    GoodNoSmithy,
    GoodNoCouncilRoom,
    GoodWithVictory,
    BadDuplicate,
    BadNotEnough,
    BadTooMany,
    BadWithInvalidSupplyCard,
    CountKingdom
} KingdomType;

typedef enum DeckType
{
    StartingDeck = 0,
    SmallDeck,
    SmallCountDeck,
    MediumDeck,
    MediumCountDeck,
    LargeDeck,
    LargeNoSmithy,
    LargeNoCouncilRoom,
    LargeCountDeck,
    WithTreasures,
    WithoutTreasures
} DeckType;

typedef enum CardLocation
{
    Hand = 0,
    Deck,
    Discard,
    Supply,
    Trash
} CardLocation;

// TYPEDEFS

/* Comparator function typedefs */
typedef int (*COMP_PTR)(void *val1, void *val2);
typedef int (*ARR_COMP)(void *arr1, int size1, void *arr2, int size2);

/* Convenience typedefs */
typedef struct gameState GameState;
typedef int* Cards;
typedef int Bool;
typedef int Card;
typedef int Player;

// STRUCTS

typedef struct TestResults
{
    Bool wereSuccessful;    // can be TRUE or FALSE indicating successful / unsuccessful test
    char* message;          // NULL if wereSuccessful = TRUE, failure message if FALSE
} TestResults;

// GENERIC ASSERTION FUNCTIONS

int AssertEqual(void *val1, void *val2, COMP_PTR comparator);
int AssertNotEqual(void *val1, void *val2, COMP_PTR comparator);
int AssertArraysNotEqual(void *arr1, size_t size1, void *arr2, size_t size2);
int AssertGreaterThan(void *val1, void *val2, COMP_PTR comparator);
int AssertLessThan(void *val1, void *val2, COMP_PTR comparator);
int AssertTrue(Bool expression);
int AssertFalse(Bool expression);

// COMPARATOR FUNCTIONS

int CompareGameState(void *val1, void *val2);
int CompareInt(void *val1, void *val2);

// HELPER FUNCTIONS

GameState *CreateRandomGameState();
Cards CreateKingdom(KingdomType type);
Cards CreateDeck(DeckType deck);
Cards Reset(Cards cards, KingdomType type, GameState *state, GameState *blank);
int DeckAndDiscardCount(Card card, Player player, GameState *game);
int HandCount(Card card, Player player, GameState *game);
int TreasureCount(CardLocation location, GameState *state, Player p);
Bool IsTreasure(Card card);

#endif