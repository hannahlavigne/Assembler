#ifndef FUNC_H
#define FUNC_H
#include <inttypes.h>
#include <stdlib.h>
#include <string.h>

//function helper
struct _Func {
	char* func;
	char* mnemonic;
};

typedef struct _Func Func;

const Func* findFunction(const char* const func);

#endif
