/*
 ============================================================================
 Name        : AoC2020.c
 Author      : Mikko Pesonen
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

#define RUN_TESTS 0

extern void aoc1(void);
extern void aoc2(void);
extern void aoc3(void);
extern void aoc4(void);
extern void aoc5(void);
extern void aoc6(void);
extern void aoc7(void);
extern void aoc8(void);
extern void aoc9(void);
extern void aoc10(void);
extern void aoc11(void);
extern void aoc12(void);
extern void aoc13(void);
extern void aoc14(void);
extern void aoc15(void);
extern void aoc17(void);
extern void aoc20(void);
extern void aoc21(void);
extern void aoc22(void);

int main(void)
{

#if RUN_TESTS
	aoc1();
	aoc2();
	aoc3();
	aoc4();
	aoc5();
	aoc6();
	aoc8();
	aoc9();
	aoc10();
	aoc11();
	aoc12();
	aoc13();
	aoc14();
	aoc15();
	aoc17();
	aoc20();
	aoc21();
	aoc22();
#endif
	aoc22();
	return EXIT_SUCCESS;
}
