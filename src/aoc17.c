#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

static char fname[] = "inputs/aoc17.txt";

FILE * fp;

//#define PART_1
#define PART_2

#if defined(PART_1) && defined(PART_2)
	#error	Error, only one part may be defined at a time.
#endif

#define MAX 8+2*(6+1)

#define LOOP(x, y, z, min, max, ...)				\
	for(x = min; (x) <= max; (x)++)			\
	{												\
		for(y = min; (y) <= max; (y)++)  			\
		{											\
			for(z = min; (z) <= max; (z)++)			\
			{										\
				__VA_ARGS__							\
			}										\
		}											\
	}

static uint8_t cube[MAX][MAX][MAX][MAX];
static uint8_t cube_temp[MAX][MAX][MAX][MAX];

#ifdef PART_2
// For checking the neighbor (4D) cubes
static uint8_t check(int x, int y, int z, int w)
{
    int i,j,k,l;
    int val;	// Amount of active neighboring cubes
    val = 0;

    LOOP(i, j, k, -1, 1, {
    		for(l = -1; l <= 1; l++)
    		{
    			if(i==0 && j==0 && k==0 && l==0)
    				continue;
    			if(cube[x+i][y+j][z+k][w+l] == 1)
    				val++;
    		}});

    if(cube[x][y][z][w])	// Active cube
    {
    	if(val == 2 || val == 3)
    		return 1;
    } else {
    	// Inactive cube
    	if(val == 3)
    		return 1;
    }
    return 0;

}

#elif defined(PART_1)
// For checking the neighbor conway cubes
static uint8_t check(int x, int y, int z)
{
    int i, j, k, val;	// Amount of active neighboring cubes
    val = 0;

    LOOP(i, j, k, -1, 1, {
    		if(i==0 && j==0 && k==0)
    			continue;
    		if(cube[x+i][y+j][z+k][0] == 1)
    			val++;
    });

    if(cube[x][y][z][0]) // Active cube
    {
    	if(val == 2 || val == 3)
    		return 1;
    } else {
    	// Inactive cube
    	if(val == 3)
    		return 1;
    }
    return 0;
}
#endif


#ifdef PART_2
// Part 2/2
static void part2()
{
		int i, counter, x, y, z, w;

		i = counter = 0;
		while(i < 6)
		{
			LOOP(x, y, z, 0, MAX-1,
					{
							for(w = 0; w < MAX; w++)
							{
								cube_temp[x][y][z][w] = check(x,y,z,w);
							}

					});

		i++;
		memcpy(cube, cube_temp, sizeof(cube));
		}

		LOOP(x, y, z, 0, MAX-1,{
				for(w = 0; w < MAX; w++)
				{
					counter += cube[x][y][z][w];
				}
		});

		printf("\n Part 2: %d \n", counter);

}
#endif

#ifdef PART_1
// Part 1/2
static void part1()
{
	int i, counter, x, y, z;

	i = counter = 0;
	while(i < 6)
	{
		LOOP(x, y, z, 0, MAX-1, cube_temp[x][y][z][0] = check(x,y,z); );
		i++;
		memcpy(cube, cube_temp, sizeof(cube));
	}

	LOOP(x, y, z, 0, MAX-1, counter += cube[x][y][z][0]; );

	printf("\n Part 1: %d \n", counter);

}
#endif


void aoc17()
{

	int x, y;
	char c;

    memset(cube, 0, sizeof(cube));
    memset(cube_temp, 0, sizeof(cube_temp));

    if(NULL == ( fp = fopen(fname, "r")))
    {
    	perror(fname);
    	exit(0);
    }

    // Fill conway cube with bool values
    for(x = 7; x < 15; x++)
    {
    	for(y = 7; y < 15 ; y++)
    	{
    		if('\n' == (c = fgetc(fp)))
    			c = fgetc(fp); // Linebreak, read next..
    		if('#' == c)
    			cube[x][y][0][0] = 1;
    	}
    }

#if defined(PART_1)
    part1();
#elif defined(PART_2)
    part2();
#endif

}
