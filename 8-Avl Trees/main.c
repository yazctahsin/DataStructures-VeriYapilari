#include <stdio.h>
#include <stdlib.h>

// Agac dügümü
struct node {
    int key;
    struct node *left, *right;
    int height;
};

// Yeni dügüm olusturma
struct node *newNode(int key) {
    struct node *node = (struct node *)malloc(sizeof(struct node));
    node->key = key;
    node->left = node->right = NULL;
    node->height = 1;
    return node;
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

int height(struct node *N) {
    return (N == NULL) ? 0 : N->height;
}

// right rotate
struct node *rightRotate(struct node *y) {
    struct node *x = y->left;
    struct node *T = x->right;
    x->right = y;
    y->left = T;
    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;
    return x;
}

// left rotate
struct node *leftRotate(struct node *x) {
    struct node *y = x->right;
    struct node *T = y->left;
    y->left = x;
    x->right = T;
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;
    return y;
}

// Denge degeri
int getBalance(struct node *n) {
    return (n == NULL) ? 0 : height(n->left) - height(n->right);
}

// AVL agacına ekleme (dengeye göre rotate)
struct node *insert(struct node *node, int key) {
    if (node == NULL)
        return newNode(key);

    if (key < node->key)
        node->left = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);
    else
        return node;

    node->height = max(height(node->left), height(node->right)) + 1;

    int balance = getBalance(node);

    // Sol-Sol durumu
    if (balance > 1 && key < node->left->key)
        return rightRotate(node);

    // Sag-Sag durumu
    if (balance < -1 && key > node->right->key)
        return leftRotate(node);

    // Sol-Sag durumu
    if (balance > 1 && key > node->left->key) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // Sag-Sol durumu
    if (balance < -1 && key < node->right->key) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

// preOrder dolasma
void preOrder(struct node *root) {
    if (root != NULL) {
        printf("%d ", root->key);
        preOrder(root->left);
        preOrder(root->right);
    }
}

// Min dugumu bulma
struct node *minValueNode(struct node *node) {
    struct node *current = node;
    while (current && current->left != NULL)
        current = current->left;
    return current;
}

// Dugum silme
struct node *deleteNode(struct node *root, int key) {
    if (root == NULL)
        return root;

    if (key < root->key)
        root->left = deleteNode(root->left, key);
    else if (key > root->key)
        root->right = deleteNode(root->right, key);
    else {
        if (root->left == NULL || root->right == NULL) {
            struct node *temp = root->left ? root->left : root->right;
            if (temp == NULL) {
                temp = root;
                root = NULL;
            } else {
                *root = *temp;
            }
            free(temp);
        } else {
            struct node *temp = minValueNode(root->right);
            root->key = temp->key;
            root->right = deleteNode(root->right, temp->key);
        }
    }

    if (root == NULL)
        return root;

    root->height = max(height(root->left), height(root->right)) + 1;

    int balance = getBalance(root);

    // Sol-Sol durumu
    if (balance > 1 && getBalance(root->left) >= 0)
        return rightRotate(root);

    // Sol-Sag durumu
    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    // Sag-Sag durumu
    if (balance < -1 && getBalance(root->right) <= 0)
        return leftRotate(root);

    // Sag-Sol durumu
    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

int main() {
    struct node *root = NULL;

    root = insert(root, 80);
    root = insert(root, 40);
    root = insert(root, 10);
    root = insert(root, 60);
    root = insert(root, 70);
    root = insert(root, 90);
    root = insert(root, 20);
    root = insert(root, 50);
    root = insert(root, 55);

    printf("Preorder dolasma: \n");
    preOrder(root);

    root = deleteNode(root, 80);
    root = deleteNode(root, 90);
    root = deleteNode(root, 10);
    root = deleteNode(root, 40);
    root = deleteNode(root, 55);
    root = deleteNode(root, 60);
    root = deleteNode(root, 50);

    printf("\nPreorder dolasma(silmeden sonra): \n");
    preOrder(root);

    return 0;
}
