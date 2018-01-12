#include <stdio.h>
#include <time.h>
#include <stdlib.h>
unsigned int rand_interval(unsigned int min, unsigned int max);
int main(int argc, char **argv)
{
	int i;
	for(i = 0; i<200; ++i) {
		unsigned r = rand_interval(1,1000);
		if(!(r%2) ? !(r%6) : !(r%5))
			printf("true for %u\n",r);
	}
	return 0;
}
unsigned int rand_interval(unsigned int min, unsigned int max)
{
    int r;
    const unsigned int range = 1 + max - min;
    const unsigned int buckets = RAND_MAX / range;
    const unsigned int limit = buckets * range;

    /* Create equal size buckets all in a row, then fire randomly towards
     * the buckets until you land in one of them. All buckets are equally
     * likely. If you land off the end of the line of buckets, try again. */
    do
    {
        r = rand();
    } while (r >= limit);

    return min + (r / buckets);
}
