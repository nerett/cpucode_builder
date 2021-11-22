#include "cpu_interpretation.h"
#include <stdlib.h>
#include <stdio.h>

int main()
{
	Code some_code;
	input_asm_code( &some_code, "code.asm" );
	compile_code( &some_code );

	printf( "Machine code: " );
	for( int i = 0; i < some_code.N_machine_code_entities; i++ )
	{
		printf( "%d ", some_code.digit_format[i] );
	}
	printf( "\n" );

	output_machine_code( &some_code, "cpucode" );

	free_assembler_memory( &some_code );
	return 0;
}
