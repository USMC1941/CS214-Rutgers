/*
 * You can include libraries in the header file
 * and include the header file in this corresponding
 * source file. Then you don't need to write that 
 * much include at beginning
 */
#include "liba.h"

void func_liba() {
	puts("Greeting from liba!!\n");
}

void add_one() {
	global_var++;
}