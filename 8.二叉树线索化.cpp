/*************************************************************************
	> File Name: 二叉树线索化.cpp
	> Author: 
	> Mail: 
	> Created Time: 2020年02月25日 星期二 14时08分06秒
 ************************************************************************/

#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
#include <map>
#include <cmath>
#include <queue>
#include <ctime>
#include <cstdlib>
#define NORMAL 0
#define THREAD 1
using namespace std;

typedef struct Node {
    int key;
    int ltag, rtag;
    struct Node *lchild, *rchild;
} Node;

Node *getNewNode(int val) {
    Node *p = (Node *)malloc(sizeof(Node));
    p->key = val;
    p->lchild = p->rchild = NULL;
    p->ltag = p->rtag = NORMAL;
    return p;
}

Node *insert(Node *node, int val) {
    if (node == NULL) return getNewNode(val);
    if (node->key == val) return node;
    if (node->key > val) node->lchild = insert(node->lchild, val);
    else node->rchild = insert(node->rchild, val);
    return node;
}

void build_thread(Node *root) {
    if (root == NULL) return ;
    static Node *pre = NULL;
    build_thread(root->lchild);
    if (root->lchild == NULL) {
        root->lchild = pre;
        root->ltag = THREAD;
    }
    if (pre != NULL && pre->rchild == NULL) {
        pre->rchild = root;
        pre->rtag = THREAD;
    }
    pre = root;
    build_thread(root->rchild);
    return ;
}

void clear(Node *node) {
    if (node == NULL) return ;
    if (node->ltag == NORMAL) clear(node->lchild);
    if (node->rtag == NORMAL) clear(node->rchild);
    free(node);
    return ;
}

void __in_order(Node *node) {
    if (node == NULL) return ;
    if (node->ltag == NORMAL) __in_order(node->lchild);
    printf("%d ", node->key);
    if (node->rtag == NORMAL) __in_order(node->rchild);
}

void in_order(Node *node) {
    if (node == NULL) return ;
    __in_order(node);
    printf("\n");
}

Node *most_left(Node *p) {
    while (p && p->ltag == NORMAL && p->lchild) p = p->lchild;
    return p;
}

void __output(Node *node) {
    Node *p = most_left(node);
    while (p) {
        printf("%d ", p->key);
        if (p->rtag == THREAD) {
            p = p->rchild;
        } else {
            p = most_left(p->rchild);
        }
    }
    return ;
}

void output(Node *node) {
    __output(node);
    printf("\n");
}

int main() {
    srand(time(0));
    #define max_op 20
    Node *root = NULL;
    for (int i = 0; i < max_op; i++) {
        int val = rand() % 100;
        root = insert(root, val);
    }
    build_thread(root);
    in_order(root);
    output(root);
    return 0;
}
