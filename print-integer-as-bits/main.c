#include <stdio.h>
void bitprint(int x);
int main(int argc, char **argv) 
{
	bitprint(42);
	return 0;
}
void bitprint(int x) 
{
	int i;
	int n = sizeof(int) * 4;
	int mask = 1 << (n-1);
	for(i = 1; i <= n; ++i) 
	{
		putchar(!(x & mask) ? '0' : '1');
		x <<= 1;
		if(i < n && !(i%4)) 
		{
			putchar(' ');
		}
	}
}
