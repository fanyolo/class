#include <stdio.h>
#include <stdlib.h>

#define MaxSize 100
typedef char ElemType;          // 结点数据类型

// 二叉链结点结构定义
typedef struct node {
    ElemType data;              // 数据域
    struct node *lchild;        // 指向左孩子
    struct node *rchild;        // 指向右孩子
} BTNode;


void CreateBTree(BTNode *&b, const char *str) {
    BTNode *St[MaxSize], *p = NULL;   
    int top = -1, k = 0, j = 0;       // top为栈顶指针，k表示孩子方向，j为字符串下标
    char ch;

    b = NULL;                       
    ch = str[j];

    while (ch != '\0') {             
        switch (ch) {
            case '(':
                St[++top] = p;       
                k = 1;               
                break;
            case ')':
                --top;               
                break;
            case ',':
                k = 2;               
                break;
            default:
            
                p = (BTNode*)malloc(sizeof(BTNode));
                p->data = ch;
                p->lchild = p->rchild = NULL;

                if (b == NULL) {
                    b = p;         
                } else {
           
                    if (k == 1) St[top]->lchild = p;
                    else if (k == 2) St[top]->rchild = p;
                }
                break;
        }
        ch = str[++j];              
    }
}

//销毁二叉树


void DestroyBTree(BTNode *&b) {
    if (b != NULL) {
        DestroyBTree(b->lchild);      // 释放左子树
        DestroyBTree(b->rchild);      // 释放右子树
        free(b);                      // 释放根结点
        b = NULL;
    }
}


BTNode* FindNode(BTNode *b, ElemType x) {
    BTNode *p;
    if (b == NULL) return NULL;        // 空树
    if (b->data == x) return b;        // 找到结点
    p = FindNode(b->lchild, x);        // 在左子树中查找
    if (p != NULL) return p;
    return FindNode(b->rchild, x);     // 在右子树中查找
}


BTNode* LchildNode(BTNode *p) {
    if (p == NULL) return NULL;
    return p->lchild;
}


BTNode* RchildNode(BTNode *p) {
    if (p == NULL) return NULL;
    return p->rchild;
}


int BTHeight(BTNode *b) {
    int lh, rh;
    if (b == NULL) return 0;           // 空树高度为0
    lh = BTHeight(b->lchild);          // 左子树高度
    rh = BTHeight(b->rchild);          // 右子树高度
    return (lh > rh) ? (lh + 1) : (rh + 1);
}


void DispBTree(BTNode *b) {
    if (b != NULL) {
        printf("%c", b->data);         // 输出根结点
        if (b->lchild != NULL || b->rchild != NULL) {
            printf("(");
            DispBTree(b->lchild);      // 输出左子树
            if (b->rchild != NULL) printf(",");
            DispBTree(b->rchild);      // 输出右子树
            printf(")");
        }
    }
}

