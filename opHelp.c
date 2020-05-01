#include "opHelp.h"

#define NUMOP 24

//Stores Opcodes
static OpCode OpcodeTable[NUMOP] = {
  {"011100", "mul"},
  {"000000", "sub"},
  {"001000", "addi"},
  {"001111", "lui"},
  {"100011", "lw"},
  {"000000", "mult"},
  {"000000", "add"},
  {"000000", "nor"},
  {"001010", "slti"},
  {"000000", "syscall"},
  {"001000", "la"},
  {"000100", "beq"},
  {"000101", "bne"},
  {"101011", "sw"},
  {"000000", "addu"},
  {"001001", "addiu"},
  {"000000", "nop"},
  {"000000", "sll"},
  {"000000", "slt"},
  {"000000", "sra"},
  {"000000", "srav"},
  {"000110", "blez"},
  {"000111", "bgtz"},
  {"000010", "j"}

};

//Gets the opcode from the table
const OpCode* OpcodeHelper(const char* const opcode){
  for (int i = 0; i < 24; i++){
    if(strcmp(opcode, OpcodeTable[i].opName) == 0){
      return &OpcodeTable[i];
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
