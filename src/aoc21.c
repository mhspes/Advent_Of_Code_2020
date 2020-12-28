#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>

FILE *fp;

/*  DAY 21  */

#define ING_MAX 250
#define AL_MAX 10

typedef struct{
	char name[10];
	int num;
	uint8_t ingredients[ING_MAX];
} allergen;

static void add_ingr(void * dest, void * src)
{
    int i;
    for(i = 0; i < ING_MAX; i++)
        *((uint8_t*)dest+i) += *((uint8_t*)src+i);
}

void aoc21()
{
    char c, temp[10];
    int i, j, sum;
    uint8_t ind_num_temp[ING_MAX], ind_num[ING_MAX];
    allergen al[AL_MAX];
    char keywords[ING_MAX][10];

    if(NULL == ( fp = fopen("inputs/aoc21.txt", "r")))
    {
        printf("File not found.\n");
        exit(0);
    }

    memset(al, 0, sizeof(allergen)*AL_MAX);
    memset(keywords, 0, sizeof(keywords));
    memset(ind_num, 0, sizeof(ind_num));
    memset(ind_num_temp, 0, sizeof(ind_num_temp));

    i = sum = 0;
    // Find the number of keywords (ingredients) and fill the list of allergens & ingredients
    while(EOF != (c = getc(fp)))
    {
    	if(' ' == c){
    		// Ingredient read
    		// Add, check if not listed
    		temp[i] = '\0';
    		i=0;
    		while(i < ING_MAX)
    		{
    			if(!strcmp(keywords[i], temp))
    			{
    				ind_num_temp[i]++;
    				break;
    			}
    			if(keywords[i][0] == 0)
    			{
    				strcpy(keywords[i], temp); // Not listed, add
    				ind_num_temp[i]++;
    				break;
    			}
    			i++;
    		}
    		i=0;
    	}
    	else if('\n' == c){
    		// Skip
    	}
    	else if('(' == c){
    		// All ingredients read, process allergens
    		i = 0;
    		while(' ' != (c = getc(fp))); // Skip nonnecessary
    		while('\n' != (c = getc(fp)))
    		{
    			if(',' == c || ')' == c)
    			{
    				// An allergen read
    				temp[i] = '\0';
    				i = 0;
    				while(i <= AL_MAX)
    				{
    					if(i == AL_MAX - 1){
    						exit(0); // Something's wrong..
    					}
    					if(!strcmp(al[i].name, temp))
    					{
    						add_ingr(&al[i].ingredients, ind_num_temp);
    						al[i].num++;
    						break;
    					}
    					if(al[i].name[0] == 0){
    						strcpy(&al[i].name[0], temp); // New allergen, add to list
    						add_ingr(&al[i].ingredients, ind_num_temp);
    						al[i].num++;
    						break;
    					}
    					i++;
    				}
    				i = 0;
    			} else if (' ' ==c || ')'==c) {
    				// Skip
    			} else {
    			temp[i++] = c;
    			}
    		}
    		// Single line processed, set buffers..
    		add_ingr(ind_num, ind_num_temp);
    		memset(ind_num_temp, 0, sizeof(ind_num_temp));
    	}
    	else {
    		temp[i++] = c;
    	}
    }

    // Print possible ingredients, remove from list of total sum
    for(j = 0 ; j < AL_MAX; j++)
    {
    	if('\0' != al[j].name[0])
    	{
    		printf("For %s:\n", al[j].name);
    		for(i = 0; i < ING_MAX; i++)
    		{
    			if(al[j].num == al[j].ingredients[i] )
    			{
    				printf("%s ", keywords[i]);
    				ind_num[i] = 0;
    			}
    		}
    		printf("\n");
    	}
    }
    // Compute & print sum
    for(j = 0; j < ING_MAX; j++)
        sum += ind_num[j];

    printf("Sum: %d\n", sum);
}
