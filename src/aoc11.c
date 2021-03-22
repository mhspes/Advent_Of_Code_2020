#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char fname[] = "inputs/aoc11.txt";
static FILE * fp;

char seats_1[100][100]; // Seating before & after the change
char seats_2[100][100];

// Check amout of occupied/free seats next to
// Return 0 if amount exceeded, 1 otherwise
int check(char (*ptr)[100], int x, int y, char c, int amount)
{

    int i,j, val;
    val = 0;
    for(i = -1; i <= 1; i++){
        for(j = -1; j <=1; j++){
            if(i==0 && j==0)
            	continue;
            if(ptr[x+i][y+j] == c)
            	val++;
            if(val == amount)
            	return 0;
        }
    }
    return 1;
}

// Task 1/2
static void task1()
{

    char c;
    int i, j, flag, counter;

    if(NULL == ( fp = fopen(fname, "r")))
    {
        printf("File not found..\n");
        exit(0);
    }
    // Read the data + insert padding
    i = j = 1;
    memset(seats_1[0],'.',100);
    memset(seats_1[99],'.',100);
    seats_1[1][0] = seats_1[98][99] = '.';
    while(EOF != (c = fgetc(fp)))
    {
        if('\n' == c){
            seats_1[i][99] = '.';
            i++;
            seats_1[i][0] = '.';
            j=1;
        } else {
            seats_1[i][j++] = c;
        }
    }
    fclose(fp);
    memcpy(seats_2, seats_1, sizeof(seats_1));

    // Iterate the changes in the seat arrangements
    do
    {
    	flag = 0; // Set the flag if a change occurs
        for(i=1; i < 99; i++)
        {
            for(j=1; j < 99; j++)
            {
            	if(seats_1[i][j]=='L')
            		if(check(seats_1, i, j, '#', 1))
            		{
            			seats_2[i][j]='#';
            			flag = 1;
            		}
            	if(seats_1[i][j]=='#')
            		if(!check(seats_1, i, j, '#', 4))
            		{
            			seats_2[i][j]='L';
            			flag = 1;
            		}
            }
        }
        memcpy(seats_1, seats_2, sizeof(seats_2));
    } while (flag);

counter = 0;

    for(i=0; i < 100; i++)
        for(j=0; j < 100; j++)
            if('#' == seats_2[i][j])
            	counter++;

printf("Occupied seats: %d", counter);

}
void aoc11()
{
	task1();
}
