#include "bst.h"
#include "string_format.h"

void inorder_bst(bst *tree) {
    printf("== TREE IN ORDER ==\n");
    bool can_be_traversed = tree->was_visited;
    tree->was_visited = !tree->was_visited;
    while (tree != NULL) {
        if (tree->left != NULL && (*(tree->left)).was_visited == can_be_traversed) {
            tree = tree->left;
            tree->was_visited = !tree->was_visited;
        } else if (tree->right != NULL && (*(tree->right)).was_visited == can_be_traversed) {
            printf("%s(%d), ", tree->value, tree->counter);
            tree = tree->right;
            tree->was_visited = !tree->was_visited;
        } else {
            if (tree->right == NULL) {
                printf("%s(%d), ", tree->value, tree->counter);
            }
            tree = tree->parent;
        }
    }
    printf("\n===================\n");
}

int load_bst(bst *tree, char const *dir) {
    FILE *file = fopen(dir, "r");

    if (file != NULL) {
        char k = fgetc(file);
        char *str = malloc(sizeof(char)*100); // MALLOC
        while (k != EOF) {
            for (int i=0; i<100; i++) {
                if (k == ' ' || k == '\n') {
                    *(str+i) = '\0';
                    if (i > 0) {
                        insert_bst(tree, str);
                    }
                    k = fgetc(file);

                    break;
                } else if (k == EOF) {
                    *(str+i) = '\0';
                    if (i > 0) {
                        insert_bst(tree, str);
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

int insert_bst(bst *tree, char str[]) {
    char const *string_to_add = prepare_string(str); // MALLOC

    if (tree->value == NULL) {
        tree->value = string_to_add;
        tree->counter = 1;
        return 1;
    } else {
        bool root_flag = tree->was_visited;
        while (true) {
            int cmp_value = strcmp(string_to_add, tree->value);
            if (cmp_value > 0) { // string_to_add > tree->value
                if (tree->right != NULL) {
                    tree = tree->right;
                } else {
                    bst *new_node = malloc(sizeof(bst)); // MALLOC
                    new_node->parent = tree;
                    new_node->left = NULL;
                    new_node->right = NULL;
                    new_node->value = string_to_add;
                    new_node->counter = 1;
                    new_node->was_visited = root_flag;

                    tree->right = new_node;
                    return 1;
                }
            } else if (cmp_value < 0) { // string_to_add < tree->value
                if (tree->left != NULL) {
                    tree = tree->left;
                } else {
                    bst *new_node = malloc(sizeof(bst)); // MALLOC
                    new_node->parent = tree;
                    new_node->left = NULL;
                    new_node->right = NULL;
                    new_node->value = string_to_add;
                    new_node->counter = 1;
                    new_node->was_visited = root_flag;

                    tree->left = new_node;
                    return 1;
                }
            } else {
                tree->counter++;
                free((void *)string_to_add);
                return 1;
            }
        }
    }
}

/*
// Podprocedura delete_bst()
*/
int delete_node(bst *node, bst **root) {
    if (node->left == NULL) { // left is NULL, right can be NULL
        if (node->parent != NULL) {
            if (node == (node->parent)->right) {
                (node->parent)->right = node->right;
            } else {
                (node->parent)->left = node->right;
            }
            free((void *)node->value);
            if (node->right != NULL) {
                (node->right)->parent = node->parent;
            }
            free(node);
        } else { // mamy root
            free((void *)node->value);
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
            free((void *)node->value);
            (node->left)->parent = node->parent;
            free(node);
        } else { // mamy root
            free((void *)node->value);
            (node->left)->parent = NULL;
            *root = node->left;
            free(node);
        }
    } else { // both aren't NULL
        bst *swap = successor_bst(node, node->value, false);
        free((void *)node->value);
        node->value = swap->value; // ustalamy succesora (a musi istniec), bierzemy jego wartosc i usuwamy go z drzewa
        node->counter = swap->counter;
        swap->value = NULL;
        return delete_node(swap, root);
    }

    return 1;
}

int delete_bst(bst **root, char const *value) {
    bst *tree = *root;
    while (tree != NULL) {
        int cmp_value = strcmp(value, tree->value);
        if (cmp_value > 0) { // value > tree->value
            tree = tree->right;
        } else if (cmp_value < 0){
            tree = tree->left;
        } else {
            if (tree->counter > 1) {
                tree->counter--;
                return 1;
            } else {
                return delete_node(tree, root);
            }
        }
    }

    return 0;
}

char const * max_bst(bst *tree) {
    while (tree->right != NULL) {
        tree = tree->right;
    }

    return tree->value;
}

char const * min_bst(bst *tree) {
    while (tree->left != NULL) {
        tree = tree->left;
    }

    return tree->value;
}

int find_bst(bst *tree, char const *value) {
    while (tree != NULL) {
        int cmp_value = strcmp(value, tree->value);
        if (cmp_value > 0) { // value > tree->value
            tree = tree->right;
        } else if (cmp_value < 0) {
            tree = tree->left;
        } else {
            return 1;
        }
    }

    return 0;
}

bst * successor_bst(bst *tree, char const *value, bool search_by_value) {
    bst *last_parent = NULL;
    if (search_by_value) {
        while (tree != NULL) {
            int cmp_value = strcmp(value, tree->value);
            if (cmp_value > 0) { // value > tree->value
                tree = tree->right;
            } else if (cmp_value < 0) {
                last_parent = tree;
                tree = tree->left;
            } else {
                if (tree->right != NULL) { // szukamy najmniejszej wartosci w prawym poddrzewie
                    tree = tree->right;
                    while (tree->left != NULL) {
                        tree = tree->left;
                    }

                    return tree;
                } else { // zwracamy ostatniego rodzica, u ktorego w lewym poddrzewie jest nasza wartosc
                    return last_parent;
                }
            }
        }
    } else { // na cele delete_bst()
        tree = tree->right;
        while (tree->left != NULL) {
            tree = tree->left;
        }

        return tree;
    }

    return NULL;
}

int main() {
    bst *bst_tree = create_bst();

    int lines;
    char command[10], arg[512];

    scanf("%d", &lines);
    for (int i=0; i<lines; i++) {
        scanf("%s", command);

        if (strcmp(command, "insert") == 0) {
            scanf("%s", arg);
            insert_bst(bst_tree, arg);
        } else if (strcmp(command, "load") == 0) {
            scanf("%s", arg);
            if (load_bst(bst_tree, arg) == 0) {
                printf("FILE NOT FOUND\n");
            }
        } else if (strcmp(command, "delete") == 0) {
            scanf("%s", arg);
            delete_bst(&bst_tree, arg);
        } else if (strcmp(command, "find") == 0) {
            scanf("%s", arg);
            printf("%d\n", find_bst(bst_tree, arg));
        } else if (strcmp(command, "min") == 0) {
            char const *min = min_bst(bst_tree);
            if (min != NULL) {
                printf("%s\n", min);
            } else {
                printf("Tree is empty.\n");
            }
        } else if (strcmp(command, "max") == 0) {
            char const *max = max_bst(bst_tree);
            if (max != NULL) {
                printf("%s\n", max);
            } else {
                printf("Tree is empty.\n");
            }
        } else if (strcmp(command, "successor") == 0) {
            scanf("%s", arg);
            bst *successor = successor_bst(bst_tree, arg, true);
            if (successor != NULL) {
                printf("%s\n", successor->value);
            } else {
                printf("\n");
            }
        } else if (strcmp(command, "inorder") == 0) {
            inorder_bst(bst_tree);
        }
    }
}