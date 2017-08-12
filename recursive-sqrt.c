//	 ______                              _                 ______                   
//	(_____ \                            (_)               / _____)              _   
//	 _____) )_____  ____ _   _  ____ ___ _ _   _ _____   ( (____   ____  ____ _| |_ 
//	|  __  /| ___ |/ ___) | | |/ ___)___) | | | | ___ |   \____ \ / _  |/ ___|_   _)
//	| |  \ \| ____( (___| |_| | |  |___ | |\ V /| ____|   _____) ) |_| | |     | |_ 
//	|_|   |_|_____)\____)____/|_|  (___/|_| \_/ |_____)  (______/ \__  |_|      \__)
//
// Author: Rohan Molloy           
// Description: We do recursive, integer square-root per Newton method
//
//
#include <stdio.h>

#define ITER 100
#define SQUARE(x) ((x)*(x))

int sqrt_int(const int,int);
int sqrt_int(const int n, int est)
{
	static int i = 1;
	printf("iteration:%d, estimated sqrt(%d):%d\n",i++,n,est);
	
	return (est < n && SQUARE(est) < n && SQUARE(est+1) > n) ? 
			est :
			sqrt_int(n, ((est + (n / est))/2)); 

}

int main(int argc, char **argv)
{

		int k = sqrt_int(16555,1);
		printf("final estimate %d\n",k);

}
