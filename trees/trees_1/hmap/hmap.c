#include "hmap.h"
#include "rbt.h"
#include "twlist.h"
#include "string_format.h"
#include "hash_func.h"

wrapper create_wrapper() {
    wrapper wrap = {
        createList(),
        0,
        'l'
    };

    return wrap;
}

hmap * create_hmap(int size, int n_t) {
    hmap *map = malloc(sizeof(hmap));
    map->size = size;
    map->n_t = n_t;
    map->table = malloc(sizeof(wrapper)*size); // malloc for pointers
    for (int i=0; i<size; i++) {
        *(map->table + i) = create_wrapper();
    }

    return map;
}

void list_to_rbt(wrapper *ptr) {
    ptr->type_of_structure = 't';
    rbt *new_tree = create_rbt(); // MALLOC
    for (int i=0; i<ptr->size; i++) {
        insert_rbt(&new_tree, getElement(ptr->structure, 0)->value);
        deleteElement(ptr->structure, 0, false);
    }
    free(ptr->structure);
    ptr->structure = new_tree;
}

/*
// FOR deletion purposes
*/
int full_no_fixup_delete_rbt(rbt *node, rbt **root) {
    if (node->left == NULL) { // left is NULL, right can be NULL
        if (node->parent != NULL) {
            if (node == (node->parent)->right) {
                (node->parent)->right = node->right;
            } else {
                (node->parent)->left = node->right;
            }
            if (node->right != NULL) {
                (node->right)->parent = node->parent;
            }
            free(node);
        } else { // mamy root
            if (node->right != NULL) {
                (node->right)->parent = NULL;
                *root = node->right;
            } else {
                node->value = NULL;
            }
            free(node);
        }
    } else if (node->right == NULL) { // right is NULL, left is not NULL
        if (node->parent != NULL) {
            if (node == (node->parent)->right) {
                (node->parent)->right = node->left;
            } else {
                (node->parent)->left = node->left;
            }
            (node->left)->parent = node->parent;
            free(node);
        } else { // mamy root
            (node->left)->parent = NULL;
            *root = node->left;
            free(node);
        }
    } else { // both aren't NULL
        rbt *swap = successor_rbt(node, node->value, false);
        node->value = swap->value; // ustalamy succesora (a musi istniec), bierzemy jego wartosc i usuwamy go z drzewa
        if (node->counter > 0) { // then is red
            node->counter = abs(swap->counter);
        } else { // then is black
            node->counter = -abs(swap->counter);
        }
        swap->value = NULL;
        return full_no_fixup_delete_rbt(swap, root);
    }

    return 1;
}

void rbt_to_list(wrapper *ptr) {
    ptr->type_of_structure = 'l';
    list *new_list = createList();
    for (int i=0; i<ptr->size; i++) {
        if (((rbt *)ptr->structure)->counter > 1) {
            char const *string_to_add = prepare_string((char *)((rbt *)ptr->structure)->value); // MALLOC
            addElement(new_list, string_to_add);
            ((rbt *)ptr->structure)->counter--;
        } else if (((rbt *)ptr->structure)->counter < -1) {
            char const *string_to_add = prepare_string((char *)((rbt *)ptr->structure)->value); // MALLOC
            addElement(new_list, string_to_add);
            ((rbt *)ptr->structure)->counter++;
        } else {
            addElement(new_list, ((rbt *)ptr->structure)->value);
            full_no_fixup_delete_rbt(ptr->structure, (rbt **)&(ptr->structure));
        }
    }
    free(ptr->structure); // zwalniamy rbt
    ptr->structure = new_list;
}

int insert_hmap(hmap *map, char str[]) {
    char const *string_to_add = prepare_string(str); // MALLOC
    unsigned int index = SuperFastHash(string_to_add, strlen(string_to_add)) % map->size;
    wrapper *ptr = map->table + index;
    if (ptr->type_of_structure == 'l') { // mamy liste
        addElement(ptr->structure, string_to_add);
        ptr->size++;
        if (ptr->size >= map->n_t) {
            list_to_rbt(ptr);
        }
    } else { // tutaj domyslnie 't' czyli drzewo
        insert_rbt((rbt **)&(ptr->structure), string_to_add);
        ptr->size++;
    }

    return 1;
}

int load_hmap(hmap *map, char const *dir) {
    FILE *file = fopen(dir, "r");

    if (file != NULL) {
        char k = fgetc(file);
        char *str = malloc(sizeof(char)*100); // MALLOC
        while (k != EOF) {
            for (int i=0; i<100; i++) {
                if (k == ' ' || k == '\n') {
                    *(str+i) = '\0';
                    if (i > 0) {
                        insert_hmap(map, str);
                    }
                    k = fgetc(file);

                    break;
                } else if (k == EOF) {
                    *(str+i) = '\0';
                    if (i > 0) {
                        insert_hmap(map, str);
                    }

                    break;
                } else {
                    *(str+i) = k;
                    k = fgetc(file);
                }
            }
        }

        free(str);

        fclose(file);
        return 1;
    } else {
        return 0;
    }
}

int delete_hmap(hmap *map, char const *value) {
    unsigned int index = SuperFastHash(value, strlen(value)) % map->size;
    wrapper *ptr = map->table + index;
    if (ptr->type_of_structure == 'l') { // mamy liste
        for (int i=0; i<ptr->size; i++) {
            if (strcmp(value, getElement(ptr->structure, i)->value) == 0) {
                deleteElement(ptr->structure, i, true);
                ptr->size--;
                return 1;
            }
        }
    } else { // tutaj domyslnie 't' czyli drzewo
        if (delete_rbt((rbt **)&(ptr->structure), value)) {
            ptr->size--;
            if (ptr->size < map->n_t) {
                rbt_to_list(ptr);
            }
            return 1;
        }
    }

    return 0;
}

int find_hmap(hmap *map, char const *value) {
    unsigned int index = SuperFastHash(value, strlen(value)) % map->size;
    wrapper *ptr = map->table + index;
    if (ptr->type_of_structure == 'l') { // mamy liste
        for (int i=0; i<ptr->size; i++) {
            if (strcmp(value, getElement(ptr->structure, i)->value) == 0) {
                return 1;
            }
        }
    } else { // tutaj domyslnie 't' czyli drzewo
        return find_rbt(ptr->structure, value);
    }

    return 0;
}

int main() {
    int hmap_SIZE = 100;
    int n_t = 100;
    hmap *hmap_structure = create_hmap(hmap_SIZE, n_t);

    int lines;
    char command[10], arg[512];

    scanf("%d", &lines);
    for (int i=0; i<lines; i++) {
        scanf("%s", command);

        if (strcmp(command, "insert") == 0) {
            scanf("%s", arg);
            insert_hmap(hmap_structure, arg);
        } else if (strcmp(command, "load") == 0) {
            scanf("%s", arg);
            if (load_hmap(hmap_structure, arg) == 0) {
                printf("FILE NOT FOUND\n");
            }
        } else if (strcmp(command, "delete") == 0) {
            scanf("%s", arg);
            delete_hmap(hmap_structure, arg);
        } else if (strcmp(command, "find") == 0) {
            scanf("%s", arg);
            printf("%d\n", find_hmap(hmap_structure, arg));
        } else if (strcmp(command, "min") == 0) {
            printf("\n");
        } else if (strcmp(command, "max") == 0) {
            printf("\n");
        } else if (strcmp(command, "successor") == 0) {
            printf("\n");
        } else if (strcmp(command, "inorder") == 0) {
            printf("\n");
        }
    }
}