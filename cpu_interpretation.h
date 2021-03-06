#ifndef CPU_INTERPRETATION_H_INCLUDED
#define CPU_INTERPRETATION_H_INCLUDED


#include "instructions.h"
#include "../string_parsing_operations/string-operations.h"

const int ASSEMBLER_VERSION = 2;
const char NUMBER_SYMBOLS[] = "0123456789";

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
	int N_machine_code_entities = 0; //для неравномерного кода изменить
};


void input_asm_code( Code* some_code, const char* filename );
void compile_code( Code* some_code );
void output_machine_code( Code* some_code, const char* filename );

instruction_type interpretate_asm_instruction( const char* input_line );
cpucode_descriptional_argument interpretate_param_argument( const char* some_argument );
asmcode_argument_type determine_asmcode_argument_type( const char* some_text_argument );

void free_assembler_memory( Code* some_code );

bool is_number( const char* some_string );


#endif
