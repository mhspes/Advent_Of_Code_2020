#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>

#define STATE_MAX 10000

uint8_t states[STATE_MAX][50]; 	// Static memory for the previous hands of the round
uint8_t (*ptr_s)[50];			// Pointer to the next empty state

// Input data
const uint8_t cards_p1[50] = {25, 37, 35, 16, 9, 26, 17, 5, 47, 32, 11, 43, 40, 15, 7, 19, 36, 20, 50, 3, 21, 34, 44, 18, 22};
const uint8_t cards_p2[50] = {12, 1, 27, 41, 4, 39, 13, 29, 38, 2, 33, 28, 10, 6, 24, 31, 42, 8, 23, 45, 46, 48, 49, 30, 14};

// Winning card stack
uint8_t result_stack[50];


/* Check if looping, (ie. same cards in the same order in a player's deck)
 * Ret 1 for repeating state, 0 otherwise
 * @param sample_stack			the stack (state) to be compared
 * @param size_stack			number of cards in the stack
 * @param state_ptr				pointer to the first saved state of an iteration
 * @param last					pointer to the last saved state
 */
static uint8_t check_states(uint8_t * sample_stack, uint8_t size_stack,
		uint8_t (*state_ptr)[50], uint8_t (*last)[50])
{
    uint32_t ind_state, ind_card;

    ind_state = 0;
    while(&state_ptr[ind_state] <= last)
    {
        for(ind_card = 0; ind_card < size_stack; ind_card++)
        {
        	if(sample_stack[ind_card] != state_ptr[ind_state][ind_card])
        		break; // ind_card:th card differs --> break
        	if(ind_card == size_stack-1 && state_ptr[ind_state][ind_card+1] == 0)
        	{
        		// Last card read, all matched
        		return 1;
        	}
        }
        ind_state++;
    }
    // No repeating state found, return 0
    return 0;
}

/* Perform a card swap (two played cards to the bottom of winner's card stack)
 * and shift to fix arr indexes
 * @param dest			destination card stack
 * @param src			source stack
 * @param len_d			dest card stack size
 * @paran len_s			source size
 */
static void SwapShift(uint8_t * dest, uint8_t * src, uint8_t * len_d, uint8_t * len_s)
{
    int i;
    uint8_t temp1 = *dest;
    for(i = 1; i < *len_d; i++){
        dest[i-1] = dest[i];
    }
    dest[*len_d-1] = temp1;
    dest[*len_d] = src[0];
    for(i = 1; i < *len_s; i++){
        src[i-1] = src[i];
    }
    src[*len_s-1] = 0;
    (*len_d)++;
    (*len_s)--;
}

/* Recursive combat-function
 * ret 1 if player 1 wins, 0 if player 2 wins
 * @param l1			pointer to the first card stack
 * @param l2			pointer to the 2nd card stack
 * @param len1			length of the 1st cardstack
 * @param len2			len of the 2nd cardstack
 */
static int recursiveCombat(uint8_t * l1, uint8_t * l2, uint8_t len1, uint8_t len2)
{
    uint8_t l1_temp[50], l2_temp[50];
    uint8_t res;

    // Save state-pointer address
    uint8_t (*p_states)[50] = ptr_s;

    // Temp card stack data for the subgame
    memcpy(l1_temp, l1, len1);
    memcpy(l2_temp, l2, len2);
    memset(l1_temp+len1, 0, 50-len1);
    memset(l2_temp+len2, 0, 50-len2);


    while(len1 != 0 && len2 != 0)
    {
        // Check if a repeating state occurs..
        // Note: sufficient to check either player's cards
        res = check_states(l1_temp, len1, p_states, ptr_s);
        if(res == 1)
        {
        	// Repeating state, p1 wins
        	// Clear states & reset the pointer
        	memset(p_states, 0, 50*(ptr_s-p_states));
        	ptr_s = p_states;
        	return 1;
        }

        // Save the current state to the list
        memcpy(ptr_s, l1_temp, len1);

        ptr_s++;
        // Check if state buffer full
        if(ptr_s == &states[STATE_MAX])
        {
            printf("Buffer full..\n");
            exit(0);
        }

        if(len1-1 >= l1_temp[0] && len2-1 >= l2_temp[0])
        {
            res = recursiveCombat(&l1_temp[1], &l2_temp[1], l1_temp[0], l2_temp[0]);
            if(res)
                SwapShift(&l1_temp[0], &l2_temp[0], &len1, &len2);
            else
                SwapShift(&l2_temp[0], &l1_temp[0], &len2, &len1);
        } else {
            if(l1_temp[0] > l2_temp[0])
                SwapShift(&l1_temp[0], &l2_temp[0], &len1, &len2);
            else
                SwapShift(&l2_temp[0], &l1_temp[0], &len2, &len1);
        }
    }

    // Clear states & reset the pointer as in the beginning
    memset(p_states, 0, 50*(ptr_s-p_states));
    ptr_s = p_states;

    if(len1 == 50)
    {
        memcpy(result_stack, l1_temp, len1);
        return 1;
    }
    if(len2 == 50)
    {
        memcpy(result_stack, l2_temp, len2);
        return 0;
    }
    if(len1 && !len2)
    {
    	return 1;
    } else if (len2 && !len1)
    {
    	return 0;
    } else {
    	printf("Error? len1:%d, len2:%d\n", len1, len2);
    	exit(0);
    }

}

// Part 2/2
static void part2()
{
	uint32_t sum;
	uint8_t l1_temp[50], l2_temp[50], i, ret;

    memcpy(l1_temp, cards_p1, 50);
    memcpy(l2_temp, cards_p2, 50);

    sum = 0;
    ptr_s = &states[0];

    memset(states, 0, sizeof(states));

    ret = recursiveCombat(l1_temp, l2_temp, 25, 25);

    if(ret)
    	for(i = 0; i < 50; i++)
    		sum += result_stack[i]*(50-i);
    else
    	for(i = 0; i < 50; i++)
    		sum += result_stack[i]*(50-i);

    printf("Part 2: %u\n", sum);

}

// Part 1/2
static void part1()
{
	uint32_t sum = 0;

	uint8_t l1_temp[50], l2_temp[50], len1, len2, i;
    len1 = len2 = 25;


	// Make local copies of cards
	memcpy(l1_temp, cards_p1, 50);
	memcpy(l2_temp, cards_p2, 50);

	while(len1 != 0 && len2 != 0)
	{
		if(l1_temp[0] > l2_temp[0])
			SwapShift(l1_temp, l2_temp, &len1, &len2);
		else
			SwapShift(l2_temp, l1_temp, &len2, &len1);
	}

	if(len1 != 0)
		for(i = 0; i < 50; i++)
			sum += l1_temp[i]*(len1-i);
	else
		for(i = 0; i < 50; i++)
			sum += l2_temp[i]*(len2-i);

	printf("Part 1: %u\n", sum);

}

void aoc22(void)
{
	part1();
	part2();

}
