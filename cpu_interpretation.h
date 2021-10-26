#ifndef CPU_INTERPRETATION_H_INCLUDED
#define CPU_INTERPRETATION_H_INCLUDED


#include <stdlib.h>
#include <assert.h>
#include "instructions.h"
#include "../string_parsing_operations/string-operations.h"

const int ASSEMBLER_VERSION = 0;

struct BinaryHeader
{
	char header = 0x7f;
	char type[4] = "ELF";
	char name[18] = "SoftwareProcessor";
	int version = ASSEMBLER_VERSION;
};

struct Code
{
	text text_format = {};
	int* digit_format = NULL;
};


void input_asm_code( Code* some_code, const char* filename );
void compile_code( Code* some_code );
void output_machine_code( Code* some_code, const char* filename );

instruction_type interpretate_asm_instruction( const char* input_line );

void free_assembler_memory( Code* some_code );


#endif
