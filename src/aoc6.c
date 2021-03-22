#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char fname[] = "inputs/aoc6.txt";
static FILE *fp;


// Return number of bits of an integer
int numberofbits(unsigned int num)
{
	int i, ret;
	ret = 0;
	for(i = 0; i < 26; i++){
		ret += num & 1;
		num >>= 1;
	}
	return ret;
}

// Task 2/2
// Use bit mapping for encountered letters
// Cumulatively AND to indicate incidence on all lines
static void task2()
{
    char c, c_prev;
    int bool_c[10], i, sum, temp_bool;

    memset(bool_c, 0, 10*sizeof(int));
    sum = i = 0;
    c_prev = ' ';

    while(1)
    {
    	c = fgetc(fp);

    	if(c != EOF && c != '\n')
    	{
    		// Bit flagging for encountered letters ( 0..26)
    		temp_bool = 1 << (c - 'a');
    		if(!(bool_c[i] & temp_bool)) bool_c[i] += temp_bool;
    		c_prev = c;
    	}
    	else if (c == '\n')
        {
    		i++;
            if(c_prev =='\n')
            {
            	i -=2;
            	temp_bool = bool_c[i];
            	for(; 0 < i; i--)
            	{
            		bool_c[i] = 0; // Clear used indicators
            		temp_bool = temp_bool & bool_c[i-1]; // Cumulative AND
            	}
            	bool_c[0] = 0;
            	// temp_bool = bits i.e. letters found in each line of a set
            	sum += numberofbits((unsigned int)temp_bool);
            	i = 0;
            }
            c_prev = c;
        }
    	else if (EOF == c)
    	{
    		// Process last set
    		i-=2;
    		temp_bool = bool_c[i];
    		for(; 0 < i; i--)
    			temp_bool = temp_bool & bool_c[i-1];
    		sum += numberofbits((unsigned int)temp_bool);
        	break;
        }
    }
    printf("Task 2 sum: %d\n", sum);

}

// Task 1/2
static void task1()
{
    char c, c_prev;
    int bool_c, temp, sum;

    sum = bool_c = 0;
    c_prev = ' ';

    while(1)
    {
    	c = fgetc(fp);

    	if(c != EOF && c != '\n')
    	{
    		// Bit flagging for encountered letters ( 0..26)
    		temp = 1 << (c - 'a');
    		if(!(bool_c & temp)) bool_c += temp;
    		c_prev = c;
    	}
    	else if (c == '\n')
        {
    		if(c_prev =='\n')
    		{
    			sum += numberofbits((unsigned int)bool_c);
    			bool_c = 0;
    		}
    		c_prev = c;
        }
    	else if (EOF == c)
    	{
    		sum += numberofbits((unsigned int)bool_c);
        	break;
        }
    }
    printf("Task 1 sum: %d\n", sum);

}

void aoc6()
{
    if(NULL == ( fp = fopen(fname, "r")))
    {
        printf("File not found..\n");
        exit(0);
    }

	task1();

	rewind(fp);

	task2();
}
