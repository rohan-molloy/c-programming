/*

 * swap_xor.c
 *
 *  Created on: 20/04/2015
 *      Author: rohan molloy
 */
#include <stdio.h>
void swap_xor(int*,int*);
int main(int argc, char *argv[])
{
	int a = 10, b = 40;
	printf("a = %d | b = %d\n",a,b);
	swap_xor(&a,&b);
	printf("a = %d | b = %d\n",a,b);
	return 0;
}
void swap_xor(int *x, int *y)
{
	if(*x == *y) return;
	*x = *x ^ *y;
	*y = *x ^ *y;
	*x = *x ^ *y;
}
