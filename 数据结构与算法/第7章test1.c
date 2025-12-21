#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    char data;
    struct node *lchild, *rchild;
} BTNode;

// 创建新结点
BTNode *newNode(char ch) {
    BTNode *p = (BTNode *)malloc(sizeof(BTNode));
    p->data = ch;
    p->lchild = p->rchild = NULL;
    return p;
}

/*********** 1. 先序遍历思路 ***********/
int LnodeNum_Pre(BTNode *b, int k) {
    if (b == NULL || k <= 0)
        return 0;
    if (k == 1)
        return 1;
    return LnodeNum_Pre(b->lchild, k - 1)
         + LnodeNum_Pre(b->rchild, k - 1);
}

/*********** 2. 层次遍历思路（队列） ***********/
#define MaxSize 100

typedef struct {
    BTNode *data[MaxSize];
    int front, rear;
} SqQueue;

void InitQueue(SqQueue *q)      { q->front = q->rear = 0; }
int  QueueEmpty(SqQueue *q)     { return q->front == q->rear; }
int  EnQueue(SqQueue *q, BTNode *x) {
    if ((q->rear + 1) % MaxSize == q->front) return 0;
    q->rear = (q->rear + 1) % MaxSize;
    q->data[q->rear] = x;
    return 1;
}
int  DeQueue(SqQueue *q, BTNode **x) {
    if (QueueEmpty(q)) return 0;
    q->front = (q->front + 1) % MaxSize;
    *x = q->data[q->front];
    return 1;
}
int  QueueLength(SqQueue *q) {
    return (q->rear - q->front + MaxSize) % MaxSize;
}

int LnodeNum_Level(BTNode *b, int k) {
    if (b == NULL || k <= 0) return 0;

    SqQueue q;
    InitQueue(&q);
    EnQueue(&q, b);
    int level = 1;

    while (!QueueEmpty(&q)) {
        int count = QueueLength(&q);   // 当前层结点数
        if (level == k)                // 到达目标层
            return count;

        int i;
        for (i = 0; i < count; i++) {
            BTNode *p;
            DeQueue(&q, &p);
            if (p->lchild) EnQueue(&q, p->lchild);
            if (p->rchild) EnQueue(&q, p->rchild);
        }
        level++;
    }
    return 0;
}

/*********** 主函数：构造测试树并验证 ***********/
int main() {
 
    BTNode *A = newNode('A');
    BTNode *B = newNode('B');
    BTNode *C = newNode('C');
    BTNode *D = newNode('D');
    BTNode *E = newNode('E');
    BTNode *F = newNode('F');
    BTNode *G = newNode('G');

    A->lchild = B; A->rchild = C;
    B->lchild = D; B->rchild = E;
    C->lchild = F; C->rchild = G;

    printf("测试二叉树：A 为根，第二层 B 和 C，第三层 D E F G\n\n");

    int k;
    for (k = 1; k <= 5; k++) {
        int n1 = LnodeNum_Pre(A, k);
        int n2 = LnodeNum_Level(A, k);
        printf("k = %d: 先序算法 = %d,  层次算法 = %d\n", k, n1, n2);
    }

    return 0;
}

