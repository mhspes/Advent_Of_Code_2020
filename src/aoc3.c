#include <stdlib.h>
#include <stdio.h>

FILE *fp;

/*  DAY 3  */
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

void aoc3(void)
{
	int i,j;
	unsigned long prod;
	char tempc;
	char map[323][31];
	i = j = 0;
	prod = 1;

	if (NULL == (fp = fopen("inputs/aoc3.txt", "r")))
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
	prod *= aoc3_routine(1, 1, map);
	prod *= aoc3_routine(3, 1, map);
	prod *= aoc3_routine(5, 1, map);
	prod *= aoc3_routine(7, 1, map);
	prod *= aoc3_routine(1, 2, map);

	printf("Product of #:s of trees: %lu\n", prod);
}
