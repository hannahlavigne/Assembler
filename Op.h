#ifndef Op_H
#define Op_H
#include <inttypes.h>
#include <stdlib.h>
#include <string.h>


//operation helper
struct _Op {
	char* op;
	char* mnemonic;
};

typedef struct _Op Op;

const Op* findOp(const char* const op);

#endif
