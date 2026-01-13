#include <stdio.h>
#include <stdlib.h>


typedef struct BSTNode {
    int key;
    struct BSTNode *lchild;
    struct BSTNode *rchild;
} BSTNode;

BSTNode* NewNode(int x) {
    BSTNode* p = (BSTNode*)malloc(sizeof(BSTNode));
    p->key = x;
    p->lchild = p->rchild = NULL;
    return p;
}


void InsertBST(BSTNode* &root, int x) {
    if (root == NULL) {
        root = NewNode(x);
        return;
    }
    BSTNode* cur = root;
    while (1) {
        if (x < cur->key) {
            if (cur->lchild == NULL) {
                cur->lchild = NewNode(x);
                return;
            }
            cur = cur->lchild;
        } else if (x > cur->key) {
            if (cur->rchild == NULL) {
                cur->rchild = NewNode(x);
                return;
            }
            cur = cur->rchild;
        } else {
            return; // 忽略重复
        }
    }
}


int IsValidSearchSequence(BSTNode* root, int a[], int m) {
    if (root == NULL || m <= 0) return 0;
    if (a[0] != root->key) return 0;

    BSTNode* cur = root;
    for (int i = 1; i < m; i++) {
        if (cur->lchild && cur->lchild->key == a[i])
            cur = cur->lchild;
        else if (cur->rchild && cur->rchild->key == a[i])
            cur = cur->rchild;
        else
            return 0;
    }
    return 1;
}

void DestroyBST(BSTNode* &root) {
    if (root) {
        DestroyBST(root->lchild);
        DestroyBST(root->rchild);
        free(root);
        root = NULL;
    }
}

void PrintSeq(int a[], int m) {
    for (int i = 0; i < m; i++) printf("%d ", a[i]);
}

int main() {
    BSTNode* bt = NULL;

    /* ===== 4层左右的BST ===== */
    int data[] = {50, 30, 70, 20, 40, 60, 80, 10, 25, 35, 45};
    int n = sizeof(data) / sizeof(data[0]);

    for (int i = 0; i < n; i++)
        InsertBST(bt, data[i]);

    printf("已构造二叉排序树 bt（共 %d 个结点，约 4 层）：\n", n);
    PrintSeq(data, n);
    printf("\n\n");

  
    int t1[] = {50, 30, 20, 10};
    int t2[] = {50, 30, 40, 45};
    int t3[] = {50, 70, 60};
    int t4[] = {50, 70, 80};

    int t5[] = {50, 20};        // 跳层
    int t6[] = {30, 20};        // 非根开始
    int t7[] = {50, 30, 70};    // 中途换分支
    int t8[] = {50, 30, 99};    // 不存在
    int t9[] = {50, 40, 35};    // 孙子当孩子

    int* tests[] = {t1,t2,t3,t4,t5,t6,t7,t8,t9};
    int lens[]   = {4,4,3,3,2,2,3,3,3};

    printf("\n查找序列合法性判定\n");
    for (int i = 0; i < 9; i++) {
        printf("序列 %d：", i + 1);
        PrintSeq(tests[i], lens[i]);
        printf("\n结果：%s\n\n",
               IsValidSearchSequence(bt, tests[i], lens[i]) ? "YES" : "NO");
    }
   

    DestroyBST(bt);
    return 0;
}

