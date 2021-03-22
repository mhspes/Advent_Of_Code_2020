#include <stdio.h>
#include <stdlib.h>

static char fname[] = "inputs/aoc2.txt";

static FILE * fp;


// Task 2/2
static void task2()
{
	int b1, b2, ind, valid;
	int bool;
	char c, tempc;
	valid = 0;

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
	printf("Valid passwords: %d\n", valid);
}

// Task 1/2
static void task1()
{
	int b1, b2, ind, valid;
	char c, tempc;
	valid = 0;

	// Assuming the input is always valid and b1<b2
	while(EOF != fscanf(fp, "%d-%d %c: ", &b1, &b2, &c))
	{
		ind = 0;
		while('\n' != (tempc = fgetc(fp)) && EOF != tempc)
			if(tempc == c) ind++;
		if(b1 <= ind && ind <= b2)valid++;
	}
	printf("Valid passwords: %d\n", valid);

}

void aoc2()
{

	if (NULL == (fp = fopen(fname, "r")))
	{
		printf("File not found..\n");
		exit(0);
	}

	task1();
	rewind(fp);
	task2();
	fclose(fp);

}
