#ifndef INSTRUCTIONS_H_INCLUDED
#define	INSTRUCTIONS_H_INCLUDED


/*--------------------------ENUM----------------------------------------------*/
enum instruction_type //тип инструкции, выполняемой процессором
{
	HLT = 0, //!TODO убрать дублирование индексов команд и аргументов в enum'ах
	STRT = 1,
	PUSH = 2,
	POP = 3,
	ADD = 4,
	SUB = 5,
	MUL = 6,
	DIV = 7,
	OUT = 8,
	NONE = 9/*,
	PUSH_AX = 10,
	PUSH_BX = 11,
	PUSH CX = 12,
	PUSH_DX = 13,
	PUSH_RAM = 14,
	POP_AX = 15,
	POP_BX = 16,
	POP_CX = 17,
	POP_DX = 18,
	POP_RAM = 19*/
};

enum cpucode_descriptional_argument //тип дополнительного (определительного) аргумента в машинном коде
{
	NARG = 0,
	INT = 1,
	REAL = 2,
	RGAX = 3,
	RGBX = 4,
	RGCX = 5,
	RGDX = 6,
	RAM = 7,
	RAMA = 8,
	RAMB = 9,
	RAMC = 10,
	RAMD = 11
};

enum asmcode_argument_type //не записывается в код, используется для описания ассемблерных функций
{
	NOTYPE = 0,
	INSTRUCTION_TYPE = 1,
	NUMBER = 2,
	PARAMETER = 3,
	VARIABLE_ARG = 4
};


/*--------------------------CONST---------------------------------------------*/
/*
const char instruction_code_lenght[] = //сделать отдельный массив для длины текстовых инструкций
{
	1, //HLT //можно сделать сравнение базовых команд без strcmp для ускорения
	1, //STRT
	3, //PUSH
	2, //POP
	1, //ADD
	1, //SUB
	1, //MUL
	1, //DIV
	1, //OUT //создать команду "__VzLoM__ZhOpPi__" (каллок в цикле) (вывод предупреждения ближайший магазин с оперативной памятью находится...)
	1 //NONE //!TODO добавить FMA4;
};
*/

const char instruction_text_lenght[] = //сделать отдельный массив для длины текстовых инструкций
{
	1, //HLT //можно сделать сравнение базовых команд без strcmp для ускорения
	1, //STRT
	2, //PUSH
	2, //POP
	1, //ADD
	1, //SUB
	1, //MUL
	1, //DIV
	1, //OUT //создать команду "__VzLoM__ZhOpPi__" (каллок в цикле) (вывод предупреждения ближайший магазин с оперативной памятью находится...)
	1 //NONE //!TODO добавить FMA4;
};

const char text_command_length[] =
{
	1, //HLT //можно сделать сравнение базовых команд без strcmp для ускорения
	1, //STRT
	2, //PUSH
	2, //POP
	1, //ADD
	1, //SUB
	1, //MUL
	1, //DIV
	1, //OUT
	1 //NONE //!TODO добавить FMA4;
};

const asmcode_argument_type asmcode_argument_mask[][2] = //маска, используемая для описания ассемблерных функций
{
	{ INSTRUCTION_TYPE }, //HLT //можно сделать сравнение базовых команд без strcmp для ускорения
	{ INSTRUCTION_TYPE }, //STRT
	{ INSTRUCTION_TYPE, VARIABLE_ARG }, //PUSH
	{ INSTRUCTION_TYPE, PARAMETER }, //POP
	{ INSTRUCTION_TYPE }, //ADD
	{ INSTRUCTION_TYPE }, //SUB
	{ INSTRUCTION_TYPE }, //MUL
	{ INSTRUCTION_TYPE }, //DIV
	{ INSTRUCTION_TYPE }, //OUT
	{ INSTRUCTION_TYPE } //NONE //!TODO добавить FMA4;
};


#endif
