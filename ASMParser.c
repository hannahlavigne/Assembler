#include "ASMParser.h"

/***  Add include directives for here as needed.  ***/
#include "funcHelp.h"
#include "opHelp.h"
#include "regHelp.h"
#include <inttypes.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

ParseResult* parseASM(const char* const pASM, int currLine) {
   /***  Implementation here is up to you!  ***/
	char* pos;
	char* temp = pASM;
	//Set up my parse final
	ParseResult* final = (ParseResult*) calloc(10, sizeof(ParseResult));
	//Get the instruction
	final->ASMInstruction = (char*) calloc(10, sizeof(char*));
	strcpy(final->ASMInstruction, pASM);
	pos = strtok (temp, " ,\t()");
	final->Mnemonic = (char*) calloc(10, sizeof(char*));
	strcpy(final->Mnemonic, pos);
	// Handle the R-type
	// mul and sub instructions
	// Format: SUB rd, rs, rt
	// Format: MUL rd, rs, rt
	if (strcmp(final->Mnemonic, "mul") == 0 ||
			strcmp(final->Mnemonic, "sub") == 0 ||
			strcmp(final->Mnemonic, "add") == 0 ||
		  strcmp(final->Mnemonic, "nor") == 0 ||
			strcmp(final->Mnemonic, "slt") == 0 ||
		  strcmp(final->Mnemonic, "addu") == 0) {
				// Find the opcode
				final->Opcode = (char*) calloc(10, sizeof(char*));
				strcpy(final->Opcode, OpcodeHelper(final->Mnemonic)->opcode);
				pos = strtok (NULL, " ,\t()");
				// Find the RD register info
				final->rdName = (char*) calloc(10, sizeof(char*));
				strcpy(final->rdName, pos);
				final->rd = RegistersHelper(final->rdName)->regNum;
				final->RD = (char*) calloc(10, sizeof(char*));
				strcpy(final->RD, RegistersHelper(final->rdName)->currReg);
				pos = strtok (NULL, " ,\t()");
				// Find the RS register info
				final->rsName = (char*) calloc(10, sizeof(char*));
				strcpy(final->rsName, pos);
				final->rs = RegistersHelper(final->rsName)->regNum;
				final->RS = (char*) calloc(10, sizeof(char*));
				strcpy(final->RS, RegistersHelper(final->rsName)->currReg);
				pos = strtok (NULL, " ,\t()");
				// Find the RT register info
				final->rtName = (char*) calloc(10, sizeof(char*));
				strcpy(final->rtName, pos);
				final->rt = RegistersHelper(final->rtName)->regNum;
				final->RT = (char*) calloc(10, sizeof(char*));
				strcpy(final->RT, RegistersHelper(final->rtName)->currReg);
				// Find the Funct info
				final->Funct = (char*) calloc(10, sizeof(char*));
				strcpy(final->Funct, FuncHelper(final->Mnemonic)->func);
				/**
				No Imm or IMM infomration
				set = to NULL or 0
				**/
				final->Imm = 0;
				final->IMM = NULL;
		}
	// Handle the addi instruction
	// Format: ADDI rt, rs, immediate
	else if (strcmp(final->Mnemonic, "addi") == 0 ||
					 strcmp(final->Mnemonic, "slti") == 0 ||
				 	 strcmp(final->Mnemonic, "addiu") == 0) {
					// Find the opcode
					final->Opcode = (char*) calloc(10, sizeof(char*));
					strcpy(final->Opcode, OpcodeHelper(final->Mnemonic)->opcode);
					pos = strtok (NULL, " ,\t()");
					/**
					No RD register
					set name = NULL
					set num = 255
					set RD = NULL
					**/
					final->rdName = NULL;
					final->RD = NULL;
					final->rd = 255;
					// Find RT register
					final->rtName = (char*) calloc(10, sizeof(char*));
					strcpy(final->rtName, pos);
					final->rt = RegistersHelper(final->rtName)->regNum;
					final->RT = (char*) calloc(10, sizeof(char*));
					strcpy(final->RT, RegistersHelper(final->rtName)->currReg);
					pos = strtok (NULL, " ,\t()");
					// Find RS register
					final->rsName = (char*) calloc(10, sizeof(char*));
					strcpy(final->rsName, pos);
					final->rs = RegistersHelper(final->rsName)->regNum;
					final->RS = (char*) calloc(10, sizeof(char*));
					strcpy(final->RS, RegistersHelper(final->rsName)->currReg);
					/**
					No Funct
					set funct = NULL
					**/
					final->Funct = NULL;
					pos = strtok (NULL, " ,\t()");
					// Find Imm and IMM
					final->Imm = atoi(pos);
					final->IMM = (char*) calloc(10, sizeof(char*));
					char* tempIMM = calloc(10, sizeof(char*));
					int i = 15;
					int counter = 0;
					while(i >= 0){
						int j = atoi(pos);
						int k = j >> i;
						if(k & 1) {
							tempIMM[counter] = '1';
						}
						else {
							tempIMM[counter] = '0';
						}
						counter++;
						i--;
					}
					strcpy(final->IMM, tempIMM);
					free(tempIMM);
	}
  // Handle the lui instruction
	// Format: LUI rt, immediate
	else if (strcmp(final->Mnemonic, "lui") == 0 ||
					 strcmp(final->Mnemonic, "li") == 0) {
		// Find the opcode
		final->Opcode = (char*) calloc(10, sizeof(char*));
		strcpy(final->Opcode, OpcodeHelper(final->Mnemonic)->opcode);
		/**
		No RD register
		set name = NULL
		set num = 255
		set RD = NULL
		**/
		final->rdName = NULL;
		final->RD = NULL;
		final->rd = 255;
				pos = strtok(NULL, " ,\t()");
		// Find RT register info
		final->rtName = (char*) calloc(10, sizeof(char*));
		strcpy(final->rtName, pos);
		final->rt = RegistersHelper(final->rtName)->regNum;
		final->RT = (char*) calloc(10, sizeof(char*));
		strcpy(final->RT, RegistersHelper(final->rtName)->currReg);
		/**
		No RS register
		set name = NULL
		set num = 0
		set RS = 00000
		**/
		final->rsName = NULL;
		final->rs = 0;
		final->RS = (char*) calloc(10, sizeof(char*));
		strcpy(final->RS,"00000");
		// No Funct, set = to NULL
		final->Funct = NULL;
		pos = strtok(NULL, " ,\t()");
		//Find the Imm and IMM
		final->Imm = atoi(pos);
		final->IMM = (char*) calloc(10, sizeof(char*));
		char* tempIMM = calloc(10, sizeof(char*));
		int i = 15;
		int counter = 0;
		while(i >= 0){
			int j = atoi(pos);
			int k = j >> i;
			if(k & 1) {
				tempIMM[counter] = '1';
			}
			else {
				tempIMM[counter] = '0';
			}
			counter++;
			i--;
		}
		strcpy(final->IMM, tempIMM);
		free(tempIMM);
	}
	// Handle the lw instruction
	// Format: LW rt, offset(base)
    else if (strcmp(final->Mnemonic, "lw") == 0 ||
						 strcmp(final->Mnemonic, "sw") == 0) {
			// Find opcode
			final->Opcode = (char*) calloc(10, sizeof(char*));
			strcpy(final->Opcode, OpcodeHelper(final->Mnemonic)->opcode);
			/**
			No RD register
			set name = NULL
			set num = 0
			set RD = NULL
			**/
			final->rdName = NULL;
			final->rd = 255;
			final->RD = NULL;
			pos = strtok(NULL, " ,\t()");
			// Find RT register info
			final->rtName = (char*) calloc(10, sizeof(char*));
			strcpy(final->rtName, pos);
			final->rt = RegistersHelper(final->rtName)->regNum;
			final->RT = (char*) calloc(10, sizeof(char*));
			strcpy(final->RT, RegistersHelper(final->rtName)->currReg);
			pos = strtok(NULL, " ,\t()");
			//No Funct, set = to NULL
			final->Funct = NULL;
			// Find Imm and IMM
			final->IMM = (char*) calloc(10, sizeof(char*));
			final->Imm = atoi(pos);
			char* tempIMM = calloc(10, sizeof(char*));
			int i = 15;
			int counter = 0;
			while(i >= 0){
				int j = atoi(pos);
				int k = j >> i;
				if(k & 1) {
					tempIMM[counter] = '1';
				}
				else {
					tempIMM[counter] = '0';
				}
				counter++;
				i--;
			}
			strcpy(final->IMM, tempIMM);
			free(tempIMM);
			pos = strtok(NULL, " ,\t()");
			// Find RS register info
			final->rsName = (char*) calloc(10, sizeof(char*));
			strcpy(final->rsName, pos);
			final->rs = RegistersHelper(final->rsName)->regNum;
			final->RS = (char*) calloc(10, sizeof(char*));
			strcpy(final->RS, RegistersHelper(final->rsName)->currReg);

		}
	// Handle the mult instruction
	// Format: MULT rs, rt
	else if (strcmp(final->Mnemonic, "mult") == 0){
		// Find the opcode
		final->Opcode = (char*) calloc(10, sizeof(char*));
		strcpy(final->Opcode, OpcodeHelper(final->Mnemonic)->opcode);
		/**
		No RD register
		set name = NULL
		set num = 255
		set RD = NULL
		**/
		final->rdName = NULL;
		final->RD = NULL;
		final->rd = 0;
		pos = strtok (NULL, " ,\t()");
		// Find RS register info
		final->rsName = (char*) calloc(10, sizeof(char*));
		strcpy(final->rsName, pos);
		final->rs = RegistersHelper(final->rsName)->regNum;
		final->RS = (char*) calloc(10, sizeof(char*));
		strcpy(final->RS, RegistersHelper(final->rsName)->currReg);
		pos = strtok (NULL, " ,\t()");
		// Find RT register info
		final->rtName = (char*) calloc(10, sizeof(char*));
		strcpy(final->rtName, pos);
		final->rt = RegistersHelper(final->rtName)->regNum;
		final->RT = (char*) calloc(10, sizeof(char*));
		strcpy(final->RT, RegistersHelper(final->rtName)->currReg);
		// Find Funct info
		final->Funct = (char*) calloc(10, sizeof(char*));
		strcpy(final->Funct, FuncHelper(final->Mnemonic)->func);
		/**
		No Imm and IMM
		set Imm = 0
		set IMM = NULL
		**/
		final->Imm = 0;
		final->IMM = NULL;
	}
	// Handle the syscall instruction
	// Format: syscall
	else if (strcmp(final->Mnemonic, "syscall") == 0) {
		//Find the Opcode
		final->Opcode = (char*) calloc(10, sizeof(char*));
		strcpy(final->Opcode, OpcodeHelper(final->Mnemonic)->opcode);
		/**
		No RD register
		set name = NULL
		set num = 0
		set RD = NULL
		**/
		final->rdName = NULL;
		final->rd = 0;
		final->RD = NULL;
		/**
		No RS register
		set name = NULL
		set num = 0
		set RS = NULL
		**/
		final->rsName = NULL;
		final->rs = 0;
		final->RS = NULL;
		/**
		No RT register
		set name = NULL
		set num = 0
		set RT = NULL
		**/
		final->rtName = NULL;
		final->rt = 0;
		final->RT = NULL;
		//Find func info
		final->Funct = (char*) calloc(10, sizeof(char*));
		strcpy(final->Funct, FuncHelper(final->Mnemonic)->func);
		/**
		No Imm and IMM
		set Imm = 0
		set IMM = NULL
		**/
		final->Imm = 0;
		final->IMM = NULL;
	}
	// Handles la command
	else if (strcmp(final->Mnemonic, "la") == 0) {
		//Find the opcode
		final->Opcode = (char*) calloc(10, sizeof(char*));
		strcpy(final->Opcode, OpcodeHelper(final->Mnemonic)->opcode);
		// No RD register
		final->rdName = NULL;
		final->rd = 0;
		final->RD = NULL;
		pos = strtok(NULL, " ,\t()");
		// Find RS register info
		final->rsName = (char*) calloc(10, sizeof(char*));
		strcpy(final->rsName, "$zero");
		final->RS = (char*) calloc(10, sizeof(char*));
		strcpy(final->RS, RegistersHelper(final->rsName)->currReg);
		// Find the RT register info
		final->rtName = (char*) calloc(10, sizeof(char*));
		strcpy(final->rtName, pos);
		final->RT = (char*) calloc(10, sizeof(char*));
		strcpy(final->RT, RegistersHelper(final->rtName)->currReg);
		pos = strtok(NULL, " ,\t()");
		// Open symbol.txt
		FILE* symbol = fopen("symbol.txt", "r");
		char symbolTemp[100];
		// Find IMM info
		final->IMM = (char*) calloc(10, sizeof(char*));
			while (fgets(symbolTemp, 100, symbol) != NULL) {
				if (strstr(symbolTemp, pos) != NULL) {
					char* tempPos = strtok(symbolTemp, "  ");
					char* help = helper(16, (int)strtol(tempPos, NULL, 0));
					strcpy(final->IMM, help);
					free(help);
					break;
				}
			}
			// close symbol.txt
			fclose(symbol);
		}
		// Handles beq and bne instructions
		// Format: beq rs, rt, offset
		// Format: bne rs, rt, offset
		else if (strcmp(final->Mnemonic, "beq") == 0 || strcmp(final->Mnemonic, "bne") == 0) {
			//Find the opcode
			final->Opcode = (char*) calloc(10, sizeof(char*));
			strcpy(final->Opcode, OpcodeHelper(final->Mnemonic)->opcode);
			//No RD register
			final->rdName = NULL;
			final->rd = 0;
			final->RD = NULL;
		  pos = strtok(NULL, " ,\t()");
			//Find RS register info
			final->rsName = (char*) calloc(10, sizeof(char*));
			strcpy(final->rsName, pos);
			final->RS = (char*) calloc(10, sizeof(char*));				 strcpy(final->RS, RegistersHelper(final->rsName)->currReg);
			pos = strtok(NULL, " ,\t()");
			// Find RT register info
			final->rtName = (char*) calloc(10, sizeof(char*));
			strcpy(final->rtName, pos);
			final->RT = (char*) calloc(10, sizeof(char*));
		  strcpy(final->RT, RegistersHelper(final->rtName)->currReg);
			// Open symbol.txt
			FILE* symbol = fopen("symbol.txt", "r");
			char symbolTemp[100];
			// Find the IMM info
			final->IMM = (char*) calloc(10, sizeof(char*));
			pos = strtok(NULL, " ,\t()");
			while (fgets(symbolTemp, 100, symbol) != NULL) {
				if (strstr(symbolTemp, pos) != NULL) {
					char* tempPos = strtok(symbolTemp, "  ");
					int number = (((int)strtol(tempPos, NULL, 0)) / 4) - currLine - 1;
					char* help = helper(16, number);
					strcpy(final->IMM, help);
					free(help);
				}
			}
			// Close symbol.txt
			fclose(symbol);
		}
		else if (strcmp(final->Mnemonic, "sll") == 0 ||
		 strcmp(final->Mnemonic, "sra") == 0) {
			 final->Opcode = calloc(7, sizeof(char));
			 strcpy(final->Opcode, OpcodeHelper(final->Mnemonic)->opcode);
		final->rdName = calloc(7, sizeof(char));
		pos = strtok(NULL, " ,\t()");
		strcpy(final->rdName, pos);
		final->rtName = calloc(7, sizeof(char));
		pos = strtok(NULL, " ,\t()");
		strcpy(final->rtName, pos);

		final->Funct = calloc(7, sizeof(char));
		final->RD = calloc(6, sizeof(char));
		final->RS = calloc(6, sizeof(char));
		final->RT = calloc(6, sizeof(char));

		strcpy(final->Funct, FuncHelper(final->Mnemonic)->func);
		strcpy(final->RD, RegistersHelper(final->rdName)->currReg);
		strcpy(final->RS, "00000");
		strcpy(final->RT, RegistersHelper(final->rtName)->currReg);
		final->Shift = calloc(6, sizeof(char));
		pos = strtok(NULL, " ,\t()");
		int number = atoi(pos);
		char* f = helper(5, number);
		strcpy(final->Shift, f);
		free(f);
	}
	else if (strcmp(final->Mnemonic, "j") == 0) {
			final->Opcode = calloc(7, sizeof(char));
			strcpy(final->Opcode, OpcodeHelper(final->Mnemonic)->opcode);
			final->IMM = calloc(27, sizeof(char));
			pos = strtok(NULL, " ,\t()");
			FILE* input = fopen("symbol.txt", "r");
			char line[100];
			while (fgets(line, 100, input) != NULL) {
				if (strstr(line, pos) != NULL) {
					char* label = strtok(line, ":  ");
					int number = (int)strtol(label, NULL, 0);
					int jump = number / 4;
					char* f = helper(26, jump);
					strcpy(final->IMM, f);
					free(f);
				}
			}
			fclose(input);
		}

		return final;
	}

/*
* helper function to help convert
* bytes and numbers to binary
*/
char* helper(int b, int number) {
	int j = b + 1;
	char* final = calloc(j, sizeof(char));
	int i = b - 1;
	while(i >= 0){
		int shift = number >> i;
	  int index = b - 1 - i;
		if (!(shift & 1)) {
			final[index] = '0';
		}
		else {
			final[index] = '1';
		}
		i--;
	}
	return final;
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
