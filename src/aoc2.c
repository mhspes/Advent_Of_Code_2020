#include <stdio.h>
#include <stdlib.h>

FILE *fp;
/*  DAY 2  */
// Find amount of valid passwords
// char c must be either on b1:th OR b2:th letter
void aoc2(void)
{
	int b1,b2, ind, valid;
	int bool;
	char c, tempc;
	valid = 0;

	if (NULL == (fp = fopen("inputs/aoc2.txt", "r")))
	{
		printf("File not found..\n");
		exit(0);
	}
	// Assuming the input is always valid and b1<b2
	while(EOF != fscanf(fp, "%d-%d %c: ", &b1, &b2, &c))
	{
		ind = bool = 0;
		while('\n' != (tempc = fgetc(fp)) && EOF != tempc)
		{
			if(++ind == b1)
				if(tempc == c) bool++;
			if(ind == b2)
				if(tempc == c) bool++;
		}
		if(bool == 1)valid++;
	}
	fclose(fp);
	printf("Valid passwords: %d\n", valid);
}
