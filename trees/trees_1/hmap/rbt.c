#include "rbt_functions.h"

void bfs_traversal(rbt *tree) { // max 100 in queue
    rbt *queue[100];
    queue[0] = tree;
    int check_index = 0;
    int add_index = 1;
    while (queue[check_index] != NULL) {
        if (check_index == add_index) {
            break;
        }

        if (queue[check_index] == tree) {
            if (check_index == 0) {
                printf("%s (%d)\n", queue[check_index]->value, queue[check_index]->counter);
            } else {
                printf("NULL\n");
                check_index++;
                continue;
            }
        } else {
            printf("%s (%d)\n", queue[check_index]->value, queue[check_index]->counter);
        }
        if (queue[check_index]->left != NULL) {
            queue[add_index] = queue[check_index]->left;
        } else {
            queue[add_index] = tree;
        }
        add_index++;
        
        if (queue[check_index]->right != NULL) {
            queue[add_index] = queue[check_index]->right;
        } else {
            queue[add_index] = tree;
        }
        add_index++;

        check_index++;
    }
}

void inorder_rbt(rbt *tree) {
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

int load_rbt(rbt **root, char const *dir) {
    FILE *file = fopen(dir, "r");

    if (file != NULL) {
        char k = fgetc(file);
        char *str = malloc(sizeof(char)*100); // MALLOC
        while (k != EOF) {
            for (int i=0; i<100; i++) {
                if (k == ' ' || k == '\n') {
                    *(str+i) = '\0';
                    if (i > 0) {
                        insert_rbt(root, str);
                    }
                    k = fgetc(file);

                    break;
                } else if (k == EOF) {
                    *(str+i) = '\0';
                    if (i > 0) {
                        insert_rbt(root, str);
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

int insert_rbt(rbt **root, char const *string_to_add) {
    rbt *tree = *root;

    if (tree->value == NULL) {
        tree->value = string_to_add;
        tree->counter = -1; // adding as black
        return 1;
    } else {
        bool root_flag = tree->was_visited;
        while (true) {
            int cmp_value = strcmp(string_to_add, tree->value);
            if (cmp_value > 0) { // string_to_add > tree->value
                if (tree->right != NULL) {
                    tree = tree->right;
                } else {
                    rbt *new_node = malloc(sizeof(rbt)); // MALLOC
                    new_node->parent = tree;
                    new_node->left = NULL;
                    new_node->right = NULL;
                    new_node->value = string_to_add;
                    new_node->counter = 1; // adding as red
                    new_node->was_visited = root_flag;

                    tree->right = new_node;
                    return insertion_fix(new_node, root);
                }
            } else if (cmp_value < 0) { // string_to_add < tree->value
                if (tree->left != NULL) {
                    tree = tree->left;
                } else {
                    rbt *new_node = malloc(sizeof(rbt)); // MALLOC
                    new_node->parent = tree;
                    new_node->left = NULL;
                    new_node->right = NULL;
                    new_node->value = string_to_add;
                    new_node->counter = 1; // adding as red
                    new_node->was_visited = root_flag;

                    tree->left = new_node;
                    return insertion_fix(new_node, root);
                }
            } else {
                if (tree->counter > 0) {
                    tree->counter++; // red
                } else {
                    tree->counter--; // black
                }
                free((void *)string_to_add);
                return 1;
            }
        }
    }
}

rbt * successor_rbt(rbt *tree, char const *value, bool search_by_value) {
    rbt *last_parent = NULL;
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
    } else { // na cele delete_rbt()
        tree = tree->right;
        while (tree->left != NULL) {
            tree = tree->left;
        }

        return tree;
    }

    return NULL;
}

/*
// Podprocedura delete_rbt()
*/
int delete_node(rbt *node, rbt **root) {
    int original_node_color = node->counter;

    if (node->left == NULL) { // left is NULL, right can be NULL
        rbt *x = node->right;
        rbt *parent = node->parent;
        
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

        if (original_node_color < 0) {
            return deletion_fix(x, parent, root);
        }
    } else if (node->right == NULL) { // right is NULL, left is not NULL
        rbt *x = node->left;
        rbt *parent = node->parent;

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

        if (original_node_color < 0) {
            return deletion_fix(x, parent, root);
        }
    } else { // both aren't NULL
        rbt *swap = successor_rbt(node, node->value, false);
        free((void *)node->value);
        node->value = swap->value; // ustalamy succesora (a musi istniec), bierzemy jego wartosc i usuwamy go z drzewa
        if (node->counter > 0) { // then is red
            node->counter = abs(swap->counter);
        } else { // then is black
            node->counter = -abs(swap->counter);
        }
        swap->value = NULL;
        return delete_node(swap, root);
    }

    return 1;
}

int delete_rbt(rbt **root, char const *value) {
    rbt *tree = *root;
    while (tree != NULL) {
        int cmp_value = strcmp(value, tree->value);
        if (cmp_value > 0) { // value > tree->value
            tree = tree->right;
        } else if (cmp_value < 0) {
            tree = tree->left;
        } else {
            if (tree->counter > 1) {
                tree->counter--;
                return 1;
            } else if (tree->counter < -1) {
                tree->counter++;
                return 1;
            } else {
                return delete_node(tree, root);
            }
        }
    }

    return 0;
}

char const * max_rbt(rbt *tree) {
    while (tree->right != NULL) {
        tree = tree->right;
    }

    return tree->value;
}

char const * min_rbt(rbt *tree) {
    while (tree->left != NULL) {
        tree = tree->left;
    }

    return tree->value;
}

int find_rbt(rbt *tree, char const *value) {
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

rbt * create_rbt() {
    rbt *ptr = (rbt *)malloc(sizeof(rbt));
    ptr->parent = NULL;
    ptr->left = NULL;
    ptr->right = NULL;
    ptr->value = NULL;
    ptr->counter = 0;
    ptr->was_visited = false;

    return ptr;
}