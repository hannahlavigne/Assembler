#ifndef REGISTER_H
#define REGISTER_H
#include <inttypes.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

//register helper
struct _Reg {
	uint8_t num;
	char* reg;
	char* name;
};

typedef struct _Reg Reg;

const Reg* findRegister(const char* const reg);

#endif
