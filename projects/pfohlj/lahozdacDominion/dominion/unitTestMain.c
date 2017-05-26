#include "dominion.h"
#include "unitTest.h"
#include "unitTestUtilities.h"
#include <stdio.h>

int main() {
	struct gameState* state = newGame();

	int* kingdom_cards = kingdomCards(village,smithy,mine,great_hall,adventurer,sea_hag,treasure_map,embargo,council_room,salvager);

	initializeGame(2,kingdom_cards,15,state);

	//Save snapshot of gameState
	struct gameState snapshot = *state;

	printf("***************************************\n");
	printf("TESTING buyCard()\n");
	printf("\n");
	testBuyCard(state);
	*state = snapshot;


	printf("***************************************\n");
	printf("TESTING isGameOver()\n");
	printf("\n");
	testIsGameOver(state);
	*state = snapshot;
	printf("\n");

	printf("***************************************\n");
	printf("TESTING fullDeckCount()\n");
	printf("\n");
	testFullDeckCount(state);
	*state = snapshot;
	printf("\n");

	printf("***************************************\n");
	printf("TESTING numHandCards()\n");
	printf("\n");
	testNumHandCards(state);
	*state = snapshot;
	printf("\n");

	printf("***************************************\n");
	printf("TESTING SMITHY\n");
	printf("\n");
	testSmithy(state);
	*state = snapshot;
	printf("\n");

	printf("***************************************\n");
	printf("TESTING ADVENTURER\n");
	printf("\n");
	testAdventurer(state);
	*state = snapshot;
	printf("\n");

	printf("***************************************\n");
	printf("TESTING VILLAGE\n");
	printf("\n");
	testVillage(state);
	*state = snapshot;
	printf("\n");

	printf("***************************************\n");
	printf("TESTING COUNCIL ROOM\n");
	printf("\n");
	testCouncilRoom(state);
	printf("\n");

	printf("***************************************\n");
	printf("\n");

	return 0;
}