/*
Mike Thweatt
10/14/18
CS362
Dominion - Card Test 2
'adventurer' card
adventurer info: Reveal cards from your deck until you reveal 2 treasure cards. 
	Place the treasure cards in your hand and discard the other revealed cards.
*/

#include "dominion.h"
#include <stdio.h>
#include <string.h>

void rigPlayerCards(int player, struct gameState *currentState){
	//Hand cards (no treasure in hand to start)
	currentState->hand[player][0] = estate;
	currentState->hand[player][1] = duchy;
	currentState->hand[player][2] = province;
	currentState->hand[player][3] = adventurer;
	currentState->hand[player][4] = smithy;
	//Deck cards (Put treasure at the end to generate cards skipped)
	currentState->deck[player][0] = cutpurse;
	currentState->deck[player][1] = village;
	currentState->deck[player][2] = gold;
	currentState->deck[player][3] = silver;
	currentState->deck[player][4] = copper;
}

int main(){
	//Initiate game
	int i, j, found;
	struct gameState currentState, originalState;
	int k[10] = {adventurer, feast, gardens, smithy, village, minion, mine, cutpurse,
		   embargo, outpost};
	
	//2 = number of players
	//10 = random generator seed
	initializeGame(2, k, 10, &currentState);
	
	//Start the test with all unique cards between hand and deck for better verification
	//Start with NO treasure in hand, only in deck
	rigPlayerCards(0, &currentState);
	
	//Copy original gameState for comparison after
	memcpy(&originalState, &currentState, sizeof(struct gameState));
	
	//Play adventurer card (in handPos 3)
	playCard(3, -1, -1, -1, &currentState);
	
	
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
		
		// -- 1.d: Deck should decrease by 2 + however many non-treasure cards were found
		// -- for the test, it should skip 2 cards, so deck should decrease by 4
		if (currentState.deckCount[0] == originalState.deckCount[0] - 4){
			printf("Test 1.d success: deckCount decreased by 4\n");
		} else {
			printf("Test 1.d failure: deckCount did not decrease by 4 (current deckCount: %d, original deckCount: %d)\n", 
				currentState.deckCount[0], originalState.deckCount[0]);
		}
		
		// -- 1.e: discardCount[player] should equal however many non-treasure cards were skipped
		// for this test, two should be discarded (cutpurse and village)
		if (currentState.discardCount[0] == originalState.discardCount[0] + 2){
			printf("Test 1.e success: discardCount increased by 2\n");
		} else {
			printf("Test 1.e failure: discardCount did not increase by 2 (current discardCount: %d, original discardCount: %d)\n", 
				currentState.discardCount[0], originalState.discardCount[0]);
		}
		
		// -- 1.f: discard[player][i] should now have all cards that were skipped
		// -- For this test it should have cutpurse and village)
		j = 0;
		for (i = 0; i < currentState.discardCount[0]; i++){
			if (currentState.discard[0][i] == cutpurse || currentState.discard[0][i] == village){
				j++;
			}
		}
		if (j == 2){
			printf("Test 1.f success: cuturse & village found in discard\n");
		} else {
			printf("Test 1.f failure: cutpurse & village not found in discard\n");
		}
		
		// -- 1.g: handCount should increase by 1 (additional 2 treasure cards - 1 adventurer)
		if (currentState.handCount[0] == originalState.handCount[0] + 1){
			printf("Test 1.g success: handCount increased by 1\n");
		} else {
			printf("Test 1.g failure: handCount did not increase by 1 (current handCount: %d, original handCount: %d)\n", 
				currentState.handCount[0], originalState.handCount[0]);
		}
		
		// -- 1.h: hand[player][i] should no longer have adventurer
		found = 0;
		for (i = 0; i < currentState.handCount[0]; i++){
			if (currentState.hand[0][i] == adventurer){
				found = 1;
				break;
			}
		}
		if (found){
			printf("Test 1.h failure: adventurer is still in hand\n");
		} else {
			printf("Test 1.h success: adventurer is no longer in hand\n");
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
			printf("Test 2.e success: player 2 score remains the same\n");
		} else {
			printf("Test 2.e failure: player 2 score should have remained the same\n");
		}

	return 0;
}