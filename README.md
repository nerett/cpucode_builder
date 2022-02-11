# CPUcode Builder
This project is an implementation of assembler and disassembler (isn't done yet) for the Software CPU project. Assembler compiles asm code into machine code that can be run with the Software CPU.

## Usage
#### Assembler
If you've already built and added `assembly` to `$PATH`, run `assembly <path-to-asm-code>` to compile an assembler programm into machine code supported by the Software CPU. Otherwise build the project and execute assembler with `./Debug/assembly <path-to-asm-code>` or `make asm <path-to-asm-code>` (from project root directory).

#### Disassembler
This section isn't done yet.

## Building from source
Download this repository with

```
git clone https://github.com/nerett/cpucode_builder.git
```

Build the project

```
cd cpucode_builder/
make
```

Run Software CPU with

```
make run <path-to-machine-code>
```

To totally rebuild the project run

```
make clean
make
```

## Documentation
This section isn't done yet.

## About project
This programm was written during MIPT **Ded's** cource.
