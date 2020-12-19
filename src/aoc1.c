#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE *fp;

#define BUF_LEN_MAX 256
/*  DAY 1  */
// Find numbers x y z from input such that x+y+z=2020
void aoc1(void)
{

	int i, j, k, c, n1, n2, n3;
	int aoc[BUF_LEN_MAX];

	if (NULL == (fp = fopen("inputs/aoc1.txt","r")))
	{
		printf("File not found..\n");
		exit(0);
	}

	c = 0;
	n1 = n2 = n3 = 0;

	// Read input to buffer
	while(EOF != fscanf(fp, "%d", aoc + c) && c++ < BUF_LEN_MAX);

	fclose(fp);

	for(i = 0; i < c ; i++)
	{
		for(j = i ; j < c ; j++)
		{
			for(k = j; k < c ; k++)
			{
				if(2020 == aoc[k] + aoc[i] + aoc[j])
				{
					n1 = aoc[i];
					n2 = aoc[j];
					n3 = aoc[k];
					goto end;
				}
			}
		}
	}

end:
	if(n1 && n2 && n3) printf("Numbers: (%d,%d,%d), product: %d ", n1,n2,n3, n1*n2*n3);
	else printf("No numbers found..");
}
