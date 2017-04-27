#include "test_helpers.h"
#include "../../dominion/dominion.h"
#include <string.h>

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