/*
Mike Thweatt
11/13/18
CS362
Dominion - Random Test Card 1
'smithy' card
smithy info: Add 3 cards to hand, discard the smithy card
int cardEffect(int card, int choice1, int choice2, int choice3, struct gameState *state, int handPos, int *bonus)
*/

#include "dominion.h"
#include <assert.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

int testCard(int choice1, int choice2, int choice3, struct gameState *currentGame, int handPos, int *bonus, int i){
	int faultFound = 0;
	//Make a copy of the game state to compare after the card is played
	struct gameState gameBefore;
	memcpy(&gameBefore, currentGame, sizeof(struct gameState));
	int player = gameBefore.whoseTurn;
	
	//Play smithy card
	int result = cardEffect(smithy, choice1, choice2, choice3, currentGame, handPos, bonus);
	
	
	//Make needed changes to the gameBefore state as expected from the card functions
	
	//Because of the randomness of the shuffle function, copy the deck, hand, and playedCards arrays
	memcpy(gameBefore.deck[player], currentGame->deck[player], sizeof(int) * MAX_DECK);
	memcpy(gameBefore.hand[player], currentGame->hand[player], sizeof(int) * MAX_HAND);
	memcpy(gameBefore.playedCards, currentGame->playedCards, sizeof(int) * (currentGame->playedCardCount));
	
	//Increase hand count by 2 (+3 draws - 1 played)
	if (gameBefore.deckCount[player] < 3){
		//Add all available cards to hand
		gameBefore.handCount[player] += gameBefore.deckCount[player];
		//Subtract card played
		gameBefore.handCount[player]--;
	} else {
		gameBefore.handCount[player] += 2;
	}
	//Increase played count by 1
	gameBefore.playedCardCount++;
	//Decrease deck count by 3 (only if currently =>3)
	if (gameBefore.deckCount[player] < 4){
		gameBefore.deckCount[player] = 0;
	} else {
		gameBefore.deckCount[player] -= 3;
	}
	
	//Compare the game states before and after
	assert(result == 0);
	if (memcmp(&gameBefore, currentGame, sizeof(struct gameState)) != 0){
		faultFound = 1;
		printf("----------Loop %d---------\n", i);
		printf("gameBefore state != currentGame state\n");
		//Check more detailed gameState items
		if (gameBefore.numPlayers != currentGame->numPlayers){
			printf("Number of players has changed\n");}
		if (memcmp(&gameBefore.supplyCount, currentGame->supplyCount, sizeof(int) * (treasure_map + 1)) != 0){
			printf("Supply counts have changed\n");}
		if (memcmp(&gameBefore.embargoTokens, currentGame->embargoTokens, sizeof(int) * (treasure_map + 1)) != 0){
			printf("Embargo tokens have changed\n");}
		if (gameBefore.outpostPlayed != currentGame->outpostPlayed){
			printf("outpostPlayed has changed\n");}
		if (gameBefore.whoseTurn != currentGame->whoseTurn){
			printf("whoseTurn has changed\n");}
		if (gameBefore.phase != currentGame->phase){
			printf("phase has changed\n");}
		if (gameBefore.numActions != currentGame->numActions){
			printf("numActions has changed\n");}
		if (gameBefore.coins != currentGame->coins){
			printf("coins has changed\n");}
		if (gameBefore.numBuys != currentGame->numBuys){
			printf("numBuys has changed\n");}
		if (memcmp(&gameBefore.hand[player], currentGame->hand[player], sizeof(int) * gameBefore.handCount[player]) != 0){
			printf("hand array has changed\n");}
		if (gameBefore.handCount[player] != currentGame->handCount[player]){
			printf("handCount has changed. Before:%d After:%d\n", gameBefore.handCount[player], currentGame->handCount[player]);}
		if (memcmp(&gameBefore.deck[player], currentGame->deck[player], sizeof(int) * gameBefore.deckCount[player]) != 0){
			printf("deck array has changed\n");}
		if (gameBefore.deckCount[player] != currentGame->deckCount[player]){
			printf("deckCount has changed. Before:%d After:%d\n", gameBefore.deckCount[player], currentGame->deckCount[player]);}
		if (memcmp(&gameBefore.discard[player], currentGame->discard[player], sizeof(int) * gameBefore.discardCount[player]) != 0){
			printf("discard array has changed\n");}
		if (gameBefore.discardCount[player] != currentGame->discardCount[player]){
			printf("discardCount has changed. Before:%d After:%d\n", gameBefore.discardCount[player], currentGame->discardCount[player]);}
		if (memcmp(&gameBefore.playedCards, currentGame->playedCards, sizeof(int) * gameBefore.playedCardCount) != 0){
			printf("playedCards array has changed\n");}
		if (gameBefore.playedCardCount != currentGame->playedCardCount){
			printf("playedCardCount has changed. Before:%d After:%d\n", gameBefore.playedCardCount, currentGame->playedCardCount);}
	}
	
	return faultFound; //All tests complete
}

int main(){
	int choice1, choice2, choice3, bonus, handPos, player;
	int faultFound = 0;
	struct gameState currentGame;
	srand(time(NULL));
	
	printf("-----------------------------------\n");
	printf("Starting Random Test Card 1: Smithy\n");
	printf("-----------------------------------\n");
	
	//Test loops
	for (int i = 0; i < 1000; i++){
		//Randomize bytes in gameState
		for (int j = 0; j < sizeof(struct gameState); j++){
			((char*)&currentGame)[j] = floor(rand() * 256);
		}

		/***************************************
		* Assign any needed specific variables *
		****************************************/
		
		//Number of players between 2 and MAX_PLAYERS
		currentGame.numPlayers = rand() % MAX_PLAYERS + 2;
		
		//Current player between 0 and (numPlayers - 1)
		player = rand() % (currentGame.numPlayers - 1);
		currentGame.whoseTurn = player;
		
		//choice 1, 2, 3 = random cards between adventurer and treasure_map
		choice1 = rand() % treasure_map + adventurer;
		choice2 = rand() % treasure_map + adventurer;
		choice3 = rand() % treasure_map + adventurer;
		
		//Set handCount to 5 to ensure hand only has 5 cards
		currentGame.handCount[player] = 5;
		
		//Set deckCount to random number
		currentGame.deckCount[player] = rand() % MAX_DECK + 1;
		
		//Randomize handPos between 0 and number of cards in hand
		handPos = rand() % currentGame.handCount[player];
		
		/************
		* Test Card *
		*************/
		if (testCard(choice1, choice2, choice3, &currentGame, handPos, &bonus, i)){
			faultFound = 1;
		}
		
	}
	
	printf("All tests complete. ");
	if (faultFound){
		printf("Faults Found.\n");
	} else {
		printf("No Faults Found.\n");
	}
		
	return 0;
}