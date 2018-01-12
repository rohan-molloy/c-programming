/*
 * swap_ptr.c
 *
 *  Created on: 20/04/2015
 *      Author: rohan
 */
#include <stdio.h>
int extrema(int,int,int);
int arrange_by_size(int*,int*,int);

int main(int argc, char **argv)
{
	int p = 2, q = 45;
	printf("Before: p=%d,q=%d\n",p,q);
	arrange_by_size(&p,&q,1);
	printf("After : p=%d,q=%d\n",p,q);
	return 0;
}
/* Finds the largest of the two provided integers */
int extrema(int x, int y, int findmax)
{
	return (findmax ? x > y : x < y) ? x : y;
}
/* Takes two integer references (x,y) assigns the value of the minimum to x, and the value of the maximum to y
 * Returns non-zero if it swapped the two
 */
int arrange_by_size(int *x, int *y, int decending)
{
	if(x == NULL || y == NULL || x == y || *x == *y) {
		return -1;
	}
	int tmp = extrema(*x,*y,decending);
	*y = (*x == tmp) ? *y : *x;
	*x = tmp;
	return 0;
}

