#include "cpu_interpretation.h"

int main()
{
	Code some_code;
	input_asm_code( &some_code, "code.asm" );
	compile_code( &some_code );
	output_machine_code( &some_code, "code.txt" );
	return 0;
}
