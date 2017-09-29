/* "" is to search the target from local directory
 * while <> is to search under system directory. So
 * you need to use "" to include your own header files
 * or put your file under system lib directory and then
 * use <> to include*/
#include "libb.h"

/* define the function */
void func_libb()
{
	/* We already include stdio.h in header file 
	 * so we can use puts here directly */
	puts("Greeting from libb!!\n");
}

int global_var = 0;
