#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE *fp;

/*  DAY 6  */

int numberofbits(int num){
	int i,ret;
	ret = 0;
	for(i=0; i < 26; i++){
		ret += num & 1;
		num >>= 1;
	}
	return ret;
}

void aoc6(){
    char c, c_prev;
    int bool_c[10],i , temp, sum, temp_bool;
    sum = i = 0;
    memset(bool_c, 0, 10*4);
    if(NULL == ( fp = fopen("inputs/aoc6.txt", "r")))
    {
        printf("File not found..\n");
        exit(0);
    }
    c_prev = ' ';
    while(1)
    {
    	c = fgetc(fp);
    	if(c != EOF && c != '\n')
    	{
    		temp = 1 << (c - 'a');
    		if(!(bool_c[i] & temp)) bool_c[i] += temp;
    		c_prev = c;
    	}
    	else if (c == '\n')
        {
    		i++;
            if(c_prev =='\n'){
            	i -=2;
            	temp_bool = bool_c[i];
            	for(; 0 < i; i--)
            	{
            		bool_c[i] = 0;
            		temp_bool = temp_bool & bool_c[i-1];
            	}
            	bool_c[0] = 0;
            	temp = numberofbits(temp_bool);
            	sum += temp;
            	i = 0;
            }
            c_prev = c;
        }
    	else if (EOF == c)
    	{
    		i-=2;
    		temp_bool = bool_c[i];
    		for(; 0 < i; i--)
    			temp_bool = temp_bool & bool_c[i-1];
    		temp = numberofbits(temp_bool);
        	sum += temp;
        	break;
        }
    }
    printf("Sum: %d\n",sum);

}
