#include <stdlib.h>
#include <stdio.h>
#include <string.h>

FILE * fp;

// For sorting the integer sequence
static void bubblesort(int * arr, int n)
{
    int i, j, temp;
    for (i = 0; i < n-1; i++){
        for (j = 0; j < n-i-1; j++){
            if (*(arr+j) > *(arr+j+1))
            {
                temp = *(arr+j+1);
                *(arr+j+1) = *(arr+j);
                *(arr+j) = temp;
            }
        }
    }
}

void aoc10(void)
{

    int i, len, arr[200];
    unsigned long long arr2[200]; // List for amount of the arrangments

    memset(arr, 0, 200*sizeof(int));
    memset(arr2, 0, 200*sizeof(unsigned long long));
    arr2[0] = 1;

    if(NULL == ( fp = fopen("inputs/aoc10.txt", "r")))
    {
        printf("File not found..\n");
        exit(0);
    }

    len = 0;
    arr[len++]=0;

    while(EOF != fscanf(fp, "%d", arr+len++));
    fclose(fp);

    bubblesort(arr, len);

    len++;
    arr[len-1] = arr[len-2]+3; // The last value

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

    printf("Arrangments: %llu \n"arr2[len-1]);

}
