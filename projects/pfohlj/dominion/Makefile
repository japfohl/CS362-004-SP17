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
	echo "TESTING FILE: dominion.c\n" > tests.out

	echo "TESTS FOR: initializeGame():\n" >> tests.out
	gcc -o unittest1 ../test/functions/unittest1.c dominion.c rngs.c ../test/helpers/test_helpers.c $(CFLAGS)
	./unittest1 >> tests.out
	echo "\nCoverage:\n" >> tests.out
	gcov -b dominion.c >> tests.out

	echo "TESTS FOR: shuffle():\n" >> tests.out
	gcc -o unittest2 ../test/functions/unittest2.c dominion.c rngs.c ../test/helpers/test_helpers.c $(CFLAGS)
	./unittest2 >> tests.out
	echo "\nCoverage:\n" >> tests.out
	gcov -b dominion.c >> tests.out

	echo "TESTS FOR: fullDeckCount():\n" >> tests.out
	gcc -o unittest3 ../test/functions/unittest3.c dominion.c rngs.c ../test/helpers/test_helpers.c $(CFLAGS)
	./unittest3 >> tests.out
	echo "\nCoverage:\n" >> tests.out
	gcov -b dominion.c >> tests.out

	echo "TESTS FOR: isGameOver():\n" >> tests.out
	gcc -o unittest4 ../test/functions/unittest4.c dominion.c rngs.c ../test/helpers/test_helpers.c $(CFLAGS)
	./unittest4 >> tests.out
	echo "\nCoverage:\n" >> tests.out
	gcov -b dominion.c >> tests.out

player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player testDrawCard testBuyCard badTestDrawCard

clean:
	rm -f *.o playdom.exe playdom test.exe test player player.exe testInit testInit.exe *.gcov *.gcda *.gcno *.so *.out testDrawCard unittest*
