#include <stdio.h>

#include <stdlib.h>

/* The link list structure */
struct linkednode {
  char * value;
  struct linkednode * next;
};
typedef struct linkednode linked_node;

/* Function to create linked node from string array */
linked_node * createlist(char * []);

/* Function to calculate the number of elements in a string array */
int arrsize(char * []);

/* Function to print the linked list */
int printlist(linked_node * );

int printlist(linked_node * list) {

  void * previous = NULL;

  /* Check list is not null */
  if (!list)
    return 255;

  /* Traverse until no next node exists */
  while (list != NULL) {
    printf("%s (%p)\n|\n", list - > value, list);
    list = list - > next;
  }

  printf("%p\n", list);

  return 0;

}

linked_node * createlist(char * array[]) {
  /* Pointers to head and current position*/
  linked_node * head = NULL;
  linked_node * currentnode = NULL;

  // Iterate through the array, processing each element into a node
  // We iterate backwards, so that the head of the final list is the first element in the array
  for (int i = arrsize(array) - 1; i > 0; i--) {
    /* Create the pointer to the new (current node).
     * Allocate an amount of memory equal to the size of node, creating a void* pointer
     * Cast this void pointer to a linked node pointer
     */
    currentnode = (linked_node * ) malloc(sizeof(linked_node));
    if (!currentnode)
      return NULL;

    /* Derefrence the ptr to struct 
     * and set its fields
     */
    currentnode - > value = array[i];
    currentnode - > next = head;

    /* Set head to point to current node*/
    head = currentnode;
  }
  return head;
}

int arrsize(char * array[]) {
  int i = 0;
  while (array[i] != NULL)
    ++i;
  return i;
}

int main(int argc, char * argv[]) {

  if (argc < 2) {
    perror("Need at least 2 arguments!\n");
    return 1;
  }

  linked_node * linklist = createlist(argv);

  if (!linklist) {
    perror("createList returned null!\n");
    return 255;
  }

  printlist(linklist);

  return 0;
}
