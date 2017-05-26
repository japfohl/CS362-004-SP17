#include "dominion.h"
#include "unitTestUtilities.h"
#include "randomTest.h"
#include <stdio.h>

int main(int argc, char const *argv[])
{
	if (argc > 2) {
		unsigned long count = (unsigned long)atoi(argv[2]);
		
		switch (atoi(argv[1])) {
			case 1:
				printf("Testing ADVENTURER\n");
				randomTestAdventurer(count);
				break;
			case 2:
				printf("Testing SMITHY\n");
				randomTestSmithy(count);
				break;
			case 3:
				printf("Testing VILLAGE\n");
				randomTestVillage(count);
			default:
				break;
		}

		printf("\n");
		printf("\n");
	}

	return 0;
}