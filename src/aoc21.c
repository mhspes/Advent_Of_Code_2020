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

static void add_ingr(allergen * al, uint8_t val[ING_MAX])
{
	int i;
	for(i = 0; i < ING_MAX; i++)
		al->ingredients[i] += val[i];
}


void aoc21()
{
    char c, temp[10];
    int i, sum;
    uint8_t ind_num[ING_MAX];
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

    i = sum = 0;
    // Find the number of keywords (ingredients) and accumulate to a allergen data struct

    while(EOF != (c = getc(fp)))
    {
    	if(' ' == c){
    		// Ingredient read
    		// check if not listed --> add
    		temp[i] = '\0';
    		i=0;
    		while(i < ING_MAX)
    		{
    			if(!strcmp(keywords[i], temp))
    			{
    				ind_num[i]++;
    				i++;
    				break;
    			}
    			if(keywords[i][0] == 0)
    			{
    				strcpy(keywords[i], temp); // Add to the list
    				ind_num[i]++;
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
    		while(' ' != (c = getc(fp)));
    		while('\n' != (c = getc(fp)))
    		{
    			if(',' == c || ')' == c){
    				// allergen read
    				temp[i] = '\0';
    				i = 0;
    				while(i <= AL_MAX)
    				{
    					if(i == AL_MAX - 1){
    						printf("Buffer too small!\n");
    						exit(0);
    					}
    					if(!strcmp(al[i].name, temp))
    					{
    						add_ingr(&al[i], ind_num);
    						al[i].num++;
    						break;
    					}
    					if(al[i].name[0] == 0){
    						strcpy(&al[i].name[0], temp);
    						add_ingr(&al[i], ind_num);
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
    		memset(ind_num, 0, sizeof(ind_num));
    	}
    	else {
    		temp[i++] = c;
    	}
    }
    // Iterate 2
    int j, k;
    int len1;
    len1 = 0;
    int wrong_ind[AL_MAX];
    memset(wrong_ind, 0, AL_MAX*sizeof(int));
    for(j = 0 ; j < AL_MAX; j++){
    	if('\0' != al[j].name[0]){
    		printf("For: %s \n", al[j].name);
    		for(i = 0; i < ING_MAX ; i++)
    		{
    			if(al[j].num == al[j].ingredients[i] )
    				{
    				printf("Ing: %s, removing \n", keywords[i]);
    				for(k=0; k < AL_MAX; k++){
    					if(wrong_ind[k]==i){
    						wrong_ind[j] = i;
    					}
    				}
    				// Check if not listed alrdy..
    				len1++;
    				}
    		}
    		}

    	printf("\n");
    }
    sum=0;
    // Remove allergen
    for(j = 0; j < len1; j++){
    	memset(keywords[wrong_ind[j]],0, 10);
    }

    // Read input again now ignoring the allergens..
    while(EOF != (c = getc(fp)))
    {
    	if(' ' == c){
    		// Ingredient read
    		// check if not listed --> add
    		temp[i] = '\0';
    		i=0;
    		while(i < ING_MAX)
    		{
    			if(!strcmp(keywords[i], temp))
    			{
    				sum++;
    				break;
    			}
    			i++;
    		}
    		i=0;
    	}
    	else if('(' == c){
    		while('\n' != (c = getc(fp)));
    		// Ignore rest (allergens)
    	} else {
    		temp[i++] = c;
    	}

    }

    printf("SUM: %d\n", sum);

}
