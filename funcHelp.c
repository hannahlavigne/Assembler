#include "funcHelp.h"

#define   NUMFUNC 11

//Helper for function code
static FuncCode FuncCodeTable[NUMFUNC] = {
  {"000010", "mul"},
  {"100010", "sub"},
  {"011000", "mult"},
  {"100000", "add"},
  {"100111", "nor"},
  {"001100", "syscall"},
  {"100001", "addu"},
  {"000000", "sll"},
  {"101010", "slt"},
  {"000011", "sra"},
  {"000111", "srav"}
};

const FuncCode* FuncHelper( const char* const func){
  for (int i = 0; i < 11; i++) {
		if (strcmp(func, FuncCodeTable[i].funcName) == 0) {
			return &FuncCodeTable[i];
		}
	}
	return NULL;
}


// On my honor:
//
// - I have not discussed the C language code in my program with
// anyone other than my instructor or the teaching assistants
// assigned to this course.
//
// - I have not used C language code obtained from another student,
// the Internet, or any other unauthorized source, either modified
// or unmodified.
//
// - If any C language code or documentation used in my program
// was obtained from an authorized source, such as a text book or
// course notes, that has been clearly noted with a proper citation
// in the comments of my program.
//
// - I have not designed this program in such a way as to defeat or
// interfere with the normal operation of the grading code.
//
// Hannah LaVigne
// hannahl4
