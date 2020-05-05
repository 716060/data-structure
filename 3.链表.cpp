/*************************************************************************
	> File Name: 顺序表.cpp
	> Author: 
	> Mail: 
	> Created Time: 2020年02月20日 星期四 14时11分56秒
 ************************************************************************/

#include <iostream>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <map>
#include <cmath>
#include <queue>
#include <ctime>

using namespace std;

typedef struct ListNode {
    int data;
    struct ListNode *next;
}ListNode;

typedef struct List {
    ListNode head;
    int length;
}List;

ListNode *init_ListNode(int val) {
    ListNode *p = (ListNode *)malloc(sizeof(ListNode));
    p->data = val;
    p->next = NULL;
    return p;
}

List *init_List() {
    List *l = (List *)malloc(sizeof(List));
    l->head.next = NULL;
    l->length = 0;
    return l;
}

int insert(List *l, int ind, int val) {
    if (l == NULL) return 0;
    if (ind < 0 || ind > l->length) return 0;
    ListNode *p = &(l->head), *node = init_ListNode(val);
    while (ind--) p = p->next;
    node->next = p->next;
    p->next = node;
    l->length += 1;
    return 1;
}

int earse(List *l, int ind) {
    if (l == NULL) return 0;
    if (ind < 0 || ind >= l->length) return 0;
    ListNode *p = &(l->head), *q;
    while (ind--) p = p->next;
    q = p->next;
    p->next = q->next;
    free(q);
    l->length -= 1;
    return 1;
}

void clear_node(ListNode *node) {
    if (node == NULL) return ;
    free(node);
    return ;
}

void clear_list(List *l) {
    if (l == NULL) return ;
    ListNode *p = l->head.next, *q;
    while (p) {
        q = p->next;
        clear_node(p);
        p = q;
    }
    free(l);
    return ;
}

void output(List *l) {
    printf("List(%d) = [", l->length);
    for (ListNode *p = l->head.next; p; p = p->next) {
        printf("%d -> ", p->data);
    }
    printf("NULL ]\n");
    return ;
}

int main() {
    srand(time(0));
    #define max_op 20
    int op, ind, val;
    List *l = init_List();
    for (int i = 0; i < max_op; i++) {
        op = rand() % 4;
        ind = rand() % (l->length + 3) - 1;
        val = rand() % 100;
        switch (op) {
            case 0 :
            case 1 :
            case 2 : {
                printf("insert %d at %d to List = %d\n", val, ind, insert(l, ind, val));
                output(l);
                printf("\n");
            } break;
            case 3 : {
                printf("earse iterm st %d from List = %d\n", ind, earse(l, ind));
                output(l);
                printf("\n");
            } break;
        }
    }
    clear_list(l);

    return 0;
}
