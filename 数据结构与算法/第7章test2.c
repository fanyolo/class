#include <stdio.h>
#include <stdlib.h>

/* 二叉链结点结构 */
typedef struct node {
    char data;
    struct node *lchild, *rchild;
} BTNode;

/* 创建新结点 */
BTNode *newNode(char ch) {
    BTNode *p = (BTNode *)malloc(sizeof(BTNode));
    p->data = ch;
    p->lchild = p->rchild = NULL;
    return p;
}


BTNode *Locate(BTNode *b, char x) {
    BTNode *p;
    if (b == NULL)
        return NULL;
    if (b->data == x)
        return b;

    p = Locate(b->lchild, x);
    if (p != NULL)
        return p;

    return Locate(b->rchild, x);
}


int DepthInSubtree(BTNode *root, char x) {
    int d;
    if (root == NULL)
        return 0;
    if (root->data == x)
        return 1;

   
    d = DepthInSubtree(root->lchild, x);
    if (d > 0)
        return d + 1;

    
    d = DepthInSubtree(root->rchild, x);
    if (d > 0)
        return d + 1;

    return 0;  
}


int descendant(BTNode *b, char x, char y) {
    BTNode *py;  
    int d;       

   
    py = Locate(b, y);
    if (py == NULL) {
        
        return 0;
    }

  
    d = DepthInSubtree(py, x);

    if (d == 0) {

        return 0;
    }
    if (d == 1) {
      
        return 0;
    }

 
    return d - 1;
}


int main() {

    BTNode *A = newNode('A');
    BTNode *B = newNode('B');
    BTNode *C = newNode('C');
    BTNode *D = newNode('D');
    BTNode *E = newNode('E');
    BTNode *F = newNode('F');
    BTNode *G = newNode('G');

    A->lchild = B;  A->rchild = C;
    B->lchild = D;  B->rchild = E;
    C->lchild = F;  C->rchild = G;

    printf("测试二叉树：A 为根，第二层 B 和 C，第三层 D E F G\n\n");


    char testX[] = {'D', 'E', 'C', 'A', 'B', 'X', 'D'};
    char testY[] = {'B', 'A', 'A', 'A', 'D', 'A', 'X'};
    int n = 7;
    int i;

    for (i = 0; i < n; i++) {
        char x = testX[i];
        char y = testY[i];
        int gen = descendant(A, x, y);
        if (gen == 0) {
            printf("x = %c, y = %c:  x 不是 y 的子孙（或 x/y 不存在）\n", x, y);
        } else {
            printf("x = %c, y = %c:  x 是 y 的第 %d 代子孙\n", x, y, gen);
        }
    }

    return 0;
}

