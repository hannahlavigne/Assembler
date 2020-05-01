#include "ASMParser.h"
#include "Func.h"
#include "Op.h"
#include "Register.h"

#include <inttypes.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

/**  Breaks up given MIPS32 assembly instruction and creates a proper
 *   ParseResult object storing information about that instruction.
 *
 *   Pre:  pASM points to an array holding the bits (as chars) of a
 *         syntactically valid assembly instruction, whose mnemonic is
 *         one of the following:
 *             add addi addiu beq bne la li lui lw  mul mult nor sub slti syscall
 *
 * Final: addu  nop sll sra srav
 * Flow:  blez bgtz j
 * Psedu: move blt
 *
 * 	Throughout each if and if else; the necessary opcodes, registers, and
 *  functions are found by using the helper methods in Op.c, Reg.c, and
 *  Func.c and set appropriately within parseASM. When certain registers or
 *  functions are not used, they are either set to NULL or 0 (depeneding
 *  on the type they are).
 *
 *   Returns:
 *         A pointer to a proper ParseResult object whose fields have been
 *         correctly initialized to correspond to the target of pASM.
 */
ParseResult* parseASM(const char* const pASM, int curr) {
	char* iter = pASM;
	ParseResult* parRes = (ParseResult*) calloc(100, sizeof(ParseResult));
	parRes->ASMInstruction = (char*) calloc(100, sizeof(char*));
	strcpy(parRes->ASMInstruction, pASM);
	char* tmpC = strtok (iter, " ,\t");
	parRes->Mnemonic = (char*) calloc(100, sizeof(char*));
	strcpy(parRes->Mnemonic, tmpC);

	// addi, addiu slti instruction
	// I-Type: | $rt | $rs | immediate |
	// Will need the RT and RS registers; will not use the func helper,
	// IMM and Imm infomration will be used.
	if (strcmp(parRes->Mnemonic, "addi") == 0 || strcmp(parRes->Mnemonic, "addiu") == 0 || strcmp(parRes->Mnemonic, "slti") == 0) {
		parRes->Opcode = (char*) calloc(100, sizeof(char*));
		strcpy(parRes->Opcode, findOp(parRes->Mnemonic)->op);
		tmpC = strtok (NULL, " ,\t");
		parRes->rtName = (char*) calloc(100, sizeof(char*));
		strcpy(parRes->rtName, tmpC);
		parRes->rt = findRegister(parRes->rtName)->num;
		parRes->RT = (char*) calloc(100, sizeof(char*));
		strcpy(parRes->RT, findRegister(parRes->rtName)->reg);
		tmpC = strtok (NULL, " ,\t");
		parRes->rsName = (char*) calloc(100, sizeof(char*));
		strcpy(parRes->rsName, tmpC);
		parRes->rs = findRegister(parRes->rsName)->num;
		parRes->RS = (char*) calloc(100, sizeof(char*));
		strcpy(parRes->RS, findRegister(parRes->rsName)->reg);
		parRes->rdName = NULL;
		parRes->RD = NULL;
		parRes->rd = 255;
		tmpC = strtok (NULL, " ,\t");
		parRes->Imm = atoi(tmpC);
		parRes->IMM = (char*) calloc(16, sizeof(char*));
		char* temp = calloc(16, sizeof(char*));
		//first instance of for loop; converts to binary
		for (int i = 15; i >= 0; i--) {
			int j = atoi(tmpC) >> i;
			if(j & 1) {
				temp[15 - i] = '1';
			}
			else {
				temp[15 - i] = '0';
			}
		}
		strcpy(parRes->IMM, temp);
		free(temp);
	}

	// add, addu, mul, slt, sub, nor instructions
	// R-Type: | $rd | $rs | $rt |
	// Will use the RD, RS, and RT registers; func helper methods for both
	// mul and sub; but will not need any information for IMM or Imm.
	else if (strcmp(parRes->Mnemonic, "add") == 0 ||
  	strcmp(parRes->Mnemonic, "addu") == 0 ||
		strcmp(parRes->Mnemonic, "mul") == 0 ||
    strcmp(parRes->Mnemonic, "slt") == 0 ||
		strcmp(parRes->Mnemonic, "sub") == 0 ||
    strcmp(parRes->Mnemonic, "nor") == 0 ||
    strcmp(parRes->Mnemonic, "srav") == 0) {
		parRes->Funct = (char*) calloc(100, sizeof(char*));
		strcpy(parRes->Funct, findFunction(parRes->Mnemonic)->func);
		parRes->Opcode = (char*) calloc(100, sizeof(char*));
		strcpy(parRes->Opcode, findOp(parRes->Mnemonic)->op);
		tmpC = strtok (NULL, " ,\t");
		parRes->rdName = (char*) calloc(100, sizeof(char*));
		strcpy(parRes->rdName, tmpC);
		parRes->rd = findRegister(parRes->rdName)->num;
		parRes->RD = (char*) calloc(100, sizeof(char*));
		strcpy(parRes->RD, findRegister(parRes->rdName)->reg);
		tmpC = strtok (NULL, " ,\t");
		parRes->rsName = (char*) calloc(100, sizeof(char*));
		strcpy(parRes->rsName, tmpC);
		parRes->rs = findRegister(parRes->rsName)->num;
		parRes->RS = (char*) calloc(100, sizeof(char*));
		strcpy(parRes->RS, findRegister(parRes->rsName)->reg);
		tmpC = strtok (NULL, " ,\t");
		parRes->rtName = (char*) calloc(100, sizeof(char*));
		strcpy(parRes->rtName, tmpC);
		parRes->rt = findRegister(parRes->rtName)->num;
		parRes->RT = (char*) calloc(100, sizeof(char*));
		strcpy(parRes->RT, findRegister(parRes->rtName)->reg);
		parRes->Imm = 0;
		parRes->IMM = NULL;
	}

 // blez and bgtz instruction
else if (strcmp(parRes->Mnemonic, "blez") == 0 ||
  strcmp(parRes->Mnemonic, "bgtz") == 0) {
	 parRes->Opcode = calloc(7, sizeof(char));
			strcpy(parRes->Opcode, findOp(parRes->Mnemonic)->op);
			parRes->rsName = calloc(7, sizeof(char));
			tmpC = strtok(NULL, " ,\t()");
			strcpy(parRes->rsName, tmpC);
			parRes->RS = calloc(6, sizeof(char));
			strcpy(parRes->RS, findRegister(parRes->rsName)->reg);
			parRes->RT = calloc(6, sizeof(char));
			strcpy(parRes->RT, "00000");
			parRes->IMM = calloc(17, sizeof(char));
			tmpC = strtok(NULL, " ,\t()");
			FILE* input = fopen("symbol.txt", "r");
			char line[100];
			while(fgets(line, 100, input) != NULL) {
				if (strstr(line, tmpC) != NULL) {
					char* lab = strtok(line, ":  ");
					int n = (int)strtol(lab, NULL, 0);
					int j = (n / 4) - curr - 1;
					char* f = convert(j, 16);
					strcpy(parRes->IMM, f);
					free(f);
				}
			}
			fclose(input);
   	//parRes->Opcode = (char*) calloc(100, sizeof(char*));
    //strcpy(parRes->Opcode, findOp(parRes->Mnemonic)->op);
  	//parRes->rsName = (char*) calloc(100, sizeof(char*));
    //tmpC = strtok(NULL, " ,\t()");
  	//strcpy(parRes->rsName, tmpC);
    //parRes->RS = (char*) calloc(100, sizeof(char*));
    //strcpy(parRes->RS, findRegister(parRes->rsName)->reg);
    //parRes->RT = (char*) calloc(100, sizeof(char*));
    //strcpy(parRes->RT, findRegister(parRes->rtName)->reg);
		//parRes->IMM = (char*) calloc(16, sizeof(char*));
    //tmpC = strtok(NULL, " ,\t()");
    //char line[50];
    //FILE* in = fopen("symbol.txt", "r");
    //while (fgets(line, 50, in) != NULL) {
      //if (strstr(line, tmpC) != NULL) {
        //char* cTmp = strtok(line, ":  ");
        //int num = (int)strtol(cTmp, NULL, 0);
        //int tmpNum = (num / 4) - curr - 1;
        //char* c = convert(tmpNum, 16);
        //strcpy(parRes->IMM, c);
        //free(c);
      //}
    //}
    //fclose(in);
 }

	//beq and bne
	// | $rs | $rt | offset
	else if (strcmp(parRes->Mnemonic, "beq") == 0 ||
			 strcmp(parRes->Mnemonic, "bne") == 0) {
			parRes->Opcode = (char*) calloc(100, sizeof(char*));
			strcpy(parRes->Opcode, findOp(parRes->Mnemonic)->op);
			parRes->rsName = (char*) calloc(100, sizeof(char*));
			parRes->rtName = (char*) calloc(100, sizeof(char*));
			tmpC = strtok(NULL, " ,\t()");
			strcpy(parRes->rsName, tmpC);
			tmpC = strtok(NULL, " ,\t()");
			strcpy(parRes->rtName, tmpC);
			parRes->RS = (char*) calloc(100, sizeof(char*));
			parRes->RT = (char*) calloc(100, sizeof(char*));
			strcpy(parRes->RT, findRegister(parRes->rtName)->reg);
			strcpy(parRes->RS, findRegister(parRes->rsName)->reg);
			parRes->IMM = (char*) calloc(16, sizeof(char*));
			tmpC = strtok(NULL, " ,\t()");
			char line[50];
			FILE* in = fopen("symbol.txt", "r");
			while (fgets(line, 50, in) != NULL) {
				if (strstr(line, tmpC) != NULL) {
					char* cTmp = strtok(line, "  ");
					int num = (int)strtol(cTmp, NULL, 0);
					int tmpNum = (num / 4) - curr - 1;
					char* c = convert(tmpNum, 16);
					strcpy(parRes->IMM, c);
					free(c);
				}
			}
			fclose(in);
		}

    // j instruction
  		else if (strcmp(parRes->Mnemonic, "j") == 0) {
			parRes->Opcode = calloc(7, sizeof(char));
			strcpy(parRes->Opcode, findOp(parRes->Mnemonic)->op);
			parRes->IMM = calloc(27, sizeof(char));
			tmpC = strtok(NULL, " ,\t()");
			FILE* input = fopen("symbol.txt", "r");
			char line[100];
			while (fgets(line, 100, input) != NULL) {
				if (strstr(line, tmpC) != NULL) {
					char* label = strtok(line, ":  ");
					int number = (int)strtol(label, NULL, 0);
					int jump = number / 4;
					char* f = convert(jump, 26);
					strcpy(parRes->IMM, f);
					free(f);
				}
			}
			fclose(input);
  			//parRes->Opcode = (char*) calloc(100, sizeof(char*));
  			//strcpy(parRes->Opcode, findOp(parRes->Mnemonic)->op);
        //parRes->IMM = calloc(27, sizeof(char*));
        //tmpC = strtok(NULL, " ,\t()");
  			//char line[50];
  			//FILE* in = fopen("symbol.txt", "r");
  			//while (fgets(line, 50, in) != NULL) {
  				//if (strstr(line,tmpC) != NULL) {
  					//char* cTmp = strtok(line, "  ");
  					//int num = ((int)strtol(cTmp, NULL, 0)) / 4;
  					//char* c = convert(num, 26);
  					//strcpy(parRes->IMM, c);
  					//free(c);
  				//}
  			//}
  			//fclose(in);
  		}
	// la instruction
		else if (strcmp(parRes->Mnemonic, "la") == 0) {
			//parRes->Opcode = (char*) calloc(100, sizeof(char*));
			//strcpy(parRes->Opcode, findOp(parRes->Mnemonic)->op);
			//parRes->rsName = (char*) calloc(100, sizeof(char*));
			//parRes->rtName = (char*) calloc(100, sizeof(char*));
			//strcpy(parRes->rsName, "$zero");
			//tmpC = strtok(NULL, " ,\t()");
			//strcpy(parRes->rtName, tmpC);
			//tmpC = strtok(NULL, " ,\t()");
			//parRes->RS = (char*) calloc(100, sizeof(char*));
			//parRes->RT = (char*) calloc(100, sizeof(char*));
			//strcpy(parRes->RT, findRegister(parRes->rtName)->reg);
			//strcpy(parRes->RS, findRegister(parRes->rsName)->reg);
			//parRes->IMM = (char*) calloc(16, sizeof(char*));
			//char line[50];
			//FILE* in = fopen("symbol.txt", "r");
			//while (fgets(line, 50, in) != NULL) {
				//if (strstr(line,tmpC) != NULL) {
					//char* cTmp = strtok(line, "  ");
					//int num = (int)strtol(cTmp, NULL, 0);
					//char* c = convert(num, 16);
					//strcpy(parRes->IMM, c);
					//free(c);
				//break;
				//}
			//}
			//fclose(in);
			parRes->Opcode = (char*) calloc(1, 7*sizeof(char*));
			strcpy(parRes->Opcode, findOp(parRes->Mnemonic)->op);
			parRes->rsName = (char*) calloc(1, 7*sizeof(char*));
			parRes->rtName = (char*) calloc(1, 7*sizeof(char*));
			strcpy(parRes->rsName, "$zero");
			tmpC = strtok(NULL, " ,\t()");
			strcpy(parRes->rtName, tmpC);
			tmpC = strtok(NULL, " ,\t()");
			parRes->RS = (char*) calloc(1, 6*sizeof(char*));
			parRes->RT = (char*) calloc(1, 6*sizeof(char*));
			strcpy(parRes->RS, findRegister(parRes->rsName)->reg);
			strcpy(parRes->RT, findRegister(parRes->rtName)->reg);
			parRes->IMM = (char*) calloc(1, 17*sizeof(char*));
			FILE* input = fopen("symbol.txt", "r");
			char line[100];
			while (fgets(line, 100, input) != NULL) {
				if (strstr(line,tmpC) != NULL) {
					char* label = strtok(line, "  ");
					int number = (int)strtol(label, NULL, 0);

					char* f = convert(number, 16);
					strcpy(parRes->IMM, f);
					free(f);
				break;
				}
			}
			fclose(input);
		}

	// lui instruction
	// | $rt | immediate |
	// RT will be the only register used; Func is not needed; IMM and Imm
	// information will be used.
	else if (strcmp(parRes->Mnemonic, "lui") == 0 ||
		    strcmp(parRes->Mnemonic, "li") == 0) {
		parRes->rtName = (char*) calloc(10, sizeof(char*));
		tmpC = strtok(NULL, " ,\t");
		strcpy(parRes->rtName, tmpC);
		parRes->rsName = NULL;
		parRes->rdName = NULL;
		parRes->RD = NULL;
		parRes->Funct = NULL;
		parRes->rs = 0;
		parRes->rd = 255;
		parRes->rt = findRegister(parRes->rtName)->num;
		tmpC = strtok(NULL, " ,\t");
		parRes->Imm = atoi(tmpC);
		parRes->IMM = (char*) calloc(16, sizeof(char*));
		parRes->Opcode = (char*) calloc(10, sizeof(char*));
		parRes->RT = (char*) calloc(10, sizeof(char*));
		parRes->RS = (char*) calloc(10, sizeof(char*));
		strcpy(parRes->RS,"00000");
		strcpy(parRes->Opcode, findOp(parRes->Mnemonic)->op);
		strcpy(parRes->RT, findRegister(parRes->rtName)->reg);
		char* temp = calloc(16, sizeof(char*));
		for (int i = 15; i >= 0; i--) {
			int j = atoi(tmpC) >> i;
			if(j & 1) {
				temp[15 - i] = '1';
			}
			else {
				temp[15 - i] = '0';
			}
		}
		strcpy(parRes->IMM, temp);
		free(temp);


	}

		// lw instruction
	// | $rt | offset |
	// RT and RS registers will be used; Func will go unused; IMM
	// and Imm information will be used.
    else if (strcmp(parRes->Mnemonic, "lw") == 0 ||
			 strcmp(parRes->Mnemonic, "sw") == 0){
		parRes->rdName = NULL;
		parRes->rsName = (char*) calloc(10, sizeof(char*));
		parRes->rtName = (char*) calloc(10, sizeof(char*));

		parRes->IMM = calloc(17, sizeof(char));
		tmpC = strtok(NULL, " ,\t()");
		strcpy(parRes->rtName, tmpC);
		tmpC = strtok(NULL, " ,\t()");

		//this needs to be changed

		char* label = 	calloc(7, sizeof(char));
			strcpy(label,tmpC);
			tmpC = strtok(NULL, " ,\t()");
			if (tmpC == NULL) {
				strcpy(parRes->rsName, "$zero");
				FILE* input = fopen("symbol.txt", "r");
				char line[100];
				while (fgets(line, 100, input) != NULL) {
					if (strstr(line, label) != NULL) {
						char* label = strtok(line, ":  ");
						int number = (int)strtol(label, NULL, 0);
						char* f = convert(number, 16);
						strcpy(parRes->IMM, f);
						free(f);
						break;
					}
				}
				fclose(input);
				free(label);
			}
			else {
				strcpy(parRes->rsName, tmpC);
				int number = atoi(label);
				char* f = convert(number, 16);
				strcpy(parRes->IMM, f);
				free(f);
				free(label);
			}

		//parRes->IMM = (char*) calloc(16, sizeof(char*));
		//parRes->Imm = atoi(tmpC);
		//char* temp = calloc(16, sizeof(char*));
		//for (int i = 15; i >= 0; i--) {
			//int j = atoi(tmpC) >> i;
			//if(j & 1) {
				//temp[15 - i] = '1';
			//}
			//else {
				//temp[15 - i] = '0';
			//}
		//}
		//strcpy(parRes->IMM, temp);
		//free(temp);
		//tmpC = strtok(NULL, " ,\t()");
		//strcpy(parRes->rsName, tmpC);
		//parRes->rd = 255;
		//parRes->rs = findRegister(parRes->rsName)->num;
		//parRes->rt = findRegister(parRes->rtName)->num;
		//parRes->Funct = NULL;
		//parRes->Opcode = (char*) calloc(10, sizeof(char*));
		//parRes->RS = (char*) calloc(10, sizeof(char*));
		//parRes->RT = (char*) calloc(10, sizeof(char*));
		//strcpy(parRes->Opcode, findOp(parRes->Mnemonic)->op);
		//strcpy(parRes->RS, findRegister(parRes->rsName)->reg);
		//strcpy(parRes->RT, findRegister(parRes->rtName)->reg);
		parRes->Opcode = calloc(7, sizeof(char));
		parRes->RS = calloc(6, sizeof(char));
		parRes->RT = calloc(6, sizeof(char));
		strcpy(parRes->Opcode, findOp(parRes->Mnemonic)->op);
		strcpy(parRes->RS, findRegister(parRes->rsName)->reg);
		strcpy(parRes->RT, findRegister(parRes->rtName)->reg);

	}

  // mult instruction
  // | $rs | $rt |
  // Will use both RS and RT registers; func helper method; and Imm and
  // IMM information.
  else if (strcmp(parRes->Mnemonic, "mult") == 0){
    parRes->Opcode = (char*) calloc(100, sizeof(char*));
    strcpy(parRes->Opcode, findOp(parRes->Mnemonic)->op);
    tmpC = strtok (NULL, " ,\t");
    parRes->rsName = (char*) calloc(100, sizeof(char*));
    strcpy(parRes->rsName, tmpC);
    parRes->rs = findRegister(parRes->rsName)->num;
    parRes->RS = (char*) calloc(100, sizeof(char*));
    strcpy(parRes->RS, findRegister(parRes->rsName)->reg);
    tmpC = strtok (NULL, " ,\t");
    parRes->rtName = (char*) calloc(100, sizeof(char*));
    strcpy(parRes->rtName, tmpC);
    parRes->rt = findRegister(parRes->rtName)->num;
    parRes->RT = (char*) calloc(100, sizeof(char*));
    strcpy(parRes->RT, findRegister(parRes->rtName)->reg);
    parRes->Funct = (char*) calloc(100, sizeof(char*));
    strcpy(parRes->Funct, findFunction(parRes->Mnemonic)->func);
    parRes->rdName = NULL;
    parRes->RD = NULL;
    parRes->rd = 0;
    parRes->Imm = 0;
    parRes->IMM = NULL;
  }

  // nop instructions
  else if (strcmp(parRes->Mnemonic, "nop") == 0) {
	  parRes->Opcode = calloc(7, sizeof(char));
	strcpy(parRes->Opcode, "000000");
	parRes->RS = calloc(6, sizeof(char));
	parRes->RT = calloc(6, sizeof(char));
	strcpy(parRes->RS, "00000");
	strcpy(parRes->RT, "00000");
	parRes->IMM = calloc(17, sizeof(char));
	strcpy(parRes->IMM, "0000000000000000");

    //parRes->Opcode = (char*) calloc(100, sizeof(char*));
    //strcpy(parRes->Opcode, findOp(parRes->Mnemonic)->op);
    //parRes->RS = (char*) calloc(100, sizeof(char*));
    //parRes->RT = (char*) calloc(100, sizeof(char*));
    //strcpy(parRes->RS, findRegister(parRes->rsName)->reg);
    //strcpy(parRes->RT, findRegister(parRes->rtName)->reg);
    //parRes->IMM = (char*) calloc(17, sizeof(char*));
    //strcpy(parRes->IMM, "0000000000000000");

  }

  // sll, sra instructions
  //
	else if (strcmp(parRes->Mnemonic, "sll") == 0 || strcmp(parRes->Mnemonic, "sra") == 0) {
    	//parRes->rdName = (char*) calloc(100, sizeof(char*));
      //tmpC = strtok (NULL, " ,\t()");
      //strcpy(parRes->rdName, tmpC);
      //parRes->rtName = (char*) calloc(100, sizeof(char*));
      //tmpC = strtok (NULL, " ,\t()");
      //strcpy(parRes->rtName, tmpC);
      //parRes->Opcode = (char*) calloc(100, sizeof(char*));
      //parRes->Funct = (char*) calloc(100, sizeof(char*));
      //parRes->RD = (char*) calloc(100, sizeof(char*));
      //parRes->RS = (char*) calloc(100, sizeof(char*));
      //parRes->RT = (char*) calloc(100, sizeof(char*));
      //strcpy(parRes->Opcode, findOp(parRes->Mnemonic)->op);
      //strcpy(parRes->Funct, findFunction(parRes->Mnemonic)->func);
      //strcpy(parRes->RD, findRegister(parRes->rdName)->reg);
      //strcpy(parRes->RS, "00000");
      //strcpy(parRes->RT, findRegister(parRes->rtName)->reg);
      //parRes->Shift = calloc(6, sizeof(char));
      //tmpC = strtok (NULL, " ,\t()");
      //int num = atoi(tmpC);
      //char* c = convert(num, 5);
      //strcpy(parRes->Shift, c);
      //free(c);

		parRes->rdName = calloc(7, sizeof(char));
		tmpC = strtok(NULL, " ,\t()");
		strcpy(parRes->rdName, tmpC);
		parRes->rtName = calloc(7, sizeof(char));
		tmpC = strtok(NULL, " ,\t()");
		strcpy(parRes->rtName, tmpC);
		parRes->Opcode = calloc(7, sizeof(char));
		parRes->Funct = calloc(7, sizeof(char));
		parRes->RD = calloc(6, sizeof(char));
		parRes->RS = calloc(6, sizeof(char));
		parRes->RT = calloc(6, sizeof(char));
		strcpy(parRes->Opcode, findOp(parRes->Mnemonic)->op);
		strcpy(parRes->Funct, findFunction(parRes->Mnemonic)->func);
		strcpy(parRes->RD, findRegister(parRes->rdName)->reg);
		strcpy(parRes->RS, "00000");
		strcpy(parRes->RT, findRegister(parRes->rtName)->reg);
		parRes->Shift = calloc(6, sizeof(char));
		tmpC = strtok(NULL, " ,\t()");
		int number = atoi(tmpC);
		char* f = convert(number, 5);
		strcpy(parRes->Shift, f);
		free(f);
  }

  //else if (strcmp(parRes->Mnemonic, "srav") == 0) {

    //parRes->rdName = calloc(7, sizeof(char));
    //tmpC = strtok(NULL, " ,\t()");
    //strcpy(parRes->rdName, tmpC);
    //parRes->rtName = calloc(7, sizeof(char));
    //tmpC = strtok(NULL, " ,\t()");
    //strcpy(parRes->rtName, tmpC);
    //parRes->rsName = calloc(7, sizeof(char));
		//tmpC = strtok(NULL, " ,\t()");
		//strcpy(parRes->rsName, tmpC);

    //parRes->Opcode = calloc(7, sizeof(char));
    //parRes->Funct = calloc(7, sizeof(char));
    //parRes->RD = calloc(6, sizeof(char));
    //parRes->RS = calloc(6, sizeof(char));
    //parRes->RT = calloc(6, sizeof(char));

    //strcpy(parRes->Opcode, findOp(parRes->Mnemonic)->op);
    //strcpy(parRes->Funct, findFunction(parRes->Mnemonic)->func);
    //strcpy(parRes->RD, findRegister(parRes->rdName)->reg);

    ////strcpy(parRes->RS, "00000"); we don't want rs to be 0
    //strcpy(parRes->RS, findRegister(parRes->rsName)->reg);
	//strcpy(parRes->RT, findRegister(parRes->rtName)->reg);

	//parRes->Shift = calloc(6, sizeof(char));
	//tmpC = strtok(NULL, " ,\t()");
	//int number = atoi(tmpC);
	//char* f = convert(number, 5);
	//strcpy(parRes->Shift, f);
	//free(f);
//}


	// syscall instruction
	//
	else if (strcmp(parRes->Mnemonic, "syscall") == 0) {
			parRes->Opcode = (char*) calloc(100, sizeof(char*));
			strcpy(parRes->Opcode, findOp(parRes->Mnemonic)->op);
			parRes->Funct = (char*) calloc(100, sizeof(char*));
			strcpy(parRes->Funct, findFunction(parRes->Mnemonic)->func);

			parRes->rdName = NULL;
			parRes->rsName = NULL;
			parRes->rtName = NULL;

			parRes->Imm = 0;
			parRes->rd = 0;
			parRes->rs = 0;
			parRes->rt = 0;

			parRes->RD = NULL;
			parRes->RS = NULL;
			parRes->RT = NULL;
			parRes->IMM = NULL;
		}

   return parRes;
}

/**
 * Converts decimal to binary.
 */
char* convert(int numIn, int byte) {
	char* res = calloc(byte + 1, sizeof(char));
	int tmp = byte - 1;
	for (int i = tmp; i >= 0; i--) {
		int num = numIn >> i;
		if (num & 1) {
			res[tmp - i] = '1';
		}
		else {
			res[tmp - i] = '0';
		}
	}
	return res;
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
// Mariela Jardon
// marielaj
