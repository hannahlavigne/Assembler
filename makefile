assembler:
	gcc -o assemble -std=c11 -Wall -W -ggdb3 ParseResult.c ParseResult.h ASMParser.c ASMParser.h Func.c Func.h Op.c Op.h Register.c Register.h main.c main.h 
