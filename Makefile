CC = g++
CFLAGS = -c #-Wall -Wextra -g
LDFLAGS = #-Wall -Wextra -g
BUILDDIR = Build/
EXECDIR = Debug/

STRPRSDIR = ../string_parsing_operations/

all: mkdir assembler
	
mkdir:
	mkdir -p Build Debug

assembler: asm_main
	$(CC) $(LDFLAGS) $(BUILDDIR)assembly.o $(BUILDDIR)lib_cpu_interpretation.o $(BUILDDIR)lib_string_parsing_operations.o -o $(EXECDIR)assembly
	
asm_main: lib_cpu_interpretation lib_string_parsing_operations
	$(CC) $(CFLAGS) assembly.cpp -o $(BUILDDIR)assembly.o
	
lib_cpu_interpretation:
	$(CC) $(CFLAGS) cpu_interpretation.cpp -o $(BUILDDIR)lib_cpu_interpretation.o

lib_string_parsing_operations:
	$(CC) $(CFLAGS) $(STRPRSDIR)string-operations.cpp -o $(BUILDDIR)lib_string_parsing_operations.o

disassembler:


asm:
	./$(EXECDIR)assembly

asmd:
	valgrind ./$(EXECDIR)assembly
	
clean:
	rm -rf $(BUILDDIR) $(EXECDIR)
