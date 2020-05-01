#include "Func.h"

//function helper
static Func FunctionTable[11] = {
	{"100000", "add"},
	{"100001", "addu"},
	{"000010", "mul"},
	{"011000", "mult"},
	{"100111", "nor"},
	{"000000", "sll"},
	{"101010", "slt"},
	{"000011", "sra"},
	{"000111", "srav"},
	{"100010", "sub"},
	{"001100", "syscall"}
};

const Func* findFunction(const char* const func) {
	int count = 0;
	while (count < 11) {
		if (strcmp(func, FunctionTable[count].mnemonic) == 0) {
			return &FunctionTable[count];
		}
		count++;
	}
	return NULL;
}


