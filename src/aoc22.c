
/******************************************************************************\
 * Name        : aocc.c
 * Author      : Your name
 * Copyright   : Your copyright notice
 * Description : Hello World in C
\******************************************************************************/


#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "math.h"
#include <stdint.h>

#define STATE_MAX 10000

int counter;
uint8_t states1[STATE_MAX][50];
uint8_t states2[STATE_MAX][50];

uint8_t l1[50] = {25, 37, 35, 16, 9, 26, 17, 5, 47, 32, 11, 43, 40, 15, 7, 19, 36, 20, 50, 3, 21, 34, 44, 18, 22};
uint8_t l2[50] = {12, 1, 27, 41, 4, 39, 13, 29, 38, 2, 33, 28, 10, 6, 24, 31, 42, 8, 23, 45, 46, 48, 49, 30, 14};

int compare(uint8_t * l_sample, int len, uint8_t (*l_cmp)[50]){
    int i, j;

    i = 0;
    while(l_cmp[i][0] != 0)
    {
        j = 0;
        while(j != len)
        {
            if(l_sample[j] != l_cmp[i][j]){
                break;
            }
            if(j == len-1 && l_cmp[i][j+1] == 0){
                // All read, no diffs found = equal. Stop
                printf("Loop found!\n");
                return 1;
            }
            j++;
        }
        i++;
    }
    // No repeating state found, return 0
    return 0;
}


void SwapShift(uint8_t * dest, uint8_t * src, uint8_t * len_d, uint8_t * len_s)
{
    int i;
    uint8_t temp1 = *dest;
    for(i = 1; i < *len_d; i++){
        dest[i-1] = dest[i];
    }
    dest[*len_d-1] = temp1;
    dest[*len_d] = src[0];
    for(i = 1; i < *len_s; i++){
        src[i-1] = src[i];
    }
    src[*len_s-1] = 0;
    (*len_d)++;
    (*len_s)--;
}

int recursiveCombat(uint8_t * l1, uint8_t * l2, uint8_t len1, uint8_t len2)
{
	uint8_t l1_temp[50];
	uint8_t l2_temp[50];
    int res;
    memcpy(l1_temp, l1, len1);
    memcpy(l2_temp, l2, len2);
    memset(l1_temp+len1, 0, 50-len1);
    memset(l2_temp+len2, 0, 50-len2);


    while(len1 && len2)
    {
        // Check if repating state occurs..
        res = compare(l1_temp, len1, states1);
        if(res == 1) return 1;

        res = compare(l2_temp, len2, states2);
        if(res == 1) return 1;
        // Save new states
        memcpy(states1[counter], l1_temp, len1);
        memcpy(states2[counter], l2_temp, len2);
        counter++;
        if(counter > STATE_MAX){
            printf("Counter too large..\n");
            counter = 0;
        }
        if(len1-1 >= l1_temp[0] && len2-1 >= l2_temp[0])
        {
            res = recursiveCombat(&l1_temp[1], &l2_temp[1], len1-1, len2-1);
            if(res)
                SwapShift(&l1_temp[1], &l2_temp[1], &len1, &len2);
            else
                SwapShift(&l2_temp[1], &l1_temp[1], &len2, &len1);
        } else {
            if(l1_temp[0] > l2_temp[0])
                SwapShift(&l1_temp[0], &l2_temp[0], &len1, &len2);
            else
                SwapShift(&l2_temp[0], &l1_temp[0], &len2, &len1);
        }
    }
    if(len1 == 50){
        memcpy(l1, l1_temp, len1);
        return 1;
    }
    if(len2 == 50){
        memcpy(l2, l2_temp, len2);
        return 0;
    }
    if(len1) return 1;
    else return 0;

}

void aoc22(void)
{

	memset(states1, 0, sizeof(states1));
	memset(states2, 0, sizeof(states2));
    int it, ret;
    uint32_t sum;
    uint8_t len1, len2;
    len1 = len2 = 25;
    counter = sum = 0;

    ret = recursiveCombat(l1, l2, len1, len2);

    if(1 == ret){
        len1 = 50;
        for(it = 0; it < len1; it++){
            sum += l1[it]*(len1-it);
        }
    } else {
        len2 = 50;
        for(it = 0; it < len2; it++){
            sum += l2[it]*(len2-it);
        }
    }
    printf("The sum: %u\n", sum);

}
