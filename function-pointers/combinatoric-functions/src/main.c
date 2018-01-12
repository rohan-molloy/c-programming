#include "combinatorics.h"
static const char *MESSGE = "combinatorics program to demonstrate\function pointers\nWritten by __AUTHOR__\nCompiled on __DATE__\n";

void exit_error(const char *str)
{ fprintf(stderr,str); exit(1); }

int main(int argc, char **argv)
{
	// Our two operands
	unsigned n,k;
	n = k = 0;

	// Index of the first numerical argument,
	// default 1
	// We increment this when we come across
	// command line switches (-p -c etc)
	int iFirstOperand = 1;

	// If no option is provided in the arguments,
	// we default to the choose() function.
	// other functiosn are selected through switches
	char *operation = NULL;

	// Here we assign a function (in this case combination)
	// to our ptr
	//
	// This is a weird looking declaration.
	// First, ptr2Func is the variable name
	//
	// The variable holds any function that
	// returns unsigned long
	// and takes two unsigned integer ars
	unsigned long (*ptr2Func)(unsigned int, unsigned int) = NULL;


	// Check we have at least three arguments
	if(argc < MIN_ARGS) {
		exit_error("Too few arguments provided\n");
	}

	// This condition checks if the first argument is -p
	//
	// If it is, permutation() is the function we will pass
	// our operands to
	//
	// We change the operator symbol accordingly and we also must
	// increment the index of the first operand arg
	if( !strcmp(argv[1], OP_PERMUTATION) ){
		ptr2Func  = permutation_f;
		operation = OP_PERMUTATION;
		++iFirstOperand;
	}
	if( !strcmp(argv[1], OP_COMBINATION) ){
		ptr2Func  = combination_f;
		operation = OP_COMBINATION;
		++iFirstOperand;
	}
	else if(!ptr2Func || !operation) {
		ptr2Func  = combination_f;
		operation = OP_COMBINATION;
	}


	//  Here we check any supplied inputs are 0,
	//  in which case we can't proceed forther.
	//
	//	To perform this evaluation, we need to convert strings (args)
	//  into long unsigned integers. We do this using strtoul,
	//
	// unsigned long int strtoul(const char *nptr, char **endptr, int base);
	//
	// 	We then the parsed values into n and k variables for later access
	//
	char *ptr = NULL;
	if(
		 !( n = strtoul(argv[iFirstOperand++],&ptr,10) ) ||
		 !( k = strtoul(argv[iFirstOperand]  ,&ptr,10) ) ||
		 k > n
	 ) { 	exit_error("Invalid input provided"); }


// Finally, we print the computation and its result.
// We call function() within the printf statement.
printf
( TOKENIZED_OUTPUT, 		// printf formatted expression
	n, 	    		// operand0
	operation,  		// operationStr
	k,	    		// operand1
	ptr2Func(n,k)     	// output
);

}
