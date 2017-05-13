CFLAGS = -Wall -fpic -coverage -lm

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)

testDrawCard: testDrawCard.c dominion.o rngs.o
	gcc -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

badTestDrawCard: badTestDrawCard.c dominion.o rngs.o
	gcc -o badTestDrawCard -g  badTestDrawCard.c dominion.o rngs.o $(CFLAGS)

testBuyCard: testDrawCard.c dominion.o rngs.o
	gcc -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

testAll: dominion.o testSuite.c
	gcc -o testSuite testSuite.c -g  dominion.o rngs.o $(CFLAGS)

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

runtests: testDrawCard 
	./testDrawCard &> unittestresult.out
	gcov dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out

unittestresult.out: ../test/functions/unittest1.c dominion.c rngs.c ../test/helpers/test_helpers.c
	echo "TESTING FILE: dominion.c\n" > unittestresults.out

	echo "TESTS FOR: initializeGame():\n" >> unittestresults.out
	gcc -o unittest1 ../test/functions/unittest1.c dominion.c rngs.c ../test/helpers/test_helpers.c $(CFLAGS)
	./unittest1 >> unittestresults.out
	echo "\nCoverage:\n" >> unittestresults.out
	gcov -b dominion.c >> unittestresults.out

	echo "TESTS FOR: shuffle():\n" >> unittestresults.out
	gcc -o unittest2 ../test/functions/unittest2.c dominion.c rngs.c ../test/helpers/test_helpers.c $(CFLAGS)
	./unittest2 >> unittestresults.out
	echo "\nCoverage:\n" >> unittestresults.out
	gcov -b dominion.c >> unittestresults.out

	echo "TESTS FOR: fullDeckCount():\n" >> unittestresults.out
	gcc -o unittest3 ../test/functions/unittest3.c dominion.c rngs.c ../test/helpers/test_helpers.c $(CFLAGS)
	./unittest3 >> unittestresults.out
	echo "\nCoverage:\n" >> unittestresults.out
	gcov -b dominion.c >> unittestresults.out

	echo "TESTS FOR: isGameOver():\n" >> unittestresults.out
	gcc -o unittest4 ../test/functions/unittest4.c dominion.c rngs.c ../test/helpers/test_helpers.c $(CFLAGS)
	./unittest4 >> unittestresults.out
	echo "\nCoverage:\n" >> unittestresults.out
	gcov -b dominion.c >> unittestresults.out

	echo "TESTS FOR: Adventurer():\n" >> unittestresults.out
	echo "Tests currently un-runnable due to infinite loop bug introduced in assignment 2" >> unittestresults.out
	echo "I tested this after fixing the bug and the tests were runnable but am leaving the bug per the requirements." >>  unittestresults.out
	echo "Un-comment tests once infinite loop found and fixed\n" >> unittestresults.out
	# gcc -o cardtest1 ../test/cards/cardtest1.c dominion.c rngs.c ../test/helpers/test_helpers.c $(CFLAGS)
	# ./cardtest1 >> unittestresults.out
	# echo "\nCoverage:\n" >> unittestresults.out
	# gcov -b dominion.c >> unittestresults.out

	echo "TESTS FOR: Smithy():\n" >> unittestresults.out
	gcc -o cardtest2 ../test/cards/cardtest2.c dominion.c rngs.c ../test/helpers/test_helpers.c $(CFLAGS)
	./cardtest2 >> unittestresults.out
	echo "\nCoverage:\n" >> unittestresults.out
	gcov -b dominion.c >> unittestresults.out

	echo "TESTS FOR: CouncilRoom():\n" >> unittestresults.out
	gcc -o cardtest3 ../test/cards/cardtest3.c dominion.c rngs.c ../test/helpers/test_helpers.c $(CFLAGS)
	./cardtest3 >> unittestresults.out
	echo "\nCoverage:\n" >> unittestresults.out
	gcov -b dominion.c >> unittestresults.out

	echo "TESTS FOR: Feast():\n" >> unittestresults.out
	gcc -o cardtest4 ../test/cards/cardtest4.c dominion.c rngs.c ../test/helpers/test_helpers.c $(CFLAGS)
	./cardtest4 >> unittestresults.out
	echo "\nCoverage:\n" >> unittestresults.out
	gcov -b dominion.c >> unittestresults.out

randomtestcard1.out:
	echo "TESTING Smithy() implementation in dominion.c\n" > randomtestcard1.out
	gcc -o randomtestcard1 ../test/random-tests/randomtestcard1.c dominion.c rngs.c ../test/helpers/test_helpers.c $(CFLAGS)
	./randomtestcard1 >> randomtestcard1.out
	echo "\nCoverage:\n" >> randomtestcard1.out
	gcov -b dominion.c >> randomtestcard1.out

randomtestcard2.out:
	echo "TESTING CouncilRoom() implementation in dominion.c\n" > randomtestcard2.out
	gcc -o randomtestcard2 ../test/random-tests/randomtestcard2.c dominion.c rngs.c ../test/helpers/test_helpers.c $(CFLAGS)
	./randomtestcard2 >> randomtestcard2.out
	echo "\nCoverage:\n" >> randomtestcard2.out
	gcov -b dominion.c >> randomtestcard2.out

randomtestadventurer.out:
	echo "TESTING Adventurer() implementation in dominion.c\n" > randomtestadventurer.out
	gcc -o randomtestadventurer ../test/random-tests/randomtestadventurer.c dominion.c rngs.c ../test/helpers/test_helpers.c $(CFLAGS)
	./randomtestadventurer >> randomtestadventurer.out
	echo "\nCoverage:\n" >> randomtestadventurer.out
	gcov -b dominion.c >> randomtestadventurer.out

player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player testDrawCard testBuyCard badTestDrawCard

clean:
	rm -f *.o playdom.exe playdom test.exe test player player.exe testInit testInit.exe *.gcov *.gcda *.gcno *.so *.out testDrawCard unittest* cardtest* badTestDrawCard
