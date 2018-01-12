#include <stdio.h>
#include <stdlib.h>
#include <math.h>

unsigned long factorial(unsigned int n);
unsigned long choose(unsigned int n, unsigned int k);
unsigned long permutation(unsigned int n, unsigned int k);

int main(int argc, char **argv)
{
	unsigned n,k;
	char *ptr;


	// Index of the first numerical argument, default 1
	// We ++firstArg if we come across any command line flags
	int firstArg = 1;

	/* By default we opearing using the choose() function.
	   If we get a command line switch '-p', then
	   We will change to using the permutation() function
	*/
	char opr = 'C';
	unsigned long (*function)(unsigned int, unsigned int) = choose;

	/* Check we have at least three arguments */
	if(argc < 3)
	{
		perror "example usage -p 10 6 to compute 10p6\nor -c for combination\n"
		return 1;
	}

	/*	Argument variable 1 is "-p", So now we will use permutation() function
		We change the operator symbol accordingly and we also must
		increment firstarg so we don't parse this switch as an input
	*/
	if(! strcmp(argv[1],"-p")) {
		function = permutation;
		opr = 'P';
		++firstArg;
	}

	/*  Here we check any supplied inputs are 0, in which case we can't proceed forther.
		To perform this evaluation, we need to convert strings (args) into long unsigned
		We do this using strtoul, specifying 10 for base10 (decimal), and the optional var &ptr
		(see `man strtoul for more info)
		We then the parsed values into n and k variables for later access
	*/
	if(!(n = strtoul(argv[firstArg++],&ptr,10)) || !(k = strtoul(argv[firstArg],&ptr,10)) ) {
		return 1;
	}

	/* 	Finally, we print the computation and its result.
		We call function() within the printf statement.
	*/
	printf("%d %c %d = %ld\n",n,opr,k,function(n,k));

}
unsigned long factorial(unsigned int n)
{
	return (n == 0) ? 1 : factorial(n-1) * n;
}

unsigned long choose(unsigned int n, unsigned int k)
{

	return (k == 0 || n == k) ?  1 : choose(n-1, k-1) + choose(n-1, k);
}
unsigned long permutation(unsigned int n, unsigned int k)
{
	return factorial(n)/factorial(n-k);
}
