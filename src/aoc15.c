#include <stdio.h>
#include <string.h>
#include <stdint.h>

uint32_t input[] = {2,0,6,12,1,3};

#define LIMIT 30000000
// Hash-table sort of
static uint32_t value[LIMIT];
static uint8_t key[LIMIT];


static uint32_t process(uint32_t max)
{

	uint32_t ind, prev, next;
	memset(key, 0, max);

	// Initialize
    for(ind = 0; ind < 6; ind++)
    {
    	key[input[ind]] = 1;
    	value[input[ind]] = ind;
    }
	prev = 0;

    for(ind = 6; ind < max-1; ind++)
    {
    	if(!key[prev])
    	{
    		// First occurrence
    		key[prev] = 1;
    		value[prev] = ind;
    		prev = 0;
    	}
    	else
    	{
    		next = ind - value[prev];
    		value[prev] = ind;
    		prev = next;
    	}
    }

    return prev;

}

// Part 1 & 2
void aoc15()
{
	uint32_t res;

	res = process(2020);
	printf("Part1 : %u \n", res);

	res = process(LIMIT);
	printf("Part2 : %u \n", res);

}
