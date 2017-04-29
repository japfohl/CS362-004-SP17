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

enum KingdomType
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
};

enum DeckType
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
};

// TYPEDEFS

typedef struct gameState GameState;
typedef enum KingdomType KingdomType;
typedef enum DeckType DeckType;
typedef int (*COMP_PTR)(void *val1, void *val2);
typedef int (*ARR_COMP)(void *arr1, int size1, void *arr2, int size2);
typedef int* Cards;
typedef int Bool;
typedef int Card;
typedef int Player;

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

Cards CreateKingdom(KingdomType type);
Cards Reset(Cards cards, KingdomType type, GameState *state, GameState *blank);
Cards CreateDeck(DeckType deck);
int DeckAndDiscardCount(Card card, Player player, GameState *game);
int HandCount(Card card, Player player, GameState *game);

#endif