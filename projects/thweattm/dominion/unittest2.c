/*
Mike Thweatt
10/14/18
CS362
Dominion - Unit Test 2
'shuffle' function
*/

#include "dominion.h"
#include <stdio.h>
#include <string.h>

int main(){
	//Gather initial data
	//Note: 'shuffle' function only shuffles cards in the deck, not cards in hand
	//When it's 'your turn' you have 5 cards in hand with remainder in deck
	//Game start, upon initialization, player will have 5 in hand, 5 in deck
	struct gameState currentState, originalState;
	int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
		   sea_hag, tribute, smithy};
	
	//2 = number of players
	//10 = random generator seed
	initializeGame(2, k, 10, &currentState);
	
	/*
	printf("number of cards in deck for player 1 = %d\n", currentState.deckCount[0]);
	printf("number of cards in hand for player 1 = %d\n", currentState.handCount[0]);
	printf("number of cards in deck for player 2 = %d\n", currentState.deckCount[1]);
	printf("number of cards in hand for player 2 = %d\n", currentState.handCount[1]);
	*/
	
	//Copy original gameState for comparison after shuffle
	memcpy(&originalState, &currentState, sizeof(struct gameState));
	
	//Shuffle deck
	shuffle(0, &currentState);
	
	//int originalDeck[MAX_DECK];
	//state->deck[player][i] = newDeck[i];
	//int deckCount[MAX_PLAYERS];
	
	// -- Test 1: number of cards is same before and after shuffle for player 0
	if (currentState.deckCount[0] == originalState.deckCount[0]){
		printf("Test 1 success: deckCount matches for player 1\n"); 
	} else {
		printf("Test 1 failure: deckCount does not match for player 1\n");
	}
	
	// -- Test 2: deck order is different before and after shuffle for player 0
	int different = 0;
	int i = 0;
	while (different == 0 && i < originalState.deckCount[0]){
		if (originalState.deck[0][i] != currentState.deck[0][i])
			different = 1;
		i++;
	}
	if (different == 0){
		printf("Test 2 failure: deck sort & order remains unchanged for player 1\n");
	} else {
		printf("Test 2 success: deck sort & order is different for player 1\n");
	}
	
	// -- Test 3: number of cards is same for player 2
	if (currentState.deckCount[1] == originalState.deckCount[1]){
		printf("Test 3 success: deckCount matches for player 2\n"); 
	} else {
		printf("Test 3 failure: deckCount does not match for player 2\n");
	}
	
	// -- Test 4: deck order is same for player 2
	different = 0;
	i = 0;
	while (different == 0 && i < originalState.deckCount[1]){
		if (originalState.deck[1][i] != currentState.deck[1][i])
			different = 1;
		i++;
	}
	if (different == 0){
		printf("Test 4 success: deck sort & order remains unchanged for player 2\n");
	} else {
		printf("Test 4 failure: deck sort & order is different for player 2\n");
	}
	
	return 0;
}