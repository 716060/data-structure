/*************************************************************************
	> File Name: 顺序表.cpp
	> Author: 
	> Mail: 
	> Created Time: 2020年02月20日 星期四 14时36分35秒
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

typedef struct Vector {
    int *data;
    int size, length;
} Vector;

Vector *init(int n) {
    Vector *v = (Vector *)malloc(sizeof(Vector));
    v->data = (int *)malloc(sizeof(int) * n);
    v->size = n;
    v->length = 0;
    return v;
}

int expand(Vector *v) {
    int exter_size = v->size;
    int *p;
    while (exter_size) {
        p = (int *)realloc(v->data, sizeof(int) * (v->size + exter_size));
        if (p) break;
        exter_size /= 2;
    }
    if (!p) return 0;
    v->size += exter_size;
    v->data = p;
    return 1;
}

int insert(Vector *v, int ind, int val) {
    if (v == NULL) return 0;
    if (ind < 0 || ind > v->length) return 0;
    if (v->size == v->length) {
        if (!expand(v)) return 0;
        printf("expand Vector success = (%d)\n", v->size);
    }
    for (int i = v->length; i > ind; i--) {
        v->data[i] = v->data[i - 1];
    }
    v->data[ind] = val;
    v->length += 1;
    return 1;
}

int earse(Vector *v, int ind) {
    if (v == NULL) return 0;
    if (ind < 0 || ind >= v->length) return 0;
    for (int i = ind + 1; i < v->length; i++) {
        v->data[i - 1] = v->data[i];
    }
    v->length -= 1;
    return 1;
}

void clear(Vector *v) {
    if (v == NULL) return ;
    free(v->data);
    free(v);
    return ;
}

void output(Vector *v) {
    printf("Vector(%d) = [", v->length);
    for (int i = 0; i < v->length; i++) {
        i && printf(", ");
        printf("%d", v->data[i]);
    }
    printf("]\n");
}

int main() {
    srand(time(0));
    Vector *v = init(1);
    #define max_op 20
    int op, ind, val;
    for (int i = 0; i < max_op; i++) {
        op = rand() % 4;
        ind = rand() % (v->length + 3) - 1;
        val = rand() % 100;
        switch (op) {
            case 2 :
            case 3 :
            case 0 : {
                printf("insert %d at %d to Vector = %d\n", val, ind, insert(v, ind, val));
                output(v);
                printf("\n");
            } break;
            case 1 : {
                printf("earse element at %d from Vector = %d\n", ind, earse(v, ind));
                output(v);
                printf("\n");
            } break;
        }
    }
    clear(v);


    return 0;
}
