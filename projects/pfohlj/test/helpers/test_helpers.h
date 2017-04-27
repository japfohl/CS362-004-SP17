#ifndef TEST_HELPERS_H
#define TEST_HELPERS_H

// typedefs
typedef int (*COMP_PTR)(void *val1, void *val2);
typedef struct gameState GameState;

// generic assertion functions
int AssertEqual(void *val1, void *val2, COMP_PTR comparator);
int AssertNotEqual(void *val1, void *val2, COMP_PTR comparator);
int AssertGreaterThan(void *val1, void *val2, COMP_PTR comparator);
int AssertLessThan(void *val1, void *val2, COMP_PTR comparator);

// comparator functions
int CompareGameState(void *val1, void *val2);
int CompareInt(void *val1, void *val2);

#endif