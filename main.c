#include "ASMParser.h"
#include "main.h"
#include "ParseResult.h"

/**
 * Main runner for Assembler. It will read from a file and print outF to another file.
 */
int main(int num, char** args) {
	if (num == 4) {
		FILE* input = fopen(args[2], "r");
		FILE* output2 = fopen(args[3], "w");
		int bytes = 0;
		int number;
	char line2[100];
	fgets(line2, 100, input);

		while (line2[0] == '#' ||
		       line2[0] == '\n') {
			fgets(line2, 100, input);
		}

			number = 8192;
			fgets(line2, 100, input);
			while (strstr(line2, ":") != NULL) {
				if (strstr(line2, ".word") != NULL) {
					if (bytes != 0) {
						number = number + 4;
						bytes = 0;
					}
					if (strstr(line2, ",") != NULL) {
						char* pch = strtok(line2, " .\t:,");
						fprintf(output2, "0x%08X", number);
						fprintf(output2, ":  ");
						fprintf(output2, pch);
						fprintf(output2, "\n");
						pch = strtok(NULL, " .\t:,");
						pch = strtok(NULL, " .\t:,");
						while (pch != NULL) {
							number = number + 4;
							pch = strtok(NULL, " .\t:,");
						}
					}
					else {
						char* pch = strtok(line2, " .\t:");
						fprintf(output2, "0x%08X", number);
						fprintf(output2, ":  ");
						fprintf(output2, pch);
						fprintf(output2, "\n");
						pch = strtok(NULL, " .\t:");
						pch = strtok(NULL, " .\t:");
						pch = strtok(NULL, " .\t:");
						int count;
						if (pch != NULL) {
							count = atoi(pch);
						}
						else {
							count = 1;
						}					
						number = number + 4*count;						
					}
				}
				else if (strstr(line2, ".asciiz") != NULL){
					char* pch = strtok(line2, ":");
					fprintf(output2, "0x%08X", number);
					fprintf(output2, ":  ");
					fprintf(output2, pch);
					fprintf(output2, "\n");
					pch = strtok(NULL, "\"");
					pch = strtok(NULL, "\"");
					for (int j = 0; j < strlen(pch); j++) {
						bytes++;
						if (bytes == 4) {
							number = number + 4;
							bytes = 0;
						}
					}
					bytes++;
					if (bytes == 4) {
						number = number + 4;
						bytes = 0;
					}
				}
				fgets(line2, 100, input);
			}
			if (bytes != 0) {
				number = number + 4;
				bytes = 0;
			}


	number = 0;
	fgets(line2, 100, input);

		
		while (fgets(line2, 100, input) != NULL ) {
			if (strstr(line2, ":") != NULL) {
			char* temp = strtok(line2, ":");
			fprintf(output2, "0x%08x", number);
			fprintf(output2, ":  ");
			fprintf(output2, temp);
			fprintf(output2, "\n");
			}
			else if (line2[0] == '\n') {
				number = number + 0;
			}
			
			else if ((strstr(line2, "blt") != NULL)
					|| (strstr(line2, "ble") != NULL && strstr(line2, "blez") == NULL)) {
				number = number + 8;	
			}
			else {
				number = number + 4;
			}

		}
		

		fclose(output2);
		fclose(input);
	}
	else {
	FILE* input = fopen(args[1], "r");
	FILE* output = fopen(args[2], "w");
	FILE* output2 = fopen("symbol.txt", "w");

	// symbol
	int bytes = 0;
	int number;
	char line2[100];
	fgets(line2, 100, input);

		while (line2[0] == '#' ||
		       line2[0] == '\n') {
			fgets(line2, 100, input);
		}

			number = 8192;
			fgets(line2, 100, input);
			while (strstr(line2, ":") != NULL) {
				if (strstr(line2, ".word") != NULL) {
					if (bytes != 0) {
						number = number + 4;
						bytes = 0;
					}
					if (strstr(line2, ",") != NULL) {
						char* pch = strtok(line2, " .\t:,");
						fprintf(output2, "0x%08X", number);
						fprintf(output2, ":  ");
						fprintf(output2, pch);
						fprintf(output2, "\n");
						pch = strtok(NULL, " .\t:,");
						pch = strtok(NULL, " .\t:,");
						while (pch != NULL) {
							number = number + 4;
							pch = strtok(NULL, " .\t:,");
						}
					}
					else {
						char* pch = strtok(line2, " .\t:");
						fprintf(output2, "0x%08X", number);
						fprintf(output2, ":  ");
						fprintf(output2, pch);
						fprintf(output2, "\n");
						pch = strtok(NULL, " .\t:");
						pch = strtok(NULL, " .\t:");
						pch = strtok(NULL, " .\t:");
						int count;
						if (pch != NULL) {
							count = atoi(pch);
						}
						else {
							count = 1;
						}					
						number = number + 4*count;						
					}
				}
				else if (strstr(line2, ".asciiz") != NULL){
					char* pch = strtok(line2, ":");
					fprintf(output2, "0x%08X", number);
					fprintf(output2, ":  ");
					fprintf(output2, pch);
					fprintf(output2, "\n");
					pch = strtok(NULL, "\"");
					pch = strtok(NULL, "\"");
					for (int j = 0; j < strlen(pch); j++) {
						bytes++;
						if (bytes == 4) {
							number = number + 4;
							bytes = 0;
						}
					}
					bytes++;
					if (bytes == 4) {
						number = number + 4;
						bytes = 0;
					}
				}
				fgets(line2, 100, input);
			}
			if (bytes != 0) {
				number = number + 4;
				bytes = 0;
			}


	number = 0;
	fgets(line2, 100, input);

		
		while (fgets(line2, 100, input) != NULL ) {
			if (strstr(line2, ":") != NULL) {
			char* temp = strtok(line2, ":");
			fprintf(output2, "0x%08x", number);
			fprintf(output2, ":  ");
			fprintf(output2, temp);
			fprintf(output2, "\n");
			}
			else if ((strstr(line2, "blt") != NULL)
					|| (strstr(line2, "ble") != NULL && strstr(line2, "blez") == NULL)) {
				number = number + 8;	
			}
			
			else if (line2[0] == '\n' ||
					 strstr(line2, "#") != NULL) {
				// do nothing number not increase
			}			
			else {
				number = number + 4;
			}

		}
		

	fseek(input, 0, SEEK_SET);
	fclose(output2);

	// text

	char line[100];
	ParseResult* result;

	//line number
	int current = 0;
	while (fgets(line, 100, input) != NULL) {
		
		while (strstr(line, "#") != NULL ||
		       line[0] == '\n' ||
		       line[0] == '.' ||
			   strlen(line) == 0 ||
			   (strstr(line, "syscall") == NULL && 
			    strstr(line, "j") == NULL &&
			    strstr(line, "nop") == NULL &&
			     strstr(line, "$") == NULL) ||
		       strstr(line, ":") != NULL) {
			fgets(line, 100, input);
		}
		line[strlen(line) - 1] = '\0';
		char* templine = calloc(strlen(line) + 1, sizeof(char));
		strcpy(templine, line);
		char* pch = strtok(templine, " \t,");
		//if (strcmp(pch, "ble") == 0) {
			//char* reg1 = strtok(NULL, "\t, ");
			//char* reg2 = strtok(NULL, "\t, ");
			//char* label = strtok(NULL, "\t, ");
			//char* ins1 = calloc(50, sizeof(char));
			//char* ins2 = calloc(50, sizeof(char));
			//sprintf(ins1, "slt  $at, %s, %s", reg2, reg1);
			//sprintf(ins2, "beq  $at, $zero, %s", label);
			//result = parseASM(ins1, current);
			//printResult(output, result);
			//current++;
			//clearResult(result);
			//free(result);
			//result = parseASM(ins2, current);
			//printResult(output, result);
			//current++;
			//clearResult(result);
			//free(result);
			//free(ins1);
			//free(ins2);
		//}
		if (strcmp(pch, "blt") == 0) {
			char* reg1 = strtok(NULL, "\t, ");
			char* reg2 = strtok(NULL, "\t, ");
			char* label = strtok(NULL, "\t, ");
			char* ins1 = calloc(50, sizeof(char));
			char* ins2 = calloc(50, sizeof(char));
			sprintf(ins1, "slt  $at, %s, %s", reg1, reg2);
			sprintf(ins2, "bne  $at, $zero, %s", label);
			result = parseASM(ins1, current);
			printResult(output, result);
			current++;
			clearResult(result);
			free(result);
			result = parseASM(ins2, current);
			printResult(output, result);
			current++;
			clearResult(result);
			free(result);
			free(ins1);
			free(ins2);
		}
		else if (strcmp(pch, "move") == 0) {
			char* reg1 = strtok(NULL, "\t, ");
			char* reg2 = strtok(NULL, "\t, ");
			//char* label = strtok(NULL, "\t, ");
			char* ins1 = calloc(50, sizeof(char));
			//char* ins2 = calloc(50, sizeof(char));
			//sprintf(ins1, "slt  $at, %s, %s", reg2, reg1);
			//sprintf(ins2, "beq  $at, $zero, %s", label);
			sprintf(ins1, "addu  %s, $zero, %s", reg2, reg1);
			result = parseASM(ins1, current);
			printResult(output, result);
			current++;
			clearResult(result);
			free(result);
			//result = parseASM(ins2, current);
			//printResult(output, result);
			//current++;
			//clearResult(result);
			//free(result);
			free(ins1);
			//free(ins2);
		}
		
		else {
			result = parseASM(line, current);
			printResult(output, result);
			current++;
			clearResult(result);
			free(result);
		}
		free(templine);
	}


	//data
	fseek(input, 0, SEEK_SET);
	fgets(line, 100, input);
		while (line[0] == '#' ||
		       line[0] == '\n') {
			fgets(line, 100, input);
		}

			fgets(line, 100, input);
			fprintf(output, "\n");
			while (strstr(line, ":") != NULL) {
				if (strstr(line, ".word") != NULL) {
					if (bytes != 0) {
						for (int i = 0; i < 4 - bytes; i++)
						{
							fprintf(output, "00000000");
						}
						fprintf(output, "\n");
						bytes = 0;
					}
					
					if (strstr(line, ",") != NULL) {
						char* data = strtok(line, " .\t:,");
						data = strtok(NULL, " .\t:,");
						data = strtok(NULL, " .\t:,");
						while (data != NULL) {
							int n = atoi(data);

							char* f = convert(n, 32);
							fprintf(output, f);
							fprintf(output, "\n");
							free(f);
							data = strtok(NULL, " .\t:,");
						}
					}
					else {
						char* pch = strtok(line, " \t:.");
						pch = strtok(NULL, " \t:.");
						pch = strtok(NULL, " \t:.");
						char* temp = calloc(33, sizeof(char));
						strcpy(temp, pch);
						pch = strtok(NULL, " \t:.");
						int count;
						if (pch != NULL) {
							count = atoi(pch);
						}
						else {
							count = 1;
						}
						
						char* f = convert(atoi(temp), 32);
						for (int i = 0; i < count; i++) {
							fprintf(output, f);
							fprintf(output, "\n");
						}
							free(f);
							free(temp);
							temp = NULL;				
					}
				}
				else if (strstr(line, ".asciiz") != NULL){
					char* pch = strtok(line, "\"");
					pch = strtok(NULL, "\"");				
					for (int j = 0; j < strlen(pch); j++) {
						for (int i = 7; i >= 0; i--) {
							char c = (pch[j] & (1 << i)) ? '1' : '0';
							fprintf(output, "%c",c);
						}
							bytes++;
							if (bytes == 4) {
								fprintf(output, "\n");
								bytes = 0;
							}
						}
					fprintf(output, "00000000");
					bytes++;
					if (bytes == 4) {
						fprintf(output, "\n");
						bytes = 0;
					}
				}
				fgets(line, 100, input);
			}
			if (bytes != 0) {
				for (int i = 0; i < 4 - bytes; i++)
				{
					fprintf(output, "00000000");	
				}
				fprintf(output, "\n");
				bytes = 0;
			}
		
		
	
	fclose(input);
	fclose(output);
	return 0;
} 
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
