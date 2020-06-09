#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/*
// RBT structure
*/
typedef struct rbt rbt;

struct rbt {
    rbt *parent;
    rbt *left;
    rbt *right;
    char const *value;
    int counter; // counter > 0 is red, counter < 0 is black
    bool was_visited;
};

/*
// Create completly new red black tree node
*/
rbt * create_rbt();

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
int insert_rbt(rbt **root, char const *string_to_add);

/*
// dla kazdego wyrazu z pliku (sciezka string) oddzielonego bialym znakiem wykonujemy insert
*/
int load_rbt(rbt **root, char const *dir);

/*
// usuwamy ze struktury wartosc string, jesli istnieje. Takes address of tree pointer.
*/
int delete_rbt(rbt **root, char const *value);

/*
// szukamy wartosci string w strukturze
*/
int find_rbt(rbt *tree, char const *value);

/*
// return max value ze struktury
*/
char const * max_rbt(rbt *tree);

/*
// return min value ze struktury
*/
char const * min_rbt(rbt *tree);

/*
// return successor string lub NULL-ptr jesli nie ma nastepnikow lub nie ma k
*/
rbt * successor_rbt(rbt *tree, char const *value, bool search_by_value);

/*
// inorder-walk
*/
void inorder_rbt(rbt *tree);