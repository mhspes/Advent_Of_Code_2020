#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

static char fname[] = "inputs/aoc14.txt";
static FILE * fp;

#define LEN_MAX 100000
uint64_t res;
uint32_t len;

typedef struct
{
	uint64_t address;
    uint64_t value; // The 36-bit val %llu
} memory_val;

memory_val temp_mem[LEN_MAX];

// Save the value to the specific address
static void move_mem(uint64_t addr, uint64_t val)
{
	int i = 0;
	// Assume non-zero addresses
	while(i < LEN_MAX)
	{
		if ((temp_mem+i)->address == 0)
		{
			(temp_mem+i)->address = addr;
			(temp_mem+i)->value = val;

			if(++len >= LEN_MAX-1)
			{
				printf("Memory limit reached..\n");
				exit(0);
			}
			break;
		}
		else if(addr == (temp_mem+i)->address)
		{
			(temp_mem+i)->value = val;
			break;
		}
		i++;
	}
}

// Process the floating addresses
void addfloating(uint64_t addr, const uint64_t arg, uint64_t floating,
		uint8_t * index, uint8_t am)
{
	uint64_t temp;
	uint32_t ind, limit;
	int32_t j;
	limit = 1ULL << am;

	addr &= ~(floating); // initialize floating bit positions to zero
	for(ind = 0; ind < limit; ind++)
	{
		// Go through [0.. 2^am], shift bits to X's position (index array)
		temp = 0;
		for(j = am; j >= 0; j--)
		{
			if(1 & (ind >> j))
			{
				// Floating bit is shifted to the correct position
				temp += 1ULL << index[am-j-1];
			}
		}
		temp |= addr;
		move_mem(temp, arg);
	}

}
// Accumulate values in the memory
static uint64_t acc_sum(memory_val * memval)
{
	int i;
	uint64_t sum;

	sum = i = 0;
	while(i < len)
	{
		sum += (memval+i++)->value;
	}
	return sum;
}


// Part 2/2
static void part2()
{
	char c, tempc[5];
	uint32_t ind;
	uint64_t mask, arg, addr;
	uint64_t floating;
	uint8_t index[36], i;

	memset(temp_mem, 0, sizeof(temp_mem));

	floating = mask =  i = len = res = 0;

	while(EOF != fscanf(fp, "%4c", tempc))
	{
		if(!strcmp(tempc, "mem["))
		{
			if(0 != fscanf(fp, "%llu] = %llu\n", &addr, &arg))
			{
				addr |= mask;
				// Go through floating bits + save to memory
				addfloating(addr, (const uint64_t) arg, floating, &index[0], i);
			}
		}
    	else if(!strcmp(tempc, "mask"))
    	{
    		fscanf(fp, " = "); // ignore

    		ind = 35;
    		mask = floating = i = 0;
    		memset(index, 0, sizeof(index));
    		while('\n' != (c = fgetc(fp)))
    		{
    			if('X' == c)
    			{
    				floating += 1ULL << ind;
    				index[i++] = ind--;
    			}
    			else if ('1' == c)
    			{
    				mask += 1ULL << ind--;
    			}
    			else if ('0' == c)
    			{
    				ind--;
    			}
    			else
    			{
    				exit(0);
    			}
    		}
    	}
		else
		{
			exit(0); // Something wrong..
		}
	}

    res = acc_sum(temp_mem);
    printf("Task 2 result: %llu \n", res);

}

// Part 1/2
static void part1()
{

    char c, tempc[5];
    uint32_t ind;
    uint64_t mask, xbits, arg, temp, addr;

    memset(temp_mem, 0, sizeof(temp_mem));
    res = len = mask = xbits = temp = 0;

    while(EOF != fscanf(fp, "%4c", tempc))
    {

    	if(!strcmp(tempc, "mem["))
    	{
    		if(0 != fscanf(fp, "%llu] = %llu\n", &addr, &arg))
    		{
    			temp = arg & xbits;
    			arg &= mask; // toggle 0's
    			arg |= mask | temp; // toggle 1's and unchanged bits
    			move_mem(addr, arg);
    		}
    	}
    	else if(!strcmp(tempc, "mask"))
    	{
    		fscanf(fp, " = "); // ignore

    		ind = 35;
    		mask = xbits = 0;
    		while('\n' != (c = fgetc(fp)))
    		{
    			if('X' == c)
    			{
    				xbits += 1ULL << ind--;
    			}
    			else if ('1' == c)
    			{
    				mask += 1ULL << ind--;
    			}
    			else if ('0' == c)
    			{
    				ind--;
    			}
    			else
    			{
    				exit(0);
    			}
    		}
    	}
    	else
    	{
    		exit(0);
    	}
    }

    res = acc_sum(temp_mem);
    printf("Task 1: %llu\n", res);

}

void aoc14()
{

    if(NULL == ( fp = fopen(fname, "r")))
    {
    	perror(fname);
        exit(0);
    }

    part1();

    rewind(fp);

    part2();

}
