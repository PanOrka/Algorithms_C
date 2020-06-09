/*
// HMAP structure
*/
typedef struct hmap hmap;
typedef struct wrapper wrapper;

struct wrapper {
    void *structure;
    int size; // bad for duplicates
    char type_of_structure;
};

struct hmap {
    wrapper *table;
    int n_t;
    int size;
};

/*
// Create completly new red black tree node
*/
hmap * create_hmap(int size, int n_t);

/*
// NULL TERMINATED STRINGS
*/

/*
// return values: 1 - success, 0 - failure
*/

/*
// wstaw do struktury ciag s, usuwamy znaki rozne od [a-z] lub [A-Z] z poczatku i konca
*/
int insert_hmap(hmap *map, char str[]);

/*
// dla kazdego wyrazu z pliku (sciezka string) oddzielonego bialym znakiem wykonujemy insert
*/
int load_hmap(hmap *map, char const *dir);

/*
// usuwamy ze struktury wartosc string, jesli istnieje. Takes address of tree pointer.
*/
int delete_hmap(hmap *map, char const *value);

/*
// szukamy wartosci string w strukturze
*/
int find_hmap(hmap *map, char const *value);