/*
 * if we don't use macro in liba.h and lib.h
 * we will have redefine issue here 
 */
#include <stdio.h>

#include "liba.h"
#include "libb.h"


int main(int argc, char**argv) {
	/* These functions are not defined in main.c but you can use them */
	func_liba();
	func_libb();

	/* global_var is defined in libb.c */
	printf("The value of global_var: %d\n", global_var);
	printf("\nRunning add_one function in liba...\n");

	/* add_one is defined in liba.c */
	add_one(global_var);
	printf("The value of global_var: %d\n", global_var);
	return 0;
}