/*
Mike Thweatt
11/13/18
CS362
Dominion - Random Test adventurer card
'adventurer' card
adventurer info: Reveal cards from your deck until you find 2 treasure cards.
	Put the treasure cards in your hand, discard the remaining revealed cards.
int cardEffect(int card, int choice1, int choice2, int choice3, struct gameState *state, int handPos, int *bonus)
*/

#include "dominion.h"
#include <assert.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

int skipCards(int player, struct gameState *gameBefore){
	int skippedNum = 0;
	int treasureFound = 0;
	for (int i = gameBefore->deckCount[player]-1; i >= 0; i--){
		if (gameBefore->deck[player][i] == copper || gameBefore->deck[player][i] == silver ||
			gameBefore->deck[player][i] == gold){
			treasureFound++;
		} else {
			skippedNum++;
		}
		if(treasureFound == 2){
			return skippedNum;
		}
	}
	return -1; //Two treasures not found
}

int testCard(int choice1, int choice2, int choice3, struct gameState *currentGame, int handPos, int *bonus, int i){
	int faultFound = 0;
	//Make a copy of the game state to compare after the card is played
	struct gameState gameBefore;
	memcpy(&gameBefore, currentGame, sizeof(struct gameState));
	int player = gameBefore.whoseTurn;

	//Play adventurer card
	int result = cardEffect(adventurer, choice1, choice2, choice3, currentGame, handPos, bonus);
	

	//Make needed changes to the gameBefore state as expected from the card functions
	
	//Increase hand count by 1 (+2 treasures - 1 played)
	gameBefore.handCount[player] += 1;
	
	//Increase playedCardCount by 1
	gameBefore.playedCardCount++;
	
	//Determine the number of skipped cards and decrease deck by that many + 2 treasures
	int skippedCards = skipCards(player, &gameBefore);
	gameBefore.deckCount[player] -= (skippedCards + 2);
	
	//Add skipped cards to discardCount
	gameBefore.discardCount[player] = skippedCards;
	
	//Because of the randomness of the shuffle function, copy the deck, hand, and discard arrays
	memcpy(gameBefore.deck[player], currentGame->deck[player], sizeof(int) * MAX_DECK);
	memcpy(gameBefore.hand[player], currentGame->hand[player], sizeof(int) * MAX_HAND);
	memcpy(gameBefore.discard[player], currentGame->discard[player], sizeof(int) * MAX_DECK);
	
	
	
	//Compare the game states before and after
	assert(result == 0);
	if (memcmp(&gameBefore, currentGame, sizeof(struct gameState)) != 0){
		faultFound = 1;
		printf("----------Loop %d---------\n", i);
		printf("gameBefore state != currentGame state\n");
		//Check more detailed gameState items
		if (gameBefore.numPlayers != currentGame->numPlayers){
			printf("Number of players has changed. Should be %d, but is %d\n", gameBefore.numPlayers, currentGame->numPlayers);}
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
			printf("handCount has changed. Should be %d, but is %d\n", gameBefore.handCount[player], currentGame->handCount[player]);}
		if (memcmp(&gameBefore.deck[player], currentGame->deck[player], sizeof(int) * gameBefore.deckCount[player]) != 0){
			printf("deck array has changed\n");}
		if (gameBefore.deckCount[player] != currentGame->deckCount[player]){
			printf("deckCount has changed. Should be %d, but is %d\n", gameBefore.deckCount[player], currentGame->deckCount[player]);}
		if (memcmp(&gameBefore.discard[player], currentGame->discard[player], sizeof(int) * gameBefore.discardCount[player]) != 0){
			printf("discard array has changed\n");}
		if (gameBefore.discardCount[player] != currentGame->discardCount[player]){
			printf("discardCount has changed. Should be %d, but is %d\n", gameBefore.discardCount[player], currentGame->discardCount[player]);}
		if (memcmp(&gameBefore.playedCards, currentGame->playedCards, sizeof(int) * gameBefore.playedCardCount) != 0){
			printf("playedCards array has changed\n");}
		if (gameBefore.playedCardCount != currentGame->playedCardCount){
			printf("playedCardCount has changed. Should be %d, but is %d\n", gameBefore.playedCardCount, currentGame->playedCardCount);}
	}
	
	return faultFound; //All tests complete
}

int main(){
	int choice1, choice2, choice3, bonus, handPos, player;
	int faultFound = 0;
	struct gameState currentGame;
	srand(time(NULL));
	
	printf("-----------------------------------\n");
	printf("Starting Adventurer Random Testing:\n");
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
		
		//Set deckCount to random number >1
		currentGame.deckCount[player] = rand() % MAX_DECK + 2;
		
		
		//Randomize players deck with legitimate options
		for (int i = 0; i < MAX_DECK; i++){
			currentGame.deck[player][i] = rand() % treasure_map + curse;
		}
		
		//Stack deck with guaranteed treasure (also requires the deck count to be >1)
		currentGame.deck[player][0] = copper;
		currentGame.deck[player][1] = silver;
		
		//Print deck count and number of treasures in hand before running the function (segmentation fault verification)
		/*printf("Number of cards in deck: %d\n", currentGame.deckCount[player]);
		int currentTreasures = 0;
		for (int i = 0; i < currentGame.deckCount[player]; i++){
			if (currentGame.deck[player][i] == copper || currentGame.deck[player][i] == silver || currentGame.deck[player][i] == gold)
				currentTreasures++;
		}
		printf("Number of treasures in deck: %d\n", currentTreasures);*/
		
		//Randomize handPos between 0 and number of cards in hand
		handPos = rand() % currentGame.handCount[player];
		
		/************
		* Test Card *
		*************/
		if (testCard(choice1, choice2, choice3, &currentGame, handPos, &bonus, i)){
			faultFound = 1;
		}
		
	}
	
	printf("------------------------------------\n");
	printf("All tests complete. ");
	if (faultFound){
		printf("Faults Found.\n");
	} else {
		printf("No Faults Found.\n");
	}
	printf("------------------------------------\n");
	
	return 0;
}