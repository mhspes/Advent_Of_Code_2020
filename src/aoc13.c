#include <stdlib.h>
#include <stdio.h>

int dpt = 1000053;

long long int schedul[9] = {19, 37, 523, 13, 23, 29, 547, 41, 17};
long long int ind[9] = {0, 13, 19, 37, 42, 48, 50, 60, 67}; // Input hardcoded.. x's forbidden

int LEN = sizeof(schedul)/sizeof(int);

// Extended Euclidean algorithm for finding the inverse of N/n_i
// Does not return the gcd, not needed here
void gcdExtended(long long int a, long long int b, long long int *x, long long int *y)
{
    if (a == 0) {
        *x = 0;
        *y = 1;
        return;
    }

    long long int x1, y1;
    gcdExtended(b%a, a, &x1, &y1);
    *x = y1 - (b/a) * x1;
    *y = x1;

    return;
}

/* For part 2 - straight-forward usage of Chinese-Remainder-Theorem
 */
void part2()
{
	int i;
	long long int n_i[9], inv_n_i[9];
	long long int N, res, val;

	res = 0;
	N = 1;
	// Compute N = n1*n2*..*ni
	for(i=0; i < LEN ; i++){
		N *= schedul[i];
	}
	/* Compute Ni=N/ni, the inverse of Ni mod ni
	*  and iterate the result     */
	for(i=0; i < LEN ; i++)
	{
		n_i[i] = N/schedul[i]; // Note '__divdi3' might require to be linked manually for 64-bit div..
		gcdExtended(n_i[i], schedul[i], &inv_n_i[i], &val);
		res += -ind[i]*n_i[i]*inv_n_i[i];
	}
	// Reduce mod N
	res %= N;

	printf("Part2: %I64d\n", res);
}

void part1()
{
	int min, temp, i, ind;
	min = dpt;
	ind = 0;

	for(i = 0; i < LEN; i++)
	{
		temp = schedul[i] - (dpt % schedul[i]); // Note 64-bit int may require gcc __divdi3 linking to work..
		if(temp < min){
			min = temp;
			ind = i;
		}
	}
	printf("Part1: %I64d\n", min*schedul[ind]);
}

void aoc13(){

	part1();
	part2();
}
