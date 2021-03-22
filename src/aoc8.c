#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>

static char fname[] = "inputs/aoc8.txt";
static FILE * fp;

// Struct for instructions
typedef struct
{
	char op[3];
	int arg;
	int8_t bool;		// To check if been into this address
	int8_t bool_chk;
} instr;

instr program[1000];
unsigned int pc;		// Program Counter
unsigned int codesize;

// Task 2/2
static void task2()
{
	int count, ind_test, flag;

	count = flag = pc = ind_test = 0;

	// Find the operation to be changed, bruteforce approach
	while(1)
	{
		if(program[pc].bool)
		{
			for(pc = 0; pc <= codesize; pc++)program[pc].bool = 0;
			pc = ind_test= flag = count = 0;
			continue;
		}
		if(pc == codesize) // End reached
		{
			printf("End reached with #%d changed.\n", ind_test);
			if(!strcmp(program[ind_test].op,"nop")) strcpy(program[ind_test].op, "jmp");
			else strcpy(program[ind_test].op, "nop");
			break;
		}
		program[pc].bool = 1;
		if(!strcmp(program[pc].op,"nop")){
			if(!flag && !program[pc].bool_chk){
				program[pc].bool_chk = 1;
				ind_test = pc;
				flag = 1;
				pc += program[pc].arg;
			} else {
			pc++;
			}
		} else if (!strcmp(program[pc].op,"acc")) {
			pc++;
		} else if (!strcmp(program[pc].op,"jmp")) {
			if(!flag && !program[pc].bool_chk){
				program[pc].bool_chk = 1;
				ind_test= pc;
				flag = 1;
				pc++;
			} else {
			pc += program[pc].arg;
			}
		} else {
			exit(0);
		}
	}

	for(pc = 0; pc <= codesize; pc++)program[pc].bool = 0;
	pc = 0;
	while(1)
	{
		if(pc == codesize)
		{
			printf("End reached, sum: %d\n", count);
			break;
		}
		if(!strcmp(program[pc].op,"nop"))
		{
			pc++;
		} else if (!strcmp(program[pc].op,"acc"))
		{
			count += program[pc].arg;
			pc++;
		} else if (!strcmp(program[pc].op,"jmp"))
		{
			pc += program[pc].arg;
		}

	}

}

// Task 1/2
static void task1()
{
	int count;
	count = pc = 0;

	while(1)
	{
		if(program[pc].bool)
		{
			printf("Loop found, sum: %d\n", count);
			break;
		}
		program[pc].bool = 1;
		if(!strcmp(program[pc].op,"nop"))
		{
			pc++;
		} else if (!strcmp(program[pc].op,"acc"))
		{
			count += program[pc].arg;
			pc++;
		} else if (!strcmp(program[pc].op,"jmp"))
		{
			pc += program[pc].arg;
		} else {
			exit(0);
		}
	}
}

void aoc8()
{

	memset(program, 0, sizeof(instr)*1000);
	if(NULL == ( fp = fopen(fname, "r")))
	    {
	        printf("File not found..\n");
	        exit(0);
	    }
	// Read the input into the program struct
	while(EOF != fscanf(fp,"%s %d\n",program[pc].op, &program[pc].arg) )pc++;
	fclose(fp);

	codesize = pc;

	task1();
	// Reset flags for second task
	for(pc = 0; pc <= codesize; pc++)program[pc].bool = 0;
	task2();

}
