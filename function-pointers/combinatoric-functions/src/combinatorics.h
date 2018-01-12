#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define __AUTHOR__ "Rohan Molloy"

#define TOKENIZED_OUTPUT "%d %s %d = %lu\n"

#define MIN_ARGS 2

static const char *OP_COMBINATION = "-c";
static const char *OP_PERMUTATION = "-p";

unsigned long combination_f(unsigned int n, unsigned int k);
unsigned long permutation_f(unsigned int n, unsigned int k);
