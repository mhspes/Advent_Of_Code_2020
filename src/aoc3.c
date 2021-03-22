#include <stdlib.h>
#include <stdio.h>

static char fname[] = "inputs/aoc3.txt";
static FILE * fp;


// Find amount of encountered trees (#'s)
int aoc3_routine(int x, int y, char (*arg)[31])
{
	int i, j, count;
	i = j = count = 0;
	i += y;
	while(i < 323)
	{
		j += x;
		if(30 < j)j = j % 31;
		if(arg[i][j] == '#')count++;
		i += y;
	}
	printf("Trees encountered: %d\n", count);
	return count;
}

// Task 2/2
static void task2(char (*map)[31])
{
	unsigned int res = 1;
	res *= aoc3_routine(1, 1, map);
	res *= aoc3_routine(3, 1, map);
	res *= aoc3_routine(5, 1, map);
	res *= aoc3_routine(7, 1, map);
	res *= aoc3_routine(1, 2, map);

	printf("Task 2: %u\n", res);

}

// Task 1/2
static void task1(char (*map)[31])
{
	unsigned int res;
	res = aoc3_routine(3, 1, map);
	printf("Task 1: %u\n", res);
}

void aoc3(void)
{
	int i,j;
	char tempc;
	char map[323][31];
	i = j = 0;

	if (NULL == (fp = fopen(fname, "r")))
	{
		printf("File not found..\n");
		exit(0);
	}
	while(EOF != (tempc = fgetc(fp)) && i < 324 && j < 32)
	{
		if('\n' == tempc)
		{
			i++;
			j = 0;
			continue;
		}
		map[i][j] = tempc;
		j++;
	}
	fclose(fp);

	task1(map);
	task2(map);

}
