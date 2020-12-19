#include <stdlib.h>
#include <stdio.h>

FILE *fp;

/*  DAY 5  */
//Bubblesort for array
void bubblesort(int * arr, int n)
{
    int i, j, temp;
    for (i = 0; i < n-1; i++){
        for (j = 0; j < n-i-1; j++){
            if (*(arr+j)>*(arr+j+1))
            {
                temp = *(arr+j+1);
                *(arr+j+1) = *(arr+j);
                *(arr+j) = temp;
            }
        }
    }
}

/*  DAY 5  */
// Find the seat ID's of boarding passes
void aoc5()
{
    char c;
    int row, col;
    int temp1, temp2, max, count;
    int res[900];
    row = col = 0;
    temp1 = 128;
    temp2 = 8;
    max= count = 0;

    if(NULL == ( fp = fopen("inputs/aoc5.txt", "r")))
    {
        printf("File not found.\n");
        exit(0);
    }
    // Read file input
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
            res[count++]= temp1;
            if(max < temp1) max = temp1;
            row = col = 0;
            temp1 = 128;
            temp2 = 8;
        }
    }
    // Sort & process
    bubblesort(res, count);
    for(; 0 < count; count--)
    {
        if(res[count]-res[count-1]==2)
        {
            temp1 = res[count]-1;
            printf("Seat: %d\n", temp1);
        }
    }
    printf("LARGEST: %d\n", max);
}
