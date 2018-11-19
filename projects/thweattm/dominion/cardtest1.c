/*
Mike Thweatt
10/14/18
CS362
Dominion - Card Test 1
'smithy' card
smithy info: Add 3 cards to hand, discard the smithy card
*/

#include "dominion.h"
#include <stdio.h>
#include <string.h>

void rigPlayerCards(int player, struct gameState *currentState){
	//Hand cards
	currentState->hand[player][0] = copper;
	currentState->hand[player][1] = silver;
	currentState->hand[player][2] = gold;
	currentState->hand[player][3] = adventurer;
	currentState->hand[player][4] = smithy;
	//Deck cards
	currentState->deck[player][0] = estate;
	currentState->deck[player][1] = duchy;
	currentState->deck[player][2] = province;
	currentState->deck[player][3] = village;
	currentState->deck[player][4] = cutpurse;
}

int main(){
	//Initiate game
	int i, found;
	struct gameState currentState, originalState;
	int k[10] = {adventurer, feast, gardens, smithy, village, minion, mine, cutpurse,
		   embargo, outpost};
	
	//2 = number of players
	//10 = random generator seed
	initializeGame(2, k, 10, &currentState);
	
	//Start the test with all unique cards between hand and deck for better verification
	rigPlayerCards(0, &currentState);
	
	//Copy original gameState for comparison after
	memcpy(&originalState, &currentState, sizeof(struct gameState));
	
	//Play smithy card (in handPos 4)
	playCard(4, -1, -1, -1, &currentState);
	
	
	// -- Section 1: Current player items
		// -- 1.a: Score should stay the same
		if (scoreFor(0, &currentState) == scoreFor(0, &originalState)){
			printf("Test 1.a success: scores remain the same for player 1\n");
		} else {
			printf("Test 1.a failure: scores should have remained the same for player 1\n");
		}
		
		// -- 1.b: Number of actions should decrease by 1
		if (currentState.numActions == originalState.numActions -1){
			printf("Test 1.b success: numActions decreased by 1\n");
		} else {
			printf("Test 1.b failure: numActions did not decrease by 1\n");
		}
		
		// -- 1.c: Number of buys should remain the same
		if (currentState.numBuys == originalState.numBuys){
			printf("Test 1.c success: numBuys remained the same\n");
		} else {
			printf("Test 1.c failure: numBuys changed unexpectedly\n");
		}
		
		// -- 1.d: Deck should decrease by 3
		if (currentState.deckCount[0] == originalState.deckCount[0] - 3){
			printf("Test 1.d success: deckCount decreased by 3\n");
		} else {
			printf("Test 1.d failure: deckCount did not decrease by 3 (current deckCount: %d, original deckCount: %d)\n", 
				currentState.deckCount[0], originalState.deckCount[0]);
		}
		
		// -- 1.e: Played card count should increase by 1
		if (currentState.playedCardCount == originalState.playedCardCount + 1){
			printf("Test 1.e success: playedCardCount increased by 1\n");
		} else {
			printf("Test 1.e failure: playedCardCount did not increase by 1 (current playedCardCount: %d, original playedCardCount: %d)\n", 
				currentState.playedCardCount, originalState.playedCardCount);
		}
		
		// -- 1.f: playedCards[i] should now have smithy
		found = 0;
		for (i = 0; i < currentState.playedCardCount; i++){
			if (currentState.playedCards[i] == smithy){
				found = 1;
				break;
			}
		}
		if (found){
			printf("Test 1.f success: smithy now in the played stack\n");
		} else {
			printf("Test 1.f failure: smithy is not in the played stack\n");
		}
		
		// -- 1.g: handCount should increase by 2 (additional 3 cards - 1 smithy)
		if (currentState.handCount[0] == originalState.handCount[0] + 2){
			printf("Test 1.g success: handCount increased by 2\n");
		} else {
			printf("Test 1.g failure: handCount did not increase by 2 (current handCount: %d, original handCount: %d)\n", 
				currentState.handCount[0], originalState.handCount[0]);
		}
		
		// -- 1.h: hand[player][i] should no longer have smithy
		found = 0;
		for (i = 0; i < currentState.handCount[0]; i++){
			if (currentState.hand[0][i] == smithy){
				found = 1;
				break;
			}
		}
		if (found){
			printf("Test 1.h failure: smithy is still in hand\n");
		} else {
			printf("Test 1.h success: smithy is no longer in hand\n");
		}
		
	// -- Section 2: Other players things should remain the same
		// -- 2.a: Number of cards stay the same in hand
		if (currentState.handCount[1] == originalState.handCount[1]){
			printf("Test 2.a success: player 2 handCount unchanged\n");
		} else {
			printf("Test 2.a failure: player 2 handCount has changed (current handCount: %d, original handCount: %d)\n", 
				currentState.handCount[1], originalState.handCount[1]);
		}
		
		// -- 2.b: Number of cards stay the same in deck
		if (currentState.deckCount[1] == originalState.deckCount[1]){
			printf("Test 2.b success: player 2 deckCount unchanged\n");
		} else {
			printf("Test 2.b failure: player 2 deckCount has changed (current deckCount: %d, original deckCount: %d)\n", 
				currentState.deckCount[1], originalState.deckCount[1]);
		}
		
		// -- 2.c: Exact cards should remain same in hand
		found = 0;
		for (i = 0; i < currentState.handCount[1]; i++){
			if (currentState.hand[1][i] != originalState.hand[1][i]){
				found = 1;
				break;
			}
		}
		if (found){
			printf("Test 2.c failure: player 2 cards in hand has changed\n");
		} else {
			printf("Test 2.c success: player 2 cards in hand remains unchanged\n");
		}
		
		// - 2.d: Exact cards should remain same in deck
		found = 0;
		for (i = 0; i < currentState.deckCount[1]; i++){
			if (currentState.deck[1][i] != originalState.deck[1][i]){
				found = 1;
				break;
			}
		}
		if (found){
			printf("Test 2.d failure: player 2 cards in deck has changed\n");
		} else {
			printf("Test 2.d success: player 2 cards in deck remains unchanged\n");
		}
		
		// -- 2.e: Score should remain the same
		if (scoreFor(1, &currentState) == scoreFor(1, &originalState)){
			printf("Test 2.e success: scores remain the same for player 2\n");
		} else {
			printf("Test 2.e failure: scores should have remained the same for player 2\n");
		}
	
	return 0;
}