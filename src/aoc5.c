#include <stdlib.h>
#include <stdio.h>

static char fname[] = "inputs/aoc5.txt";
static FILE *fp;


#define MAX_SIZE 900

static int seats[MAX_SIZE];
static int len;

// Compare func for qsort
static int compare(void const *a, void const *b)
{
	return *(int*)a - *(int*)b;
}

// Task 2/2
static void task2()
{
    // Sort input & process by finding diff. of 2
    qsort(seats, MAX_SIZE, sizeof(int), compare);

    for(; 0 < len; len--)
        if(seats[len]-seats[len-1]==2)
        {
            printf("Seat: %d\n", seats[len]-1);
            return;
        }
}

// Task 1/2
// Binary search -kind of algorithm
static void task1()
{
    char c;
    int row, col;
    int temp1, temp2, max;
    row = col = 0;
    temp1 = 128;
    temp2 = 8;
    max = len = 0;

    if(NULL == ( fp = fopen(fname, "r")))
    {
        printf("File not found..\n");
        exit(0);
    }

    while(EOF != (c = fgetc(fp))){
        if(c == 'B'){
            temp1 >>= 1;
            row += temp1;
        } else if (c == 'F'){
            temp1 >>= 1;
        } else if (c == 'R'){
            temp2 >>= 1;
            col += temp2;
        } else if (c == 'L'){
            temp2 >>= 1;
        } else if (c == '\n'){
            temp1 = row*8+col;
            seats[len++]= temp1;
            if(max < temp1) max = temp1;
            row = col = 0;
            temp1 = 128;
            temp2 = 8;
        }
    }

    fclose(fp);

    printf("Largest seat ID: %d\n", max);
}

void aoc5()
{
	task1();
	task2();
}
