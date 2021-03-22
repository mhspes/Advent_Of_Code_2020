#include <stdlib.h>
#include <stdio.h>
#include <string.h>

static char fname[] = "inputs/aoc10.txt";
static FILE * fp;

int arr[200];
long long int arr2[200]; // Amount of arrangements till the i:th charger
int len;

static int compare(void const *a, void const *b)
{
	return *(int*)a - *(int*)b;
}

// Task 2/2
static void task2(void)
{
    int i;
    arr2[0] = 1;

    // Iterate the list, compute the amount of arrangments + accumulate
    for(i = 0; i <= len; i++)
    {
    	// Next 3 steps higher, no other arrangments
        if(arr[i+1]-arr[i]==3)
        {
            arr2[i+1]=arr2[i];
            continue;
        } else if (arr[i+1]-arr[i]==1)
        {
            arr2[1+i] += arr2[i];
            // Check for sub arrangements..
            if(arr[i+2]-arr[i]==2)
            {
                arr2[i+2] += arr2[i];
                if(arr[i+3]-arr[i]==3)
                    arr2[i+3] += arr2[i];
            }
            else if(arr[i+2]-arr[i]==3){
                arr2[i+2]=arr[i];
            }
        }

    }
    printf("Arrangments: %I64d \n", arr2[len-1]);

}

// Task 1/2
static void task1(void)
{
	int i, n1, n3;
    arr[0]= n1 = n3 = 0;
    len = 1;

    while(EOF != fscanf(fp, "%d", arr+len++));
    fclose(fp);

    // Sort by the voltages
    qsort(arr, len-1, sizeof(int), compare);
    arr[len-1] = arr[len-2]+3; // The last value

    // Count the amount of diffs.
    for(i = 1; i < len; i++)
    {
    	if(arr[i] - arr[i-1] == 1) n1++;
    	else if (arr[i] - arr[i-1] == 3) n3++;
    }

    printf("%d\n", n1*n3);

}

void aoc10()
{
    memset(arr, 0, 200*sizeof(int));
    memset(arr2, 0, 200*sizeof(long long int));

    if(NULL == ( fp = fopen(fname, "r")))
    {
        printf("File not found..\n");
        exit(0);
    }

	task1();
	task2();
}
