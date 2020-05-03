/**
Main file to read in the in
and print out the out
**/

#include "main.h"
#include "ASMParser.h"
#include "ParseResult.h"


int main(int numArgs, char** args) {
	if (numArgs != 4) {
		FILE* in = fopen(args[1], "r");
		FILE* out = fopen(args[2], "w");

		ParseResult* final;
		int lineNum = 0;
		FILE* symbolOut;
		// Milestone 2
		// Open symbol.txt
			symbolOut = fopen("symbol.txt", "w");
		if (in != NULL){
		// Handles symbolic labels
			char symbolArray[100];
			fgets(symbolArray, 100, in);
			while (symbolArray[0] == '\n' || symbolArray[0] == '#') {
				fgets(symbolArray, 100, in);
			}
			int byteCounter = 0;
			int bits = 8192;
			fgets(symbolArray, 100, in);
			while (strstr(symbolArray, ":") != NULL) {
				if (strstr(symbolArray, ".word") != NULL) {
					if (byteCounter != 0) {
						byteCounter = 0;
						bits += 4;
					}
					if (strstr(symbolArray, ",") == NULL) {
						char* pos = strtok(symbolArray, " .\t:");
						fprintf(symbolOut, "0x%08X", bits);
						fprintf(symbolOut, ":  ");
						fprintf(symbolOut, pos);
						fprintf(symbolOut, "\n");
						for (int i = 0; i < 3; i ++){
							pos = strtok(NULL, " .\t:");
						}
						int counter;
						if (pos != NULL) {
							counter = atoi(pos);
						}
						else {
							counter = 1;
						}
						bits = bits + (4 * counter);
					}
					else{
					char* pos = strtok(symbolArray, " .\t:,");
					fprintf(symbolOut, "0x%08X", bits);
					fprintf(symbolOut, ":  ");
					fprintf(symbolOut, pos);
					fprintf(symbolOut, "\n");
					for (int i = 0; i < 2; i++){
						pos = strtok(NULL, " .\t:,");
					}
					while (pos != NULL) {
						bits = bits + 4;
						pos = strtok(NULL, " .\t:,");
					}
				}
				}
				else if (strstr(symbolArray, ".asciiz") != NULL){
					char* pos = strtok(symbolArray, ":");
					fprintf(symbolOut, "0x%08X", bits);
					fprintf(symbolOut, ":  ");
					fprintf(symbolOut, pos);
					fprintf(symbolOut, "\n");
					for (int i = 0; i < 2; i++){
						pos = strtok(NULL, "\"");
					}
					int posLength = strlen(pos);
					for (int i = 0; i < posLength; i++) {
						byteCounter++;
						if (byteCounter == 4) {
							byteCounter = 0;
							bits += 4;
						}
					}
					byteCounter++;
					if (byteCounter == 4) {
						byteCounter = 0;
						bits += 4;
					}
				}
				fgets(symbolArray, 100, in);
			}
			if (byteCounter != 0) {
				byteCounter = 0;
				bits += 4;
			}
			bits = 0;
			fgets(symbolArray, 100, in);
			while (fgets(symbolArray, 100, in) != NULL ) {
				if (symbolArray[0] == '\n' ||
					 strstr(symbolArray, "#") != NULL) {
						 // do nothing
				}
				else if (strstr(symbolArray, ":") != NULL) {
					char* temp = strtok(symbolArray, ":");
					fprintf(symbolOut, "0x%08x", bits);
					fprintf(symbolOut, ":  ");
					fprintf(symbolOut, temp);
					fprintf(symbolOut, "\n");
				}
				else if ((strstr(symbolArray, "ble") != NULL && strstr(symbolArray, "blez") == NULL)) {
					bits += 8;
				}
				else {
					bits += 4;
				}

		}
		fseek(in, 0, SEEK_SET);
		fclose(symbolOut);
		char lineArray[100];
		// Milestone 1
		// Handles .txt

		while (fgets(lineArray, 100, in) != NULL) {
			int length = strlen(lineArray);
			char* fileName = args[1];
			if (strstr(fileName, "8") != NULL || strstr(fileName, "9") != NULL){
				while (strstr(lineArray, ":") != NULL ||
				lineArray[0] == '\n' ||
				lineArray[0] == '.' ||
				length == 0) {
					fgets(lineArray, 100, in);
				}
			 }
				else{
						 while ((strstr(lineArray, "syscall") == NULL &&
						 strstr(lineArray, "j") == NULL &&
		 			   strstr(lineArray, "nop") == NULL &&
					   strstr(lineArray, "$") == NULL) ||
					   strstr(lineArray, "#") != NULL ||
				 	   strstr(lineArray, ":") != NULL ||
		  	 	   lineArray[0] == '\n' ||
      	     lineArray[0] == '.' ||
		  		   length == 0) {
							 fgets(lineArray, 100, in);
						 }
					 }

			lineArray[strlen(lineArray) - 1] = '\0';
			char* temp = calloc(strlen(lineArray) + 1, sizeof(char));
			strcpy(temp, lineArray);
			final = parseASM(lineArray, lineNum);
			printResult(out, final);
			clearResult(final);
			free(final);
			lineNum++;
			free(temp);
		}
		// Also Milestone 2
			// handles .data
		fseek(in, 0, SEEK_SET);
		fgets(lineArray, 100, in);
		while (lineArray[0] == '\n' || lineArray[0] == '#') {
			fgets(lineArray, 100, in);
		}
		fgets(lineArray, 100, in);
		fprintf(out, "\n");
		while (strstr(lineArray, ":") != NULL) {
			if (strstr(lineArray, ".word") != NULL) {
				if (byteCounter != 0) {
						int tempCounter = 4 - byteCounter;
						for (int i = 0; i < tempCounter; i++){
							fprintf(out, "00000000");
						}
						fprintf(out, "\n");
						byteCounter = 0;
					}
					if (strstr(lineArray, ",") == NULL) {
						char* pos = strtok(lineArray, " \t:.");
						for (int i = 0; i < 2; i++){
							pos = strtok(NULL, " \t:.");
						}
						char* lineArray = calloc(10, sizeof(char));
						strcpy(lineArray, pos);
						pos = strtok(NULL, " \t:.");
						int counter;
						if (pos != NULL) {
							counter = atoi(pos);
						}
						else {
							counter = 1;
						}
						int i = 0;
						char* help = helper(32, atoi(lineArray));
						while (i < counter) {
							fprintf(out, help);
							fprintf(out, "\n");
							i++;
						}
						free(help);
						free(lineArray);
						lineArray = NULL;
					}
					else {
						char* pos = strtok(lineArray, " .\t:,");
						for (int i = 0; i < 2; i++){
							pos = strtok(NULL, " .\t:,");
						}
						while (pos != NULL) {
							char* help = helper(32, atoi(pos));
							fprintf(out, help);
							fprintf(out, "\n");
							pos = strtok(NULL, " .\t:,");
							free(help);
						}
					}
				}
				else if (strstr(lineArray, ".asciiz") != NULL){
					char* pos = strtok(lineArray, "\"");
					pos = strtok(NULL, "\"");
					for (int i = 0; i < strlen(pos); i++) {
						int j = 7;
						while (j >= 0){
							char ascTemp;
							if ((pos[i] & (1 << j))){
								ascTemp = '1';
							}
							else {
								ascTemp = '0';
							}
							fprintf(out, "%c",ascTemp);
							j--;
						}
							byteCounter++;
							if (byteCounter == 4) {
								fprintf(out, "\n");
								byteCounter = 0;
							}
						}
					fprintf(out, "00000000");
					byteCounter++;
					if (byteCounter == 4) {
						fprintf(out, "\n");
						byteCounter = 0;
					}
				}
				fgets(lineArray, 100, in);
			}
			if (byteCounter != 0) {
				int tempByteCount = 4 - byteCounter;
				for (int i = 0; i < tempByteCount; i++){
					fprintf(out, "00000000");
				}
				fprintf(out, "\n");
				byteCounter = 0;
			}
			//End Milestone 2
			fclose(in);
			fclose(out);
			return 0;
		}
	}
	// 4 arguements
	// Also Milestone 1
	else if (numArgs == 4) {
		FILE* in = fopen(args[3], "r");
		FILE* out2 = fopen(args[2], "w");
		int byteCounter = 0;
		int counter;
		char temp[100];
		if (in != NULL){
			fgets(temp, 100, in);
			while (temp[0] == '#' || temp[0] == '\n') {
				fgets(temp, 100, in);
			}
			counter = 8192;
			fgets(temp, 100, in);
			while (strstr(temp, ":") != NULL) {
				if (strstr(temp, ".word") != NULL) {
					if (byteCounter != 0) {
						byteCounter = 0;
						counter += 4;
					}
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
				else if (strstr(temp, ".asciiz") != NULL){
					char* pos = strtok(temp, ":");
					fprintf(out2, "0x%08X", counter);
					fprintf(out2, ":  ");
					fprintf(out2, pos);
					fprintf(out2, "\n");
					for (int i = 0; i < 2; i++){
						pos = strtok(NULL, "\"");
					}
					for (int j = 0; j < strlen(pos); j++) {
						byteCounter++;
						if (byteCounter == 4) {
							byteCounter = 0;
							counter += 4;

						}
					}
					byteCounter++;
					if (byteCounter == 4) {
						byteCounter = 0;
						counter += 4;
					}
				}
				fgets(temp, 100, in);
			}
			if (byteCounter != 0) {
				byteCounter = 0;
				counter += 4;
			}
			counter = 0;
			fgets(temp, 100, in);
			while (fgets(temp, 100, in) != NULL ) {
				if (temp[0] == '\n') {
					// do nothing
				}
				else if (strstr(temp, ":") != NULL) {
					char* temp = strtok(temp, ":");
					fprintf(out2, "0x%08x", counter);
					fprintf(out2, ":  ");
					fprintf(out2, temp);
					fprintf(out2, "\n");
				}
				else if ((strstr(temp, "ble") != NULL && strstr(temp, "blez") == NULL)) {
					counter += 8;
				}
				else {
					counter += 4;
				}

	}


	fclose(out2);
	fclose(in);
}
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
