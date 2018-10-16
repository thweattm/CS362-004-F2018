/*
Mike Thweatt
10/14/18
CS362
Dominion - Unit Test 1
'compare' function
*/

#include "dominion.h"
#include <stdio.h>

int main(){
	int a, b, c;
	
	// -- Test 1: a > b && both are positive numbers
	a = 5;
	b = 0;
	c = compare(&a, &b);
	
	if (c == 1){
		printf("Test 1 success: a (%d) > b (%d)\n", a, b);
	} else if (c == -1){
		printf("Test 1 failure: a (%d) < b (%d)\n", a, b);
	} else {
		printf("Error in Unit Test 1 - Test 1 (a=%d b=%d)\n", a, b);
	}
	
	// - Test 2: a < b && including negative and positive numbers
	a = -5;
	b = 2;
	c = compare(&a, &b);
	
	if (c == 1){
		printf("Test 2 failure: a (%d) > b (%d)\n", a, b);
	} else if (c == -1){
		printf("Test 2 success: a (%d) < b (%d)\n", a, b);
	} else {
		printf("Error in Unit Test 1 - Test 2 (a=%d b=%d)\n", a, b);
	}
	
	// - Test 3: a == b
	a = 3;
	b = 3;
	c = compare(&a, &b);
	
	if (c == 1){
		printf("Test 3 failure: a (%d) > b (%d)\n", a, b);
	} else if (c == -1){
		printf("Test 3 failure: a (%d) < b (%d)\n", a, b);
	} else {
		printf("Test 3 error: a (%d) == b (%d)\n", a, b);
	}
	
	// - Test 4: both negative numbers
	a = -10;
	b = -3;
	c = compare(&a, &b);
	
	if (c == 1){
		printf("Test 4 failure: a (%d) > b (%d)\n", a, b);
	} else if (c == -1){
		printf("Test 4 success: a (%d) < b (%d)\n", a, b);
	} else {
		printf("Error in Unit Test 1 - Test 4 (a=%d b=%d)\n", a, b);
	}
	
	// - Test 5: large numbers
	a = 847485;
	b = 918273;
	c = compare(&a, &b);
	
	if (c == 1){
		printf("Test 5 failure: a (%d) > b (%d)\n", a, b);
	} else if (c == -1){
		printf("Test 5 success: a (%d) < b (%d)\n", a, b);
	} else {
		printf("Error in Unit Test 1 - Test 5 (a=%d b=%d)\n", a, b);
	}
	
	return 0;
}