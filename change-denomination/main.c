#include <stdio.h>

/// Just some code I wrote years ago when I was a C noob
/// Computes how to give out an arbitary amount of currency
/// with the most even distribution of denomonations
//
/// author Rohan Molloy

int main(int argc, char **argv)
{
	long int vals[]=    {5 , 10 , 20 ,50 ,100 ,200};
	long int valcount[]={0 , 0  , 0  , 0 ,  0 ,  0};
	//  0   1    2    3    4    5
	long int value=0;
	long int num = 0;
	long int input[]={0,0};
	long int count=0;
	long int i = 0;
	
	printf("\nChange denomonation  calculator\n\n");
	
	printf("Enter num of dollars :");
	scanf("%ld",&input[0]);
	
	printf("Enter num of cents (rounded to 10c)");
	scanf("%ld",&input[1]);
	
	value = (100*input[0]);
	
	if(input[1] % 10 != 0) {
		printf("cents not a multiple of 10 - omitting");
	} else {
		value += input[1];
	}
	
	while(num<value)
	{
		for(i = 5; i>=0 && num != value; i--)
		{
			if((num+vals[i]) > value) {
				continue;
			}
			num+=vals[i];
			count++;
			valcount[i]++;
			
		}
	}
	printf("\nTOTAL COINS:%ld\tSUCCESS:%ld\n",count,(value==num));
	printf("\n10c\t20c\t50c\t$1\t$2\n");
	
	for(i = 0; i<5; i++)
	{
		printf("%ld\t",valcount[i]);
	}
	
	puts("\n");
	return 0;
}
