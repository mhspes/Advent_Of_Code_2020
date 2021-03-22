#include <stdio.h>
#include <stdlib.h>


static char fname[] = "inputs/aoc1.txt";
static FILE * fp;

#define BUF_LEN_MAX 256

int aoc[BUF_LEN_MAX];
int data_len;

// Task 2/2
static void task2()
{
	int i, j, k, n1, n2, n3;

	n1 = n2 = n3 = 0;

	for(i = 0; i < data_len ; i++)
	{
		for(j = i ; j < data_len ; j++)
		{
			for(k = j; k < data_len ; k++)
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
	if(n1 && n2 && n3) printf("Numbers: (%d,%d,%d), product: %d\n", n1,n2,n3, n1*n2*n3);
}

// Task 1/2
static void task1()
{
	int i, j, n1, n2;

	n1 = n2 = 0;

	for(i = 0; i < data_len ; i++)
	{
		for(j = i ; j < data_len ; j++)
		{
			if(2020 == aoc[i] + aoc[j])
			{
				n1 = aoc[i];
				n2 = aoc[j];
				goto end;
			}
		}
	}

end:
	if(n1 && n2) printf("Numbers: (%d,%d), product: %d\n", n1,n2, n1*n2);
}

void aoc1()
{

	data_len = 0;

	if (NULL == (fp = fopen(fname, "r")))
	{
		printf("File not found..\n");
		exit(0);
	}

	// Read the input to buffer
	while(EOF != fscanf(fp, "%d", aoc + data_len) && data_len++ < BUF_LEN_MAX);
	fclose(fp);

	task1();
	task2();

}
