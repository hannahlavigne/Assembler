/**
Main file to read in the input
and print out the output
**/

#include "main.h"
#include "ASMParser.h"
#include "ParseResult.h"


int main(int numArgs, char** args) {
	if (numArgs != 4) {
		FILE* in = fopen(args[1], "r");
		FILE* out = fopen(args[2], "w");
		char lineArray[100];
		ParseResult* final;
		int lineNum = 0;
		// Milestone 2
		// Open symbol.txt
		FILE* symbolOut = fopen("symbol.txt", "w");

		// Handles symbolic labels
		char symbolArray[100];
		fgets(symbolArray, 100, in);
		while (symbolArray[0] == '\n' || symbolArray[0] == '#') {
			fgets(symbolArray, 100, in);
		}
		fgets(symbolArray, 100, in);
		int bits = 8192;
		while (strstr(symbolArray, ":") != NULL) {
			if (strstr(symbolArray, ".word") != NULL) {
				char* pos = strtok(symbolArray, " .\t:");
				if (strstr(symbolArray, ",") == NULL) {
					fprintf(symbolOut, "0x%08X", bits);
					fprintf(symbolOut, ":  ");
					fprintf(symbolOut, pos);
					fprintf(symbolOut, "\n");
					for (int i = 0; i < 3; i++){
						pos = strtok(NULL, " .\t:");
					}
					int counter;
					if (pos == NULL) {
						counter = 1;
					}
					else {
						counter = atoi(pos);
					}
					bits = bits + (4 * counter);
				}
				else {
					fprintf(symbolOut, "0x%08X", bits);
					fprintf(symbolOut, ":  ");
					fprintf(symbolOut, pos, "\n");
					for(int i = 0; i < 3; i++) {
						pos = strtok(NULL, " .\t:,");
					}
					while (pos != NULL) {
						pos = strtok(NULL, " .\t:,");
						bits += 4;
					}
				}
			}
			fgets(symbolArray, 100, in);
		}
		fgets(symbolArray, 100, in);
		int i = 0;
		while (fgets(symbolArray, 100, in) != NULL ) {
			if (strstr(symbolArray, ":") != NULL) {
				char* tempArraySymbol = strtok(symbolArray, ":");
				fprintf(symbolOut, "0x%08x", i);
					fprintf(symbolOut, ":  ");
					fprintf(symbolOut, tempArraySymbol);
					fprintf(symbolOut, "\n");
				}
				else if (symbolArray[0] == '\n' ||
					strstr(symbolArray, "#") != NULL) {
					// do nothing
				}
				else {
					i += 4;
				}

			}
			fclose(symbolOut);
			fseek(in, 0, SEEK_SET);
			// Milestone 1
			// Handles .txt
			while (fgets(lineArray, 100, in) != NULL) {
				int length = strlen(lineArray);
			while ((strstr(lineArray, "syscall") == NULL &&
				strstr(lineArray, "$") == NULL) ||
				strstr(lineArray, "#") != NULL ||
				strstr(lineArray, ":") != NULL ||
		  	lineArray[0] == '\n' ||
		  	lineArray[0] == '.' ||
		  	length == 0) {
					fgets(lineArray, 100, in);
				}
				char* temp = calloc(strlen(lineArray) + 1, sizeof(char));
				lineArray[strlen(lineArray) - 1] = '\0';
				strcpy(temp, lineArray);
				free(temp);
				final = parseASM(lineArray, lineNum);
				lineNum++;
				printResult(out, final);
				clearResult(final);
				free(final);
			}
			// End milestone 1

			// Also Milestone 2
			// handles .data
			fseek(in, 0, SEEK_SET);
			fgets(lineArray, 100, in);
				while (lineArray[0] == '\n' || lineArray[0] == '#') {
					fgets(lineArray, 100, in);
				}
				fprintf(out, "\n");
				fgets(lineArray, 100, in);
				while (strstr(lineArray, ":") != NULL) {
					if (strstr(lineArray, ".word") != NULL) {
						char* pos = strtok(lineArray, " \t:.");
						if (strstr(lineArray, ",") == NULL) {
							for (int i = 0; i < 2; i++){
								pos = strtok(NULL, " \t:.");
							}
							char* lineArray = calloc(10, sizeof(char));
							strcpy(lineArray, pos);
							pos = strtok(NULL, " \t:.");
							int counter;
							if (pos == NULL) {
								counter = 1;
							}
							else {
								counter = atoi(pos);
							}
							int i = 0;
							while(i < counter) {
								fprintf(out, helper(32, atoi(lineArray)));
								fprintf(out, "\n");
								i++;
							}
						  free(lineArray);
							lineArray = NULL;
						}
						else{
							for (int i = 0; i < 2; i++){
								pos = strtok(NULL, " .\t:,");
							}
							while (pos != NULL) {
								fprintf(out, helper(32, atoi(pos)), "\n");
								pos = strtok(NULL, " .\t:,");
							}
						}
					}
					fgets(lineArray, 100, in);
				}
				//End Milestone 2
				fclose(in);
				fclose(out);
				return 0;
			}
			// 4 arguements
			// Also Milestone 1
			else {
				FILE* in = fopen(args[2], "r");
				FILE* out2 = fopen(args[3], "w");
				int counter = 100;
				char temp[100];
				fgets(temp, 100, in);
				while (temp[0] == '\n' || temp[0] == '#') {
					fgets(temp, 100, in);
				}
				fgets(temp, 100, in);
				while (strstr(temp, ":") != NULL) {
					if (strstr(temp, ".word") != NULL) {
						if(strstr(temp, ",") == NULL) {
							char* pos = strtok(temp, " .\t:");
							fprintf(out2, "0x%08X", counter);
							fprintf(out2, ":  ");
							fprintf(out2, pos, "\n");
							for (int i = 0; i < 3; i++){
								pos = strtok(NULL, " .\t:");
							}
							int count;
							if (pos == NULL) {
								count = 1;
							}
							else {
								count = atoi(pos);
							}
							counter += (count * 4);
						}
						else {
							char* pos = strtok(temp, " .\t:,");
							fprintf(out2, "0x%08X", counter);
							fprintf(out2, ":  ");
							fprintf(out2, pos, "\n");
							for (int i = 0; i < 2; i++){
								pos = strtok(NULL, " .\t:,");
							}
							while (pos != NULL) {
								counter = counter + 4;
								pos = strtok(NULL, " .\t:,");
							}
						}
					}
					fgets(temp, 100, in);
				}
				counter = 0;
				fgets(temp, 100, in);
				while (fgets(temp, 100, in) != NULL ) {
					if (strstr(temp, ":") != NULL) {
						char* lineArray = strtok(temp, ":");
						fprintf(out2, "0x%08x", counter);
						fprintf(out2, ":  ");
						fprintf(out2, lineArray, "\n");
					}
					else if (temp[0] == '\n') {
						// do nothing
					}
					else {
						counter = counter + 4;
					}
				}
				fclose(out2);
				fclose(in);
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
// Hannah LaVigne
// hannahl4
