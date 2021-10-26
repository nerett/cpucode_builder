#include "cpu_interpretation.h"


void input_asm_code( Code* some_code, const char* filename )
{
	assert( some_code );

	input_text( &some_code->text_format, ( char* )filename );
}



void compile_code( Code* some_code )
{
	some_code->digit_format = ( int* )calloc( some_code->text_format.N_strings, sizeof( int ) );
	instruction_type current_instruction = NONE;
	int current_length = 0;

	int i = 0;
	//int k = 0;
	while( i < some_code->text_format.N_strings  )
	{
		current_instruction = interpretate_asm_instruction( ( const char* )some_code->text_format.index_string[i] );
		current_length = instruction_lenght[current_instruction];

		some_code->digit_format[i] = current_instruction;

		if( current_length == 2 )
		{
			sscanf( some_code->text_format.index_string[i+1], "%d", &some_code->digit_format[i+1] );// current_length == + 1
		}

		i += instruction_lenght[current_instruction];
	}
}



instruction_type interpretate_asm_instruction( const char* input_line )
{
	instruction_type input_instruction = NONE;

	if( !strcmp( input_line, "start" ) ) input_instruction = START;
	else if( !strcmp( input_line, "push" ) ) input_instruction = PUSH;
	else if( !strcmp( input_line, "pop" ) ) input_instruction = POP;
	else if( !strcmp( input_line, "add" ) ) input_instruction = ADD;
	else if( !strcmp( input_line, "sub" ) ) input_instruction = SUB;
	else if( !strcmp( input_line, "mul" ) ) input_instruction = MUL;
	else if( !strcmp( input_line, "div" ) ) input_instruction = DIV;
	else if( !strcmp( input_line, "out" ) ) input_instruction = OUT;
	else if( !strcmp( input_line, "hlt" ) ) input_instruction = HLT;

	return input_instruction;
}



void output_machine_code( Code* some_code, const char* filename )
{
	FILE* machine_code_file = fopen( filename, "wb" );
	fwrite( some_code->digit_format, sizeof( int ), some_code->text_format.N_strings, machine_code_file );
	/*
	for( int i = 0; i < some_code->text_format.N_strings; i++ )
	{
		fprintf( machine_code_file, "%d ", some_code->digit_format[i] );
	}
	*/
	fclose( machine_code_file );
}



void free_assembler_memory( Code* some_code )
{
	free_memory( &some_code->text_format );
	free( some_code->digit_format );
}
