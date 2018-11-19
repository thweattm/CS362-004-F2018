/*
Mike Thweatt
10/14/18
CS362
Dominion - Unit Test 4
'isGameOver' function
*/

#include "dominion.h"
#include <stdio.h>
#include <string.h>



int main(){
	//Initiate game
	struct gameState currentState;
	int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
		   salvager, sea_hag, treasure_map};
	
	//2 = number of players
	//10 = random generator seed
	initializeGame(2, k, 10, &currentState);
	
	/*Starting numbers for my reference:
		0: supplyCount[curse] = 10
		1: supplyCount[estate] = 8
		2: supplyCount[duchy] = 8
		3: supplyCount[province] = 8
		4: supplyCount[copper] = 46
		5: supplyCount[silver] = 40
		6: supplyCount[gold] = 30
		-- Kingdom Cards -- 
		7-26: (Great Hall & Gardens get 8, rest gets 10)
		-- 27 total possible supply piles --
	*/
	
	// -- Test 1: Game is not over if province > 0
	if(isGameOver(&currentState)){
		printf("Test 1 failure: Game is reported as over when it is not\n");
	} else {
		printf("Test 1 success: Game is not over upon initialization\n");
	}
	
	// -- Test 2: Game over if province stack == 0
	currentState.supplyCount[province] = 0;
	if(isGameOver(&currentState)){
		printf("Test 2 success: Game over because province == 0\n");
	} else {
		printf("Test 2 failure: Game not over even though province == 0\n");
	}
	
	
	//Put province stack back to something to avoid game end
	currentState.supplyCount[province] = 8;
	
	
	// -- Test 3: Game is not over if only 2 supply piles = 0
	currentState.supplyCount[adventurer] = 0;
	currentState.supplyCount[gardens] = 0;
	if(isGameOver(&currentState)){
		printf("Test 3 failure: Game reported as over with only 2 supply piles as 0\n");
	} else {
		printf("Test 3 success: Game not reported as over with only 2 supply piles as 0\n");
	}
	
	// -- Test 4: Game over if any 3 supply piles == 0
	// -- Using the first 3 kingdom cards in the supplyCount array
	currentState.supplyCount[embargo] = 0;
	if(isGameOver(&currentState)){
		printf("Test 4 success: Game reported as over with 3 supply piles as 0\n");
	} else {
		printf("Test 4 failure: Game not not reported as over with 3 supply piles as 0\n");
	}
	
	// -- Test 5: Game over if any 3 supply piles == 0
	// -- Using the last 3 kingdom cards in the supplyCount array, knowing they will not get looked at
	currentState.supplyCount[adventurer] = 10;
	currentState.supplyCount[gardens] = 8;
	currentState.supplyCount[embargo] = 10;
	currentState.supplyCount[salvager] = 0;
	currentState.supplyCount[sea_hag] = 0;
	currentState.supplyCount[treasure_map] = 0;
	if(isGameOver(&currentState)){
		printf("Test 5 success: Game reported as over with 3 supply piles as 0\n");
	} else {
		printf("Test 5 failure: Game not reported as over with 3 supply piles as 0\n");
	}
	
	return 0;
}