#include "Op.h"

//operation helper
 
static Op OperationTable[26] = {
	{"000000", "add"},
	{"001000", "addi"},
	{"001001", "addiu"},
	{"100001", "addu"},
	{"000100", "beq"},
	{"000111", "bgtz"},
	{"000110", "blez"},
	{"000001", "bltz"},
	{"000101", "bne"},
	{"000010", "j"},
	{"001000", "la"},
	{"001001", "li"},
	{"001111", "lui"},
	{"100011", "lw"},
	{"011100", "mul"},
	{"000000", "mult"},
	{"000000", "nor"},
	{"000000", "nop"},
	{"000000", "sll"},
	{"000000", "slt"},
	{"001010", "slti"},
	{"000000", "sra"},
	{"000000", "srav"},
	{"000000", "sub"},
	{"101011", "sw"},
	{"000000", "syscall"}
};

const Op* findOp(const char* const op) {
	int count = 0;
	while (count < 26) {
		if (strcmp(op, OperationTable[count].mnemonic) == 0) {
			return &OperationTable[count];
		}
		count++;
	}
	return NULL;
}
