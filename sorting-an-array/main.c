#include < stdio.h >
#include < stdlib.h >

/* Initial size of the array */
#define SIZE_INIT 20

/* Function declarations */
char * readinput(void);
void selectionsort(char * );
void swap(char * , int, int);
void printarray(char * );

int main(int argc, char ** argv)
{
    /* Read input from stdin, and populate it into an array created with malloc() */
    char * userInput = readinput();

    /* Exit if array could not be created */
    if (userInput == NULL) {
	     exit(EXIT_FAILURE);
     }
    puts("sorting");
    /* Sort the array */
    selectionsort(userInput);

    /* Free the memory allocated for the array to the OS */
    free((void * ) userInput);

    /* Exit */
    exit(EXIT_SUCCESS);
}
char * readinput(void)
{
    int c, count = 0;
    int size = SIZE_INIT;

    /* Allocate memory for a char array using the initial size macro */
    char * array = (char * ) malloc(size * sizeof(char));

    /* Keep reading from stdin until EOF */
    while ((c = getchar()) != EOF) {
        /* If our array is full, call realloc() to expand the array by double */
        if (count >= size) {
            size *= 2;
            array = (char * ) realloc(array, size * sizeof(char));
        }

        /* Check for memory allocation failure, and terminate if so */
        if (array == NULL) {
            return NULL;
        }

        /* Place the read character into the array */
        array[count++] = c;
    }

    /* Place a null character at the end of the array */
    array[count] = '\0';

    /* Return ptr to array */
    return array;
}
void selectionsort(char * array)
{
    int len, i = 0;

    /* Sanity check, return if array is null or empty */
    if (array == NULL || array[0] == '\0') return;

    /* Dertermine the length of the array by incrementing until a null char is read */
    while (array[++len] != '\0');

    /* Build the sublist of sorted vals by iterating 'i' from 0 to n-1. Check if i is min, if not, swap */
    for (i = 0; i < len - 1; i++) {
        int min, j = i;

        /* Iterate through the array looking for new minima */
        while (++j < len) {
            if (array[j] < array[min]) min = j;
        }

        /* If the current element is not the minimum, swap */
        if (min != i) swap(array, i, min);
    }
}
void swap(char * array, int i1, int i2)
{
    char foo = array[i1];
    array[i1] = array[i2];
    array[i2] = foo;
}
void printarray(char * array)
{
    /* Terminate if null/empty array supplied */
    if (array == NULL || array[0] == '\0') return;
    int i;

    /* Iterate through the array until null terminating char. Print the char if its a non-control char */
    for (i = 0; array[i] != '\0'; i++) {
        if (array[i] >= '0' && array[i] <= '~') putchar(array[i]);
    }

    /* Print a new line */
    putchar('\n');
}
