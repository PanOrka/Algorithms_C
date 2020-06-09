#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/*
// Structure of node
*/
typedef struct {
    void *left;
    void *right;
    char const *value;
} node;

/*
// Structure of TWC_list
*/
typedef struct {
    node *head;
    node *tail;

    int size;
} list;

/*
// Adding element to list, takes list pointer and value
*/
void addElement(list *p, char const *string_to_add);

/*
// Returns element at given index
*/
node * getElement(list *lista, int n);

/*
// Deletes element at given index, it is optional to free values
*/
void deleteElement(list *lista, int n, bool free_value);

/*
// Deletes whole list
*/
void deleteList(list *lista);

/*
// Create TWC_list, returns list *
*/
list * createList();

/*
// Show list on stdin
*/
void showLeft(list *p);