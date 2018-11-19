/*
Mike Thweatt
10/14/18
CS362
Dominion - Card Test 4
'cutpurse' card
cutpurse info: +2 coins, each other player loses 1 copper
	if a player has no copper, they reveal their hand to prove it
*/

#include "dominion.h"
#include <stdio.h>
#include <string.h>

int main(){
	//Initiate game
	int i, found;
	struct gameState currentState, originalState;
	int k[10] = {adventurer, feast, gardens, smithy, village, minion, mine, cutpurse,
		   embargo, outpost};
	
	//2 = number of players
	//10 = random generator seed
	initializeGame(2, k, 10, &currentState);
	
	//Give player 1 a cutpurse card to use
	currentState.hand[0][0] = cutpurse;
	//Make sure player 2 has at least 1 copper in hand
	currentState.hand[1][0] = copper;
	
	//Copy original gameState for comparison after
	memcpy(&originalState, &currentState, sizeof(struct gameState));
	
	//Play cutpurse card (in handPos 0)
	playCard(0, -1, -1, -1, &currentState);
	
	
	// -- Section 1: Current player items
		// -- 1.a: Score should stay the same
		if (scoreFor(0, &currentState) == scoreFor(0, &originalState)){
			printf("Test 1.a success: Player 1 score remains the same\n");
		} else {
			printf("Test 1.a failure: Player 1 score changed unexpectedly\n");
		}
		
		// -- 1.b: Number of buys should remain the same
		if (currentState.numBuys == originalState.numBuys){
			printf("Test 1.b success: Player 1 numBuys remained the same\n");
		} else {
			printf("Test 1.b failure: Player 1 numBuys changed unexpectedly\n");
		}
		
		// -- 1.c: playedCardCount should increase by 1
		if (currentState.playedCardCount == originalState.playedCardCount + 1){
			printf("Test 1.c success: playedCardCount increased by 1\n");
		} else {
			printf("Test 1.c failure: playedCardCount did not increase by 1 (current playedCardCount: %d, original playedCardCount: %d)\n", 
				currentState.playedCardCount, originalState.playedCardCount);
		}
		
		// -- 1.d: playedCards[i] should have cutpurse
		found = 0;
		for (i = 0; i < currentState.playedCardCount; i++){
			if (currentState.playedCards[i] == cutpurse){
				found = 1;
				break;
			}
		}
		if (found){
			printf("Test 1.d success: cutpurse found in playedCards\n");
		} else {
			printf("Test 1.d failure: cutpurse not found in playedCards\n");
		}
		
		// -- 1.e: handCount should decrease by 1
		if (currentState.handCount[0] == originalState.handCount[0] - 1){
			printf("Test 1.e success: Player 1 handCount decreased by 1\n");
		} else {
			printf("Test 1.e failure: Player 1 handCount did not decrease by 1 (current handCount: %d, original handCount: %d)\n", 
				currentState.handCount[0], originalState.handCount[0]);
		}
		
		// -- 1.f: hand[player][i] should no longer have cutpurse
		found = 0;
		for (i = 0; i < currentState.handCount[0]; i++){
			if (currentState.hand[0][i] == cutpurse){
				found = 1;
				break;
			}
		}
		if (found){
			printf("Test 1.f failure: Player 1 still has cutpurse in hand\n");
		} else {
			printf("Test 1.f success: Player 1 no longer has cutpurse in hand\n");
		}
		
		// -- 1.g: Coins should be 2
		if (currentState.coins == 2){
			printf("Test 1.g success: Player 1 has two coins\n");
		} else {
			printf("Test 1.g failure: Player 1 coins are not 2 (current coins: %d)\n", 
				currentState.coins);
		}

	// -- Section 2: Player 2
		// -- 2.a: Player should have 1 less copper
		int currentCopper = 0, originalCopper = 0;
		for (i = 0; i < currentState.handCount[1]; i++){
			if (currentState.hand[1][i] == copper){
				currentCopper++;
			}
		}
		for (i = 0; i < originalState.handCount[1]; i++){
			if (originalState.hand[1][i] == copper){
				originalCopper++;
			}
		}
		if (currentCopper == originalCopper - 1){
			printf("Test 2.a success: Player 2 has 1 less copper\n");
		} else {
			printf("Test 2.a failure: Player 2 does not have 1 less copper (current copper count: %d, original copper count: %d, cards in hand: %d\n",
				currentCopper, originalCopper, currentState.handCount[1]);
		}
		
		// -- 2.e: Score should remain the same
		if (scoreFor(1, &currentState) == scoreFor(1, &originalState)){
			printf("Test 2.e success: player 2 score remains the same\n");
		} else {
			printf("Test 2.e failure: player 2 score should have remained the same\n");
		}

	return 0;
}