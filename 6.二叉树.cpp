/*************************************************************************
	> File Name: 二叉树.cpp
	> Author: 
	> Mail: 
	> Created Time: 2020年02月22日 星期六 14时19分23秒
 ************************************************************************/

#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
#include <map>
#include <cmath>
#include <queue>
#include <cstdlib>
#include <ctime>
using namespace std;

typedef struct Node {
    int val;
    struct Node *lchild, *rchild;
} Node;

typedef struct Tree {
    Node *root;
    int n;
}Tree;

Node *getNewNode(int val) {
    Node *p = (Node *)malloc(sizeof(Node));
    p->rchild = p->lchild = NULL;
    p->val = val;
    return p;
}

Tree *getNewTree() {
    Tree *tree = (Tree *)malloc(sizeof(Tree));
    tree->root = NULL;
    tree->n = 0;
}

Node *insertNode(Node *root, int val, int *flag) {
    if (root == NULL) {
        *flag = 1;
        return getNewNode(val);
    } 
    if (root->val == val) return root;
    if (root->val > val) root->lchild = insertNode(root->lchild, val, flag);
    else root->rchild = insertNode(root->rchild, val, flag);
    return root;
}

void insert(Tree *tree, int val) {
    int flag = 0;
    tree->root = insertNode(tree->root, val, &flag);
    tree->n += flag;
    return ;
}


void clearNode(Node *node) {
    if (node == NULL) return ;
    clearNode(node->lchild);
    clearNode(node->rchild);
    free(node);
    return ;
}

void clearTree(Tree *tree) {
    if (tree == NULL) return ;
    clearNode(tree->root);
    free(tree);
    return ;
}

void in_orderNode(Node *node) {
    if (node == NULL) return ;
    in_orderNode(node->lchild);
    printf("%d ", node->val);
    in_orderNode(node->rchild);
    return ;
}

void in_order(Tree *tree) {
    printf("in_order(%d) = ", tree->n);
    in_orderNode(tree->root);
    printf("\n");
}



int main() {
    srand(time(0));
    Tree *tree = getNewTree();
    #define max_op 10
    for (int i = 0; i < max_op; i++) {
        int val = rand() % 100;
        insert(tree, val);
        //output(tree);
    }
    in_order(tree);
    clearTree(tree);

    return 0;
}
