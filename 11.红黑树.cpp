/*************************************************************************
	> File Name: 红黑树.cpp
	> Author: 
	> Mail: 
	> Created Time: 2020年02月17日 星期一 14时20分28秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#define RED 0 
#define BLACK 1  
#define DOUBLE_BLACK 2 

typedef struct Node {
    int key, color;
    struct Node *lchild, *rchild;
}Node;

Node __NIL;
#define NIL (&__NIL)

__attribute__((constructor))
void init_NIL() {
    NIL->key = 0;
    NIL->rchild = NIL->rchild = NIL;
    NIL->color = BLACK;
    return ;
}



Node *getNewNode(int key) {
    Node *p = (Node *)malloc(sizeof(Node));
    p->key = key;
    p->lchild = p->rchild = NIL;
    p->color = RED;
    return p;
}

Node *right_rotate(Node *root) {
    Node *temp = root->lchild;
    root->lchild = temp->rchild;
    temp->rchild = root;
    return temp;
}

Node *left_rotate(Node *root) {
    Node *temp = root->rchild;
    root->rchild = temp->lchild;
    temp->lchild = root;
    return temp;
}

int hasRedChild(Node *root) {
    return root->lchild->color == RED || root->rchild->color == RED;
}

Node *earse_maintain(Node *root) {
    if (root->lchild->color != DOUBLE_BLACK && root->rchild->color != DOUBLE_BLACK) {
        return root;
    }
    if (hasRedChild(root)) {
        root->color = RED;
        root = root->lchild->color ? left_rotate(root) : right_rotate(root);
        root->color = BLACK;
        if (root->lchild->color == RED) {
            root->lchild = earse_maintain(root->lchild);
        } else {
            root->rchild = earse_maintain(root->rchild);
        }
        return root;
    }
    if (root->lchild->color == DOUBLE_BLACK) {
        if (!hasRedChild(root->lchild)) {
            root->lchild->color -= 1;
            root->rchild->color -= 1;
            root->color += 1;
            return root;
        }
        if (root->rchild->rchild->color != RED) {
            root->rchild->color = RED;
            root->rchild = right_rotate(root->rchild);
            root->rchild->color = BLACK;
        }
        root->lchild->color -= 1;
        root->rchild->color = root->color;
    } else {
        if (!hasRedChild(root->lchild)) {
            root->lchild->color -= 1;
            root->rchild->color -= 1;
            root->color += 1;
            return root;
        }
        if (root->lchild->lchild->color != RED) {
            root->lchild->color = RED;
            root->lchild = left_rotate(root->lchild);
            root->lchild->color = BLACK;
        }
        root->rchild->color -= 1;
        root->lchild->color = root->color;
    }
    root = right_rotate(root);
    root->lchild->color = root->rchild->color = BLACK;
    return root;
}

Node *insert_maintain(Node *root) {
    if (!hasRedChild(root)) return root;
    if (root->lchild->color == RED && root->rchild == RED) {
        if (!hasRedChild(root->lchild) && !hasRedChild(root->rchild)) return root;
        goto red_up;
    }
    if (root->lchild->color == RED && hasRedChild(root->lchild)) {
        if (root->lchild->rchild->color == RED) {
            root->lchild = left_rotate(root->lchild);
        }
        root = right_rotate(root);
    } else if (root->rchild->color == RED && hasRedChild(root->rchild)) {
        if (root->rchild->lchild->color == RED) {
            root->rchild = right_rotate(root->rchild);
        }
        root = left_rotate(root);
    } else {
        return root;
    }
red_up:
    root->color = RED;
    root->lchild->color = root->rchild->color = BLACK;
    return root;
}

Node *__insert(Node *root, int key) {
    if (root == NIL) return getNewNode(key);
    if (root->key == key) return root;
    if (root->key < key) root->rchild = __insert(root->rchild, key);
    else {
        root->lchild = __insert(root->lchild, key);
    }
    root = insert_maintain(root);
    return root;
}

Node *insert(Node *root, int key) {
    root = __insert(root, key);
    return root;
}

Node *predecessor(Node *root) {
    Node *temp = root->lchild;
    while (temp->rchild) temp = temp->rchild;
    return temp;
}

Node *__earse(Node *root, int key) {
    if (root == NIL) return root;
    if (root->key < key) root->rchild = __earse(root->rchild, key);
    else if (root->key > key) {
        root->lchild = __earse(root->lchild, key);
    } else {
        if (root->lchild == NIL || root->rchild == NIL) {
            Node *temp = root->lchild == NIL ? root->rchild : root->lchild;
            temp->color += root->color;
            free(root);
            return temp;
        } else {
            Node *temp = predecessor(root);
            root->key = temp->key;
            root->lchild = __earse(root->lchild, temp->key);
        }
    }
    root = earse_maintain(root);
    return root;
}

Node *earse(Node *root, int key) {
    root = __earse(root, key);
    root->color = BLACK;
    return root;
}

void clear(Node *root) {
    if (root == NIL) return ;
    clear(root->lchild);
    clear(root->rchild);
    free(root);
    return ;
}

void __output(Node *root) {
    if (root == NIL) return ;
    printf("(%d | %d %d %d)\n", root->color, root->key, root->lchild->key, root->rchild->key);
    __output(root->lchild);
    __output(root->rchild);
    return ;
}

void output(Node *root) {
    printf("\n======red black tree=====\n");
    __output(root);
    printf("NIL color : %d\n", NIL->color);
    return ;
}

int main() {
    int op, val;
    Node *root = NIL;
    while (~scanf("%d%d", &op, &val)) {
        switch(op) {
            case 1: {
                printf("insert %d to red black tree!\n", val);
                root = insert(root, val);
            } break;
            case 2: {
                printf("earse %d from red black tree!\n", val);
                root = earse(root, val);
            } break;
            default : break;
        }
        output(root);
    }

    return 0;
}
