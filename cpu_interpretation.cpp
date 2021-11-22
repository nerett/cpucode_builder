#include "cpu_interpretation.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>


/*--------------------------FUNCTION----------------------------------------- */
void input_asm_code( Code* some_code, const char* filename )
{
	assert( some_code );


	printf( "Loading assembler code from \"%s\"...\n", filename );
	input_text( &some_code->text_format, ( char* )filename );
}


/*--------------------------FUNCTION----------------------------------------- */
void compile_code( Code* some_code )
{
	assert( some_code );


	printf( "Starting compilation...\n" );

	some_code->digit_format = ( int* )calloc( some_code->text_format.N_strings * 3, sizeof( int ) ); //!TODO определять объём буфера
	printf( "Memory for machine code buffer allocated\n" );

	instruction_type current_instruction = NONE;
	cpucode_descriptional_argument current_argument = NARG;
	asmcode_argument_type current_argument_type = NOTYPE;

	int current_text_length = 0;

	int i = 0;
	int j = 0;
	//int k = 0;
	printf( "Starting commands interpretation...\n" );
	while( i < some_code->text_format.N_strings  )
	{
		printf( "Processing text entity №%d...\n", i );

		current_instruction = NONE; //это вообще-то не нужно, но я на всякий случай решил добавить
		current_argument = NARG;
		current_argument_type = NOTYPE;
		current_text_length = 0;

		current_instruction = interpretate_asm_instruction( ( const char* )some_code->text_format.index_string[i] );
		current_text_length = instruction_text_lenght[current_instruction];
		printf( "Interpetated instruction code as %d with text length %d\n", current_instruction, current_text_length );

		some_code->digit_format[j] = current_instruction; //запись кода инструкции
		j++; //переход далее

		if( current_text_length > 1 ) //интерперетация аргументов
		{
			printf( "Processing arguments...\n" );

			current_argument_type = asmcode_argument_mask[current_instruction][1];
			if( current_argument_type == VARIABLE_ARG ) //определить тип вариативного аргумента
			{
				current_argument_type = determine_asmcode_argument_type( some_code->text_format.index_string[i+1] );
			}


			if( current_argument_type == PARAMETER ) //определить параметрический аргумент //записать тип аргумента в машинный код (если числовой, то тип числа; если параметрический то параметр)
			{
				some_code->digit_format[j] = interpretate_param_argument( some_code->text_format.index_string[i+1] );
				printf( "Interpetated as PARAMETER argument with code %d\n", some_code->digit_format[j] );
				j++;

				if( some_code->digit_format[j-1] == RAM )
				{
					sscanf( some_code->text_format.index_string[i+1] + 1, "%d[0-9]", &some_code->digit_format[j] );
					j++;
				}
			}
			else if( current_argument_type == NUMBER ) //считать числовой аргумент
			{
				sscanf( some_code->text_format.index_string[i+1], "%d", &some_code->digit_format[j+1] ); //interpretating operand
				cpucode_descriptional_argument descriptional_argument_buffer = INT; //!TODO добавить определение дробных чисел
				some_code->digit_format[j] = descriptional_argument_buffer; //!TODO макрос для j+1
				printf( "Interpetated as NUMBER argument \"%d\"\n", some_code->digit_format[j] ); //! ERROR
				j += 2;
			}
			//!TODO блин, я ж могу всё это реализовать проще с помощью нескольких проходов!!!
			//!TODO обработка NARG и подобных
			//sscanf( some_code->text_format.index_string[i+1], "%d", &some_code->digit_format[i+1] );// current_length == + 1
		}

		i += instruction_text_lenght[current_instruction];
		//j += instruction_code_lenght[current_instruction];
		//some_code->N_machine_code_entities += instruction_code_lenght[current_instruction];
	}
	some_code->N_machine_code_entities = j;
}


/*--------------------------FUNCTION----------------------------------------- */
instruction_type interpretate_asm_instruction( const char* input_line )
{
	instruction_type input_instruction = NONE;

	if( !strcmp( input_line, "strt" ) ) input_instruction = STRT; //сделать таблицы соответствия вместо этого
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

	if( some_argument[0] == '[' ) //если обращение к оперативной памяти
	{
		if( is_number( &some_argument[1] ) ) input_argument = RAM;
		else if( some_argument[1] == 'a' ) input_argument = RAMA;
		else if( some_argument[1] == 'b' ) input_argument = RAMB;
		else if( some_argument[1] == 'c' ) input_argument = RAMC;
		else if( some_argument[1] == 'd' ) input_argument = RAMD;
	}
	else //если обращение к регистру
	{
		if( !strcmp( some_argument, "ax" ) ) input_argument = RGAX;
		else if( !strcmp( some_argument, "bx" ) ) input_argument = RGBX;
		else if( !strcmp( some_argument, "cx" ) ) input_argument = RGCX;
		else if( !strcmp( some_argument, "dx" ) ) input_argument = RGDX;
	}

	return input_argument;
}


/*--------------------------FUNCTION----------------------------------------- */
void output_machine_code( Code* some_code, const char* filename )
{
	assert( some_code );
	assert( filename );


	printf( "Opening file...\n" );
	FILE* machine_code_file = fopen( filename, "wb" );
	printf( "File opened successfully\n" );

	BinaryHeader bin_header;
	//fclose( machine_code_file );
	//machine_code_file = fopen( filename, "ab" );
	printf( "Writing binary header...\n" );
printf("file ptr = %p\n", machine_code_file );
	fwrite( &bin_header, sizeof( bin_header ), 1, machine_code_file );

	printf( "Writing machine code from buffer to \"%s\"...\n", filename );
	fwrite( some_code->digit_format, sizeof( int ), some_code->N_machine_code_entities, machine_code_file ); //исправить размер
	printf( "Code written successfully\n" );
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


/*--------------------------FUNCTION----------------------------------------- */
asmcode_argument_type determine_asmcode_argument_type( const char* some_text_argument )
{
	if( is_number( some_text_argument ) )
	{
		return NUMBER;
	}

	return PARAMETER;
	//!TODO проверку каждого символа можно добавить и тут
}
