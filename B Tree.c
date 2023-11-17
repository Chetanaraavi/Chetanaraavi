#include <stdio.h>
#include <stdlib.h>
typedef struct BTreeNode {
    int *keys;
    struct BTreeNode **child;
    int leaf;  
    int n;   
} BTreeNode;

BTreeNode *createNode(int leaf) {
    BTreeNode *newNode = (BTreeNode *)malloc(sizeof(BTreeNode));
    newNode->leaf = leaf;
    newNode->keys = (int *)malloc(sizeof(int) * (2 * 2 - 1));
    newNode->child = (BTreeNode **)malloc(sizeof(BTreeNode *) * (2 * 2));
    newNode->n = 0;
    return newNode;
}

void splitChild(BTreeNode *x, int i, BTreeNode *y) {
    BTreeNode *z = createNode(y->leaf);
    z->n = 2 - 1;

    for (int j = 0; j < 2 - 1; j++)
        z->keys[j] = y->keys[j + 2];

    if (y->leaf == 0) {
        for (int j = 0; j < 2; j++)
            z->child[j] = y->child[j + 2];
    }

    y->n = 2 - 1;

    for (int j = x->n; j > i; j--)
        x->child[j + 1] = x->child[j];

    x->child[i + 1] = z;

    for (int j = x->n - 1; j >= i; j--)
        x->keys[j + 1] = x->keys[j];

    x->keys[i] = y->keys[2 - 1];
    x->n = x->n + 1;
}

void insertNonFull(BTreeNode *x, int k) {
    int i = x->n - 1;

    if (x->leaf) {
        while (i >= 0 && k < x->keys[i]) {
            x->keys[i + 1] = x->keys[i];
            i--;
        }

        x->keys[i + 1] = k;
        x->n = x->n + 1;
    } else {
        while (i >= 0 && k < x->keys[i])
            i--;

        i = i + 1;

        if (x->child[i]->n == (2 * 2 - 1)) {
            splitChild(x, i, x->child[i]);

            if (k > x->keys[i])
                i++;
        }

        insertNonFull(x->child[i], k);
    }
}

BTreeNode *insert(BTreeNode *root, int k) {
    if (root == NULL) {
        BTreeNode *newRoot = createNode(1);
        newRoot->keys[0] = k;
        newRoot->n = 1;
        return newRoot;
    }

    if (root->n == (2 * 2 - 1)) {
        BTreeNode *newRoot = createNode(0);
        newRoot->child[0] = root;
        splitChild(newRoot, 0, root);
        insertNonFull(newRoot, k);
        return newRoot;
    } else {
        insertNonFull(root, k);
        return root;
    }
}


void display(BTreeNode *root, int level) {
    if (root != NULL) {
        int i;
        for (i = 0; i < root->n; i++) {
            display(root->child[i], level + 1);
            for (int j = 0; j < level; j++)
                printf("  ");
            printf("%d\n", root->keys[i]);
        }
        display(root->child[i], level + 1);
    }
}


int search(BTreeNode *root, int k) {
    int i = 0;
    while (i < root->n && k > root->keys[i])
        i++;

    if (i < root->n && k == root->keys[i])
        return 1;

    if (root->leaf)
        return 0;

    return search(root->child[i], k);
}

int main() {
    BTreeNode *root = NULL;
    int choice, key;

    do {
        printf("1. Insert\n");
        printf("2. Display\n");
        printf("3. Search\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter key to insert: ");
                scanf("%d", &key);
                root = insert(root, key);
                break;
            case 2:
                printf("B-tree:\n");
                display(root, 0);
                break;
            case 3:
                printf("Enter key to search: ");
                scanf("%d", &key);
                if (search(root, key))
                    printf("Key found!\n");
                else
                    printf("Key not found!\n");
                break;
            case 4:
                printf("Exiting program.\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 4);

    return 0;
}
