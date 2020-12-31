#include <stdlib.h>
#include <stdio.h>
#include <math.h>

FILE * fp;

typedef struct {
    int x; int y;
} dir;

typedef struct {
    int x;
    int y;
    dir wp; // Waypoint (task2) / orientation (task 1)
} setup;


// Rotate the waypoint using Cartesian coordinates (rotation matrix's)
void rotate(char c, int n, dir * wp)
{
    int temp;
    if('L' == c || 'R' == c)
    {
    	if('R' == c)
    	{
    		// Scale values for clockwise orientation
    		if(n==90) n = 270;
    		else if(n==270) n = 90;
    	}
    	if(n==90){
    		temp = wp->x;
    	    wp->x = -wp->y;
    	    wp->y = temp;
    	} else if (n==180)
    	{
    		wp->x = -wp->x;
    	    wp->y = -wp->y;
    	} else if (n==270)
    	{
    		temp = -wp->x;
    	    wp->x = wp->y;
    	    wp->y = temp;
    	}
    } else {
    	exit(0);
    }
}

void add_1(char c, int n, setup * stp)
{
    if(c == 'F')
    {
        stp->x += n*stp->wp.x;
        stp->y += n*stp->wp.y;
    }
    else
    {
        switch (c)
        {
            case 'N':
                stp->y += n;
                break;
            case 'E':
                stp->x += n;
                break;
            case 'S':
                stp->y -= n;
                break;
            case 'W':
                stp->x -= n;
                break;
            default:
                exit(0); // Smth wrong..
        }
    }
}


void add_2(char c, int n, setup * stp)
{
    if(c == 'F')
    {
        stp->x += n*stp->wp.x;
        stp->y += n*stp->wp.y;
    }
    else
    {
        switch (c)
        {
            case 'N':
                stp->wp.y += n;
                break;
            case 'E':
                stp->wp.x += n;
                break;
            case 'S':
                stp->wp.y -= n;
                break;
            case 'W':
                stp->wp.x -= n;
                break;
            default:
                exit(0); // Smth wrong..
        }
    }
}

void task1(){

    setup stp;
    char c;
    int n;

    stp.x = stp.y = 0;
    stp.wp.x = 1;
    stp.wp.y = 0;

    while(EOF != fscanf(fp, "%c%d\n", &c, &n))
    {
        if ('L' == c || 'R' == c)
        {
        	rotate(c, n, &stp.wp);
        } else if('F' == c) {
        	add_1(c, n, &stp);
        } else {
        	add_1(c, n, &stp);
        }
    }
    n = abs(stp.x)+abs(stp.y);
    printf("Task 1: %d\n", n);


}

void task2(){

    setup stp;
    char c;
    int n;

    stp.x = stp.y = 0;
    stp.wp.x = 10;
    stp.wp.y = 1;

    while(EOF != fscanf(fp, "%c%d\n", &c, &n))
    {
        if ('L' == c || 'R' == c)
        {
            rotate(c, n, &stp.wp);
        } else if('F' == c) {
        	add_2(c, n, &stp);
        } else {
        	add_2(c, n, &stp);
        }
    }

    n = abs(stp.x)+abs(stp.y);
    printf("Task 2: %d\n", n);

}

// Task 2
void aoc12(void)
{
    if(NULL == ( fp = fopen("inputs/aoc12.txt", "r")))
       {
           printf("File not found..\n");
           exit(0);
       }

    task1();
    rewind(fp);
    task2();
}
