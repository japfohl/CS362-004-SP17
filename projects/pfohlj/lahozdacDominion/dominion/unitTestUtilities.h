#ifndef UNITTESTUTILS_H
#define UNITTESTUTILS_H

#include "dominion.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LENGTH 500
#define MAX_ERR 100

struct test {
	int err;
	int errCount;
	int testNo;
	struct gameState* preCond;
	struct gameState* postCond;
	char status[MAX_ERR][MAX_LENGTH];
};

int cmpGameState (struct gameState* gs1, struct gameState* gs2);
void printTest(struct test* t);
void addError(struct test* t, const char* s);
void printErr(struct test* t);
void randomizeGameState (struct gameState* state, int seed);
int getCardDeckCount (int player, int card, struct gameState* state);
int getCardHandCount (int player, int card, struct gameState* state);
int getCardDiscardCount (int player, int card, struct gameState* state);
int getCardPlayedCount (int card, struct gameState* state);

#endif