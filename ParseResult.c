#include "ParseResult.h"
#include <stdlib.h>

/***  Add include directives for here as needed.  ***/


/**  Frees the dynamic content of a ParseResult object.
 *
 *   Pre:  pPR points to a proper ParseResult object.
 *   Post: All of the dynamically-allocated arrays in *pPR have been
 *         deallocated; pointers are NULL, static fields are reset to
 *         default values.
 *
 *   Comments:
 *     -  The function has no information about whether *pPR has been
 *        allocated dynamically, so it cannot risk attempting to
 *        deallocate *pPR.
 *     -  The function is intended to provide the user with a simple
 *        way to free memory; the user may or may not reuse *pPR.  So,
 *        the function does set the pointers in *pPR to NULL.
 */
void clearResult(ParseResult* const pPR) {
   free(pPR->ASMInstruction);
	pPR->ASMInstruction = NULL;
	free(pPR->Mnemonic);
	pPR->Mnemonic = NULL;
	free(pPR->rdName);
	pPR->rdName = NULL;
	free(pPR->rsName);
	pPR->rsName = NULL;
	free(pPR->rtName);
	pPR->rtName = NULL;
	free(pPR->Opcode);
	pPR->Opcode = NULL;
  free(pPR->Funct);
	pPR->Funct = NULL;
	free(pPR->RD);
	pPR->RD = NULL;
	free(pPR->RS);
	pPR->RS = NULL;
	free(pPR->RT);
	pPR->RT = NULL;
	free(pPR->IMM);
	pPR->IMM = NULL;
	pPR->rd = 0;
	pPR->rs = 0;
	pPR->rt = 0;
  pPR->Imm = 0;
}

/**  Prints the contents of a ParseResult object.
 *
 *   Pre:  Log is open on an output file.
 *         pPR points to a proper ParseResult object.
 */
void printResult(FILE* Log, const ParseResult* const pPR) {
  
  // Prints out syscall instruction
  if (strcmp(pPR->Mnemonic, "syscall") == 0) {
    fprintf(Log, pPR->Opcode);
    fprintf(Log, "00000000000000000000");
    fprintf(Log, pPR->Funct);
  }
  else if (strcmp(pPR->Mnemonic, "srav") == 0){
    fprintf(Log, pPR->Opcode);
    fprintf(Log, pPR->RT);
    fprintf(Log, pPR->RS);
    fprintf(Log, pPR->RD);
    fprintf(Log, "00000");
    fprintf(Log, pPR->Funct);
  }
  // Prints out sub, mul, add, nor instructions
  else if (strcmp(pPR->Mnemonic, "mul") == 0 ||
   strcmp(pPR->Mnemonic, "add") == 0 ||
   strcmp(pPR->Mnemonic, "nor") == 0 ||
   strcmp(pPR->Mnemonic, "slt") == 0 ||
   strcmp(pPR->Mnemonic, "sub") == 0 ||
   strcmp(pPR->Mnemonic, "addu") == 0){
     fprintf(Log, pPR->Opcode);
     fprintf(Log, pPR->RS);
     fprintf(Log, pPR->RT);
     fprintf(Log, pPR->RD);
     fprintf(Log, "00000");
     fprintf(Log, pPR->Funct);
   }
   else if (strcmp(pPR->Mnemonic, "move") == 0){
     fprintf(Log, pPR->Opcode);
     fprintf(Log, pPR->RS);
     fprintf(Log, pPR->RT);
     fprintf(Log, pPR->IMM);
     fprintf(Log, "1111111111110101");
     fprintf(Log, "move");
   }
   // Prints out lw, lui, addi, slti,
   // la, beq, bne, sw, addiu, blez,
   // and li instructions
  else if (strcmp(pPR->Mnemonic, "lui") == 0){
    fprintf(Log, pPR->Opcode);
    fprintf(Log, pPR->RS);
    fprintf(Log, pPR->RT);
    fprintf(Log, pPR->IMM);
  }
  else if (strcmp(pPR->Mnemonic, "addi") == 0){
    fprintf(Log, pPR->Opcode);
    fprintf(Log, pPR->RS);
    fprintf(Log, pPR->RT);
    fprintf(Log, pPR->IMM);
  }
  else if (strcmp(pPR->Mnemonic, "slti") == 0 ||
  strcmp(pPR->Mnemonic, "la") == 0 ||
  strcmp(pPR->Mnemonic, "beq") == 0 ||
  strcmp(pPR->Mnemonic, "bne") == 0 ||
  strcmp(pPR->Mnemonic, "sw") == 0 ||
  strcmp(pPR->Mnemonic, "addiu") == 0 ||
  strcmp(pPR->Mnemonic, "blez") == 0 ||
  strcmp(pPR->Mnemonic, "bgtz") == 0){
    fprintf(Log, pPR->Opcode);
    fprintf(Log, pPR->RS);
    fprintf(Log, pPR->RT);
    fprintf(Log, pPR->IMM);
  }
  else if (strcmp(pPR->Mnemonic, "li") == 0){
    fprintf(Log, pPR->Opcode);
    fprintf(Log, pPR->RS);
    fprintf(Log, pPR->RT);
    fprintf(Log, pPR->IMM);
  }
  else if (strcmp(pPR->Mnemonic, "lw") == 0) {
    fprintf(Log, pPR->Opcode);
    fprintf(Log, pPR->RS);
    fprintf(Log, pPR->RT);
    fprintf(Log, pPR->IMM);

}
// Print out mult instruction
else if (strcmp(pPR->Mnemonic, "mult") == 0){
  fprintf(Log, pPR->Opcode);
  fprintf(Log, pPR->RS);
  fprintf(Log, pPR->RT);
  fprintf(Log, "0000000000");
  fprintf(Log, pPR->Funct);
}
// Prints out sll and sra instructions
else if (strcmp(pPR->Mnemonic, "sra") == 0 ||
         strcmp(pPR->Mnemonic, "sll") == 0) {
		fprintf(Log, pPR->Opcode);
		fprintf(Log, pPR->RS);
	   fprintf(Log, pPR->RT);
		fprintf(Log, pPR->RD);
		fprintf(Log, pPR->Shift);
		fprintf(Log, pPR->Funct);
	}
  // Prints out nop instruction
  else if (strcmp(pPR->Mnemonic, "nop") == 0) {
		fprintf(Log, "00000");
		fprintf(Log, "00000");
		fprintf(Log, "00000");
		fprintf(Log, "00000000000000000");
	}
  // Prints out j instruction
  else if (strcmp(pPR->Mnemonic, "j") == 0){
    fprintf(Log, pPR->Opcode);
    fprintf(Log, pPR->IMM);
  }
else {
  return;
}
fprintf(Log, "\n");
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
