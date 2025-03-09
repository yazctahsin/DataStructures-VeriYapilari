#include <stdio.h>
#include <stdlib.h>

#define RED 1
#define BLACK 0

struct red_black_node {
    int key;
    int colour;
    struct red_black_node *left, *right, *parent;
};

struct red_black_tree {
    struct red_black_node *root;
};

struct red_black_node* red_black_dugum_olustur(int key) {
    struct red_black_node *d = (struct red_black_node*)malloc(sizeof(struct red_black_node));
    if (d == NULL) {
        printf("Heapte gerekli yer ayrilamadi... exit ...\n");
        exit(1);
    }
    d->key = key;
    d->left = d->right = d->parent = NULL;
    d->colour = RED;
    return d;
}

void left_rotate(struct red_black_tree *T, struct red_black_node *x) {
    struct red_black_node *y = x->right;
    x->right = y->left;
    if (y->left != NULL) y->left->parent = x;
    y->parent = x->parent;
    if (x->parent == NULL) T->root = y;
    else if (x == x->parent->left) x->parent->left = y;
    else x->parent->right = y;
    y->left = x;
    x->parent = y;
}

void right_rotate(struct red_black_tree *T, struct red_black_node *x) {
    struct red_black_node *y = x->left;
    x->left = y->right;
    if (y->right != NULL) y->right->parent = x;
    y->parent = x->parent;
    if (x->parent == NULL) T->root = y;
    else if (x == x->parent->right) x->parent->right = y;
    else x->parent->left = y;
    y->right = x;
    x->parent = y;
}

void red_black_tree_ekle(struct red_black_tree *T, int key) {
    struct red_black_node *z = red_black_dugum_olustur(key);
    struct red_black_node *y = NULL;
    struct red_black_node *x = T->root;
    while (x != NULL) {
        y = x;
        if (z->key < x->key) x = x->left;
        else x = x->right;
    }
    z->parent = y;
    if (y == NULL) T->root = z;
    else if (z->key < y->key) y->left = z;
    else y->right = z;
    z->colour = RED;
}

void red_black_tree_preorder_yardimci(struct red_black_node *root) {
    if (root == NULL) return;
    printf("%5d", root->key);
    if (root->colour == RED) printf("(R)");
    else printf("(B)");
    red_black_tree_preorder_yardimci(root->left);
    red_black_tree_preorder_yardimci(root->right);
}

void red_black_tree_preorder(struct red_black_tree *T) {
    red_black_tree_preorder_yardimci(T->root);
    printf("\n");
}

int main() {
    struct red_black_tree T = { NULL };
    red_black_tree_ekle(&T, 10);
    red_black_tree_ekle(&T, 20);
    red_black_tree_ekle(&T, 30);
    red_black_tree_ekle(&T, 40);
    red_black_tree_ekle(&T, 50);
    red_black_tree_preorder(&T);
    return 0;
}
