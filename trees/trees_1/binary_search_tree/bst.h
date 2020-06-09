#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/*
// BST structure
*/
typedef struct bst bst;

struct bst {
    bst *parent;
    bst *left;
    bst *right;
    char const *value;
    int counter;
    bool was_visited;
};

/*
// Create completly new binary search tree node
*/
bst * create_bst() {
    bst *ptr = malloc(sizeof(bst));
    ptr->parent = NULL;
    ptr->left = NULL;
    ptr->right = NULL;
    ptr->value = NULL;
    ptr->counter = 0;
    ptr->was_visited = false;

    return ptr;
}

/*
// NULL TERMINATED STRINGS
*/

/*
// return values: 1 - success, 0 - failure
*/

/*
// wstaw do struktury ciag s, usuwamy znaki rozne od [a-z] lub [A-Z] z poczatku i konca
// jesli wartosc istnieje juz w drzewie to wykonuje free(string_to_add)
*/
int insert_bst(bst *tree, char str[]);

/*
// dla kazdego wyrazu z pliku (sciezka string) oddzielonego bialym znakiem wykonujemy insert
*/
int load_bst(bst *tree, char const *dir);

/*
// usuwamy ze struktury wartosc string, jesli istnieje. Takes address of tree pointer.
*/
int delete_bst(bst **root, char const *value);

/*
// szukamy wartosci string w strukturze
*/
int find_bst(bst *tree, char const *value);

/*
// return max value ze struktury
*/
char const * max_bst(bst *tree);

/*
// return min value ze struktury
*/
char const * min_bst(bst *tree);

/*
// return successor string lub NULL-ptr jesli nie ma nastepnikow lub nie ma k
*/
bst * successor_bst(bst *tree, char const *value, bool search_by_value);

/*
// inorder-walk
*/
void inorder_bst(bst *tree);