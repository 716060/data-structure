/*************************************************************************
	> File Name: 二插排序树.cpp
	> Author: 
	> Mail: 
	> Created Time: 2020年02月18日 星期二 15时07分46秒
 ************************************************************************/
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int key;
    struct Node *lchild, *rchild;
} Node;

Node *getNewNode(int key) {
    Node *p = (Node *)malloc(sizeof(Node));
    p->key = key;
    p->lchild = p->rchild = NULL;
    return p;
}

Node *insert(Node *root, int key) {
    if (root == NULL) return getNewNode(key);
    if (root->key == key) return root;
    if (root->key > key) {
        root->lchild = insert(root->lchild, key);
    } else {
        root->rchild = insert(root->rchild, key);
    }
    return root;
}

Node *predecessor(Node *root) {
    Node *temp = root->lchild;
    while (temp->rchild) temp = temp->rchild;
    return temp;
}

Node *earse(Node *root, int key) {
    if (root == NULL) return root;
    if (root->key > key) root->lchild = earse(root->lchild, key);
    else if (root->key < key) root->rchild = earse(root->rchild, key);
    else {
        if (root->lchild == NULL || root->rchild == NULL) {
            Node *temp = root->lchild ? root->lchild : root->rchild;
            free(root);
            return temp;
        } else {
            Node *temp = predecessor(root);
            root->key = temp->key;
            root->lchild = earse(root->lchild, key);
        }
    }
    return root;
}

void clear(Node *root) {
    if (root == NULL) return ;
    clear(root->lchild);
    clear(root->rchild);
    free(root);
    return ;
}

void __output(Node *root) {
    if (root == NULL) return ;
    __output(root->lchild);
    printf("%d ", root->key);
    __output(root->rchild);
    return ;
}

void output(Node *root) {
    printf("=============\n");
    __output(root);
    printf("\n");
    return ;
}

int main() {
    int op, val;
    Node *root = NULL;
    while (~scanf("%d%d", &op, &val)) {
        switch(op) {
            case 1: root = insert(root, val); break;
            case 2: root = earse(root, val); break;
        }
        output(root);
    }
    clear(root);
    return 0;
}
