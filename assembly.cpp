#include "cpu_interpretation.h"

int main()
{
	Code some_code;
	input_asm_code( &some_code, "code.asm" );
	compile_code( &some_code );

/*
	for( int i = 0; i < some_code.text_format.N_strings; i++ )
	{
		printf(">%d<\n", some_code.digit_format[i] );
	}

	printf( "--------------\n" );

	for( int i = 0; i < some_code.text_format.N_strings; i++ )
	{
		printf(">%s<\n", some_code.text_format.index_string[i] );
	}
*/

	output_machine_code( &some_code, "cpucode" );

	free_assembler_memory( &some_code );
	return 0;
}
