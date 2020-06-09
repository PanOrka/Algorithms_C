#include "rbt_functions.h"

void left_rotate(rbt *x, rbt **root) {
    rbt *y = x->right;
    x->right = y->left;
    if (y->left != NULL) {
        y->left->parent = x;
    }
    y->parent = x->parent;
    if (x->parent != NULL) {
        if (x->parent->left == x) {
            x->parent->left = y;
        } else {
            x->parent->right = y;
        }
    } else {
        *root = y;
    }
    y->left = x;
    x->parent = y;
}

void right_rotate(rbt *x, rbt **root) {
    rbt *y = x->left;
    x->left = y->right;
    if (y->right != NULL) {
        y->right->parent = x;
    }
    y->parent = x->parent;
    if (x->parent != NULL) {
        if (x->parent->left == x) {
            x->parent->left = y;
        } else {
            x->parent->right = y;
        }
    } else {
        *root = y;
    }
    y->right = x;
    x->parent = y;
}

int insertion_fix(rbt *node, rbt **root) {
    while (node->parent != NULL && node->parent->counter > 0) { // node->parent is red so not root, node->parent->parent exists
        if (node->parent == node->parent->parent->left) {
            rbt *y = node->parent->parent->right;
            if (y != NULL && y->counter > 0) { // NULL are black, we want red
                node->parent->counter = -abs(node->parent->counter); // set black
                y->counter = -abs(y->counter); // set black
                node->parent->parent->counter = abs(node->parent->parent->counter); // set red
                node = node->parent->parent;
            } else {
                if (node == node->parent->right) {
                    node = node->parent;
                    left_rotate(node, root);
                }
                node->parent->counter = -abs(node->parent->counter); // set black
                node->parent->parent->counter = abs(node->parent->parent->counter); // set red
                right_rotate(node->parent->parent, root);
            }
        } else {
            rbt *y = node->parent->parent->left;
            if (y != NULL && y->counter > 0) { // NULL are black, we want red
                node->parent->counter = -abs(node->parent->counter); // set black
                y->counter = -abs(y->counter); // set black
                node->parent->parent->counter = abs(node->parent->parent->counter); // set red
                node = node->parent->parent;
            } else {
                if (node == node->parent->left) {
                    node = node->parent;
                    right_rotate(node, root);
                }
                node->parent->counter = -abs(node->parent->counter); // set black
                node->parent->parent->counter = abs(node->parent->parent->counter); // set red
                left_rotate(node->parent->parent, root);
            }
        }
    }

    (*root)->counter = -abs((*root)->counter);
    
    return 1;
}

int deletion_fix(rbt *node, rbt *parent, rbt **root) { // Tutaj usunelismy node ktory byl czarny i przekazalismy jego non-NULL lub NULL child
    while (node == NULL || (parent != NULL && node->counter < 0)) { // if node is NULL it has parent
        if (node == parent->left) {
            rbt *w = parent->right;
            if (w != NULL && w->counter > 0) {
                w->counter = -abs(w->counter); // set black
                parent->counter = abs(parent->counter); // set red
                left_rotate(parent, root); // doesnt change parent
                w = parent->right;
            }
            if ((w->left == NULL || w->left->counter < 0) && (w->right == NULL || w->right->counter < 0)) {
                w->counter = abs(w->counter); // set red
                node = parent;
                parent = node->parent;
            } else {
                if (w->right == NULL || w->right->counter < 0) {
                    w->left->counter = -abs(w->left->counter); // set black
                    w->counter = abs(w->counter); // set red
                    right_rotate(w, root);
                    w = parent->right;
                }
                if (parent->counter > 0) {
                    w->counter = abs(w->counter); // set red
                } else {
                    w->counter = -abs(w->counter); // set black
                }
                parent->counter = -abs(parent->counter); // set black
                w->right->counter = -abs(w->right->counter); // set black
                left_rotate(parent, root);
                node = *root;
                parent = node->parent;
            }
        } else {
            rbt *w = parent->left;
            if (w != NULL && w->counter > 0) {
                w->counter = -abs(w->counter); // set black
                parent->counter = abs(parent->counter); // set red
                right_rotate(parent, root);
                w = parent->left;
            }
            if ((w->right == NULL || w->right->counter < 0) && (w->left == NULL || w->left->counter < 0)) {
                w->counter = abs(w->counter); // set red
                node = parent;
                parent = node->parent;
            } else {
                if (w->left == NULL || w->left->counter < 0) {
                    w->right->counter = -abs(w->right->counter); // set black
                    w->counter = abs(w->counter); // set red
                    left_rotate(w, root);
                    w = parent->left;
                }
                if (parent->counter > 0) {
                    w->counter = abs(w->counter); // set red
                } else {
                    w->counter = -abs(w->counter); // set black
                }
                parent->counter = -abs(parent->counter); // set black
                w->left->counter = -abs(w->left->counter); // set black
                right_rotate(parent, root);
                node = *root;
                parent = node->parent;
            }
        }
    }

    node->counter = -abs(node->counter); // set black

    return 1;
}