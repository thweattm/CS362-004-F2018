/*
Mike Thweatt
10/14/18
CS362
Dominion - Unit Test 3
'scoreFor' function
*/

#include "dominion.h"
#include <stdio.h>
#include <string.h>

void printCards(int player, struct gameState *state){
	//Print out all cards for verification
	int i;
	printf("Cards in Hand:\n");
	for (i = 0; i < state->handCount[player]; i++){
		printf("card %d: %d\n", i, state->hand[player][i]);
	}
	printf("Cards in Deck:\n");
	for (i = 0; i < state->deckCount[player]; i++){
		printf("card %d: %d\n", i, state->deck[player][i]);
	}
	printf("Cards in Discard:\n");
	for (i = 0; i < state->discardCount[player]; i++){
		printf("card %d: %d\n", i, state->discard[player][i]);
	} 
}

void resetCards( int player, struct gameState *state){
	//Reset all players cards to copper
	int i;
	for (i = 0; i < state->handCount[player]; i++){
		state->hand[player][i] = 4;
	}
	for (i = 0; i < state->deckCount[player]; i++){
		state->deck[player][i] = 4;
	}
	for (i = 0; i < state->discardCount[player]; i++){
		state->discard[player][i] = 4;
	} 	
}

int main(){
	//Initiate game
	int score;
	int player = 0; //Player to use for verification
	struct gameState currentState;
	int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
		   sea_hag, tribute, smithy};
	
	//2 = number of players
	//10 = random generator seed
	initializeGame(2, k, 10, &currentState);
	
	// -- Test 1: Game start, player score should be 3 (3 estates)
	score = scoreFor(player, &currentState);
	if (score == 3){
		printf("Test 1 success: score == 3\n"); 
	} else {
		printf("Test 1 failure: score (%d) != 3\n", score); 
	}
	
	//printCards(player, &currentState);
	
	
	// -- Test 2: Give the player additional victory cards
	// -- 1 Province (6 pts) , 1 Estates (1 pt), 1 duchy (3 pts) = 10 pts
	// -- First reset players hand to be all coppers, for complete control
	resetCards(player, &currentState);
	
	//Put in the victory cards
	currentState.hand[player][0] = province;
	currentState.hand[player][1] = duchy; 
	currentState.hand[player][2] = estate;
	
	score = scoreFor(player, &currentState);
	if (score == 10){
		printf("Test 2 success: score == 10\n"); 
	} else {
		printf("Test 2 failure: score (%d) != 10\n", score); 
	}
	
	// -- Test 3: Give player 1 curse
	// -- Should now equal 9
	// -- Add curse to card #4, as 1 - 3 are still victory cards
	currentState.hand[player][3] = curse;
	score = scoreFor(player, &currentState);
	if (score == 9){
		printf("Test 3 success: score == 9\n"); 
	} else {
		printf("Test 3 failure: score (%d) != 9\n", score); 
	}
	
	// -- Test 4: Have a victory card in each possible places for cards
	// -- 1 in hand, 1 in discard, 1 in deck = 10
	// -- First reset players hand to be all coppers, for complete control
	resetCards(player, &currentState);
	
	//Put in the victory cards
	//Need to update the discard number to 1, since it starts at 0
	currentState.discardCount[player] = 1;
	currentState.hand[player][0] = province;
	currentState.deck[player][0] = duchy; 
	currentState.discard[player][0] = estate;
	
	score = scoreFor(player, &currentState);
	if (score == 10){
		printf("Test 4 success: score == 10\n"); 
	} else {
		printf("Test 4 failure: score (%d) != 10\n", score); 
	}
	
	//printCards(player, &currentState);
	
	return 0;
}