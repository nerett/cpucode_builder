#include "cpu_interpretation.h"


/*--------------------------FUNCTION----------------------------------------- */
void input_asm_code( Code* some_code, const char* filename )
{
	assert( some_code );

	input_text( &some_code->text_format, ( char* )filename );
}


/*--------------------------FUNCTION----------------------------------------- */
void compile_code( Code* some_code )
{
	some_code->digit_format = ( int* )calloc( some_code->text_format.N_strings, sizeof( int ) );
	instruction_type current_instruction = NONE;
	cpucode_descriptional_argument current_argument = NARG;
	asmcode_argument_type current_argument_type = NOTYPE;

	int current_text_length = 0;

	int i = 0;
	int j = 0;
	//int k = 0;
	while( i < some_code->text_format.N_strings  )
	{
		current_instruction = interpretate_asm_instruction( ( const char* )some_code->text_format.index_string[i] );
		current_text_length = instruction_text_lenght[current_instruction];

		some_code->digit_format[j] = current_instruction; //запись кода инструкции

		if( current_text_length > 1 ) //интерперетация аргументов
		{
			current_argument_type = asmcode_argument_mask[current_instruction][1];
			if( current_argument_type == VARIABLE_ARG ) //определить тип вариативного аргумента
			{
				if( is_number( some_code->text_format.index_string[i+1] ) )
				{
					current_argument_type = NUMBER;
				}
				else
				{
					current_argument_type = PARAMETER;
				}
			}


			if( current_argument_type == PARAMETER ) //определить параметрический аргумент //записать тип аргумента в машинный код (если числовой, то тип числа; если параметрический то параметр)
			{
				some_code->digit_format[j+1] = interpretate_param_argument( some_code->text_format.index_string[i+1] );
			}
			else if( current_argument_type == NUMBER ) //считать числовой аргумент
			{
				sscanf( some_code->text_format.index_string[i+2], "%d", &some_code->digit_format[j+2] ); //interpretating operand
				cpucode_descriptional_argument descriptional_argument_buffer = INT; //!TODO добавить определение дробных чисел
				some_code->digit_format[j+1] = descriptional_argument_buffer; //!TODO макрос для j+1
			}
			//!TODO блин, я ж могу всё это реализовать проще с помощью нескольких проходов!!!
			//!TODO обработка NARG и подобных
			//sscanf( some_code->text_format.index_string[i+1], "%d", &some_code->digit_format[i+1] );// current_length == + 1
		}

		i += instruction_text_lenght[current_instruction];
		j += instruction_code_lenght[current_instruction];
	}
}


/*--------------------------FUNCTION----------------------------------------- */
instruction_type interpretate_asm_instruction( const char* input_line )
{
	instruction_type input_instruction = NONE;

	if( !strcmp( input_line, "strt" ) ) input_instruction = STRT;
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


/*--------------------------FUNCTION----------------------------------------- */
cpucode_descriptional_argument interpretate_param_argument( const char* some_argument )
{
	cpucode_descriptional_argument input_argument = NARG;

	if( !strcmp( some_argument, "ax" ) ) input_argument = RGAX;
	else if( !strcmp( some_argument, "bx" ) ) input_argument = RGBX;
	else if( !strcmp( some_argument, "cx" ) ) input_argument = RGCX;
	else if( !strcmp( some_argument, "dx" ) ) input_argument = RGDX;
	else if( !strcmp( some_argument, "ram" ) ) input_argument = RAM;

	return input_argument;
}


/*--------------------------FUNCTION----------------------------------------- */
void output_machine_code( Code* some_code, const char* filename )
{
	FILE* machine_code_file = fopen( filename, "wb" );

	BinaryHeader bin_header;
	//fclose( machine_code_file );
	//machine_code_file = fopen( filename, "ab" );
	fwrite( &bin_header, sizeof( BinaryHeader ), 1, machine_code_file );
	fwrite( some_code->digit_format, sizeof( int ), some_code->text_format.N_strings, machine_code_file );
	/*
	for( int i = 0; i < some_code->text_format.N_strings; i++ )
	{
		fprintf( machine_code_file, "%d ", some_code->digit_format[i] );
	}
	*/
	fclose( machine_code_file );
}


/*--------------------------FUNCTION----------------------------------------- */
void free_assembler_memory( Code* some_code )
{
	free_memory( &some_code->text_format );
	free( some_code->digit_format );
}


/*--------------------------FUNCTION----------------------------------------- */
bool is_number( const char* some_string )
{
	return strchr( NUMBER_SYMBOLS, some_string[0] );
}
