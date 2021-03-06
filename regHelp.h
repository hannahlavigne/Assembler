#include "regHelp.h"

#define NUMREG 15


//Helper for registers
static Registers RegistersTable[NUMREG] = {
  //zero regisyer
	{0, "00000", "$zero"},
  // v registers
	{2, "00010", "$v0"},
	{3, "00011", "$v1"},
  // t registers
	{8, "01000", "$t0"},
	{9, "01001", "$t1"},
	{10, "01010", "$t2"},
	{11, "01011", "$t3"},
  // s registers
	{16, "10000", "$s0"},
	{17, "10001", "$s1"},
	{18, "10010", "$s2"},
	{19, "10011", "$s3"},
	{20, "10100", "$s4"},
	{21, "10101", "$s5"},
	{22, "10110", "$s6"},
	{23, "10111", "$s7"},
};

const Registers* RegistersHelper(const char* const registers){
  for (int i = 0; i < 15; i++) {
		if (strcmp(registers, RegistersTable[i].regName) == 0) {
			return &RegistersTable[i];
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
