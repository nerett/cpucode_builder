#ifndef CPU_INTERPRETATION_H_INCLUDED
#define CPU_INTERPRETATION_H_INCLUDED


#include <stdlib.h>
#include <assert.h>
#include "instructions.h"
#include "../onegin/string-operations.h"


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
