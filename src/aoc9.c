#include <stdlib.h>
#include <stdio.h>
#include <string.h>

FILE * fp;

// Validate the by finding a+b=number from 25 previous val's in the list
// ret 1 for valid and 0 for invalid number
static int validate(unsigned long * test_val, unsigned long * list)
{
    int i,j;
    for(i = 0; i < 25 ; i++)
        for(j = i; j < 25; j++)
            if(*test_val == list[i]+list[j]) return 1;

    return 0;
}

void aoc9(void){

    unsigned long list[1000];
    unsigned long  * ptr;
    int a, b, ind;
    unsigned long temp_sum, min, max;
    ptr = &list[0];
    a = 1;
    temp_sum = ind = 0;
    memset(list, 0, 1000*sizeof(unsigned long));

    if(NULL == ( fp = fopen("inputs/aoc9.txt", "r")))
    {
        printf("File not found..\n");
        exit(0);
    }

    // Read the preamble
    while(ptr != &list[25])
        fscanf(fp, "%lu", ptr++);

    while(EOF != fscanf(fp, "%lu", ptr))
    {
        a = validate(ptr, ptr-25);
        if(!a)
        {
            printf("Invalid number: %lu\n", *ptr);
            break;
        }
        ptr++;
    }
    fclose(fp);

    // Find (ind) sequential numbers summing to the invalid number
    for(a=0; list+a < ptr; a++)
    {
        while(temp_sum <= *ptr)
        {
            temp_sum += list[a+ind];
            ind++;
            if(temp_sum == *ptr) goto end;
        }
        ind = temp_sum = 0;
    }

    // Find the min, max of the list, compute sum
end:
    min = *ptr;
    max = b = 0;
    while(b < ind){
        if(list[a+b] < min) min = list[a+b];
        if(list[a+b] > max) max = list[a+b];
        b++;
    }

printf("Max: %lu, min: %lu, sum: %lu \n", max, min, max+min);

}
