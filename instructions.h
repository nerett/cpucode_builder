#ifndef INSTRUCTIONS_H_INCLUDED
#define	INSTRUCTIONS_H_INCLUDED


const char instruction_lenght[] =
{
	1, //HLT
	1, //START
	2, //PUSH
	1, //POP
	1, //ADD
	1, //SUB
	1, //MUL
	1, //DIV
	1, //OUT
	1 //NONE
};

enum instruction_type
{
	HLT = 0,
	START = 1,
	PUSH = 2,
	POP = 3,
	ADD = 4,
	SUB = 5,
	MUL = 6,
	DIV = 7,
	OUT = 8,
	NONE = 9
};


#endif
