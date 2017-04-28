#ifndef TEST_HELPERS_H
#define TEST_HELPERS_H

#include <stddef.h>

// DEFINES

#define FALSE 0
#define TRUE 1

// ENUMS

enum KingdomType
{
    GoodNoVictory = 0,
    GoodWithVictory,
    BadDuplicate,
    BadNotEnough,
    BadTooMany,
    BadWithInvalidSupplyCard
};

// TYPEDEFS

typedef int (*COMP_PTR)(void *val1, void *val2);
typedef int (*ARR_COMP)(void *arr1, int size1, void *arr2, int size2);
typedef struct gameState GameState;
typedef enum KingdomType KingdomType;
typedef int* Cards;
typedef int Bool;

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

#endif