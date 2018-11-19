CFLAGS= -Wall -fpic -coverage -lm -std=c99

#game functions
rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)
#To run playdom you need to entere: ./playdom <any integer number> like ./playdom 10*/

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player 

default: all
######


#my random test functions
#adventurer card
randomtestadventurer: dominion.o randomtestadventurer.c rngs.o
	echo ">>>> randomtestadventurer.c (adventurer card) <<<<" > randomtestadventurer.out
	gcc -o randomtestadventurer -g randomtestadventurer.c dominion.o rngs.o $(CFLAGS)
	./randomtestadventurer >> randomtestadventurer.out
	gcov -b dominion.c >> randomtestadventurer.out
	gcov -b -f dominion.c | grep "adventureCardEffect" -B 0 -A 5 >> randomtestadventurer.out

#smithy card
randomtestcard1: dominion.o randomtestcard1.c rngs.o
	echo ">>>> randomtestcard1.c (smithy card) <<<<" > randomtestcard1.out
	gcc -o randomtestcard1 -g randomtestcard1.c dominion.o rngs.o $(CFLAGS)
	./randomtestcard1 >> randomtestcard1.out
	gcov -b dominion.c >> randomtestcard1.out
	gcov -b -f dominion.c | grep "smithyCardEffect" -B 0 -A 5 >> randomtestcard1.out

#village card
randomtestcard2: dominion.o randomtestcard2.c rngs.o
	echo ">>>> randomtestcard2.c (village card) <<<<" > randomtestcard2.out
	gcc -o randomtestcard2 -g randomtestcard2.c dominion.o rngs.o $(CFLAGS)
	./randomtestcard2 >> randomtestcard2.out
	gcov -b dominion.c >> randomtestcard2.out
	gcov -b -f dominion.c | grep "villageEffect" -B 0 -A 4 >> randomtestcard2.out
	
randomtestresults: randomtestadventurer randomtestcard1 randomtestcard2

######
#my unit test functions
#compare function
unittest1: dominion.o unittest1.c rngs.o
	echo ">>>> unittest1.c (compare function) <<<<" > unittestresults.out
	gcc -o unittest1 -g unittest1.c dominion.o rngs.o $(CFLAGS)
	./unittest1 >> unittestresults.out
	gcov -b dominion.c >> unittestresults.out
	gcov -b -f dominion.c | grep "compare" -B 0 -A 5 >> unittestresults.out

#shuffle function
unittest2: dominion.o unittest2.c rngs.o
	echo ">>>> unittest2.c (shuffle function) <<<<" >> unittestresults.out
	gcc -o unittest2 -g unittest2.c dominion.o rngs.o $(CFLAGS)
	./unittest2 >> unittestresults.out
	gcov -b dominion.c >> unittestresults.out
	gcov -b -f dominion.c | grep "shuffle" -B 0 -A 5 >> unittestresults.out

#scoreFor function
unittest3: dominion.o unittest3.c rngs.o
	echo ">>>> unittest3.c (scoreFor function) <<<<" >> unittestresults.out
	gcc -o unittest3 -g unittest3.c dominion.o rngs.o $(CFLAGS)
	./unittest3 >> unittestresults.out
	gcov -b dominion.c >> unittestresults.out
	gcov -b -f dominion.c | grep "scoreFor" -B 0 -A 5 >> unittestresults.out
	
#isGameOver function
unittest4: dominion.o unittest4.c rngs.o
	echo ">>>> unittest4.c (isGameOver function) <<<<" >> unittestresults.out
	gcc -o unittest4 -g unittest4.c dominion.o rngs.o $(CFLAGS)
	./unittest4 >> unittestresults.out
	gcov -b dominion.c >> unittestresults.out
	gcov -b -f dominion.c | grep "isGameOver" -B 0 -A 5 >> unittestresults.out

#smithy card
cardtest1: dominion.o cardtest1.c rngs.o
	echo ">>>> cardtest1.c (smithy card) <<<<" >> unittestresults.out
	gcc -o cardtest1 -g cardtest1.c dominion.o rngs.o $(CFLAGS)
	./cardtest1 >> unittestresults.out
	gcov -b dominion.c >> unittestresults.out
	gcov -b -f dominion.c | grep "smithyCardEffect" -B 0 -A 5 >> unittestresults.out

#adventurer card
cardtest2: dominion.o cardtest2.c rngs.o
	echo ">>>> cardtest2.c (adventurer card) <<<<" >> unittestresults.out
	gcc -o cardtest2 -g cardtest2.c dominion.o rngs.o $(CFLAGS)
	./cardtest2 >> unittestresults.out
	gcov -b dominion.c >> unittestresults.out
	gcov -b -f dominion.c | grep "adventureCardEffect" -B 0 -A 5 >> unittestresults.out

#village card
cardtest3: dominion.o cardtest3.c rngs.o
	echo ">>>> cardtest3.c (village card) <<<<" >> unittestresults.out
	gcc -o cardtest3 -g cardtest3.c dominion.o rngs.o $(CFLAGS)
	./cardtest3 >> unittestresults.out
	gcov -b dominion.c >> unittestresults.out
	gcov -b -f dominion.c | grep "villageEffect" -B 0 -A 4 >> unittestresults.out

#cutpurse (not a separately implemented function in this version)
cardtest4: dominion.o cardtest4.c rngs.o
	echo ">>>> cardtest4.c (cutpurse card) <<<<" >> unittestresults.out
	gcc -o cardtest4 -g cardtest4.c dominion.o rngs.o $(CFLAGS)
	./cardtest4 >> unittestresults.out
	gcov -b dominion.c >> unittestresults.out
	
unittestresults: unittest1 unittest2 unittest3 unittest4 cardtest1 cardtest2 cardtest3 cardtest4
######



	
#previously written test functions	
testDrawCard: testDrawCard.c dominion.o rngs.o
	gcc  -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

badTestDrawCard: badTestDrawCard.c dominion.o rngs.o
	gcc -o badTestDrawCard -g  badTestDrawCard.c dominion.o rngs.o $(CFLAGS)

testBuyCard: testDrawCard.c dominion.o rngs.o
	gcc -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

testAll: dominion.o testSuite.c
	gcc -o testSuite testSuite.c -g  dominion.o rngs.o $(CFLAGS)

runtests: testDrawCard 
	./testDrawCard &> unittestresult.out
	gcov dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out
######


clean:
	rm -f *.o *.exe  *.gcov *.gcda *.gcno *.so \
	playdom player testDrawCard \
	cardtest1 cardtest2 cardtest3 cardtest4 \
	unittest1 unittest2 unittest3 unittest4 \
	randomtestcard1 randomtestcard2 randomtestadventurer
