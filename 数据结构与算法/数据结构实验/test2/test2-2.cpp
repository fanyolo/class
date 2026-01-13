
#include <stdio.h>
#include <stdlib.h>

#define MaxSize 100
typedef char ElemType;

typedef struct node {
    ElemType data;
    struct node *lchild;
    struct node *rchild;
} BTNode;


void CreateBTree(BTNode *&b, const char *str) {
    BTNode *St[MaxSize], *p = NULL;
    int top = -1, k = 0, j = 0;
    char ch;

    b = NULL;
    ch = str[j];

    while (ch != '\0') {
        switch (ch) {
            case '(':
                St[++top] = p;   // 当前结点入栈
                k = 1;           // 接下来处理左孩子
                break;
            case ')':
                --top;           // 子树结束出栈
                break;
            case ',':
                k = 2;           // 转向处理右孩子
                break;
            default:
                p = (BTNode*)malloc(sizeof(BTNode));
                p->data = ch;
                p->lchild = p->rchild = NULL;

                if (b == NULL) {
                    b = p;       // 根结点
                } else {
                    if (k == 1) St[top]->lchild = p;
                    else if (k == 2) St[top]->rchild = p;
                }
                break;
        }
        ch = str[++j];
    }
}

// 销毁二叉树
void DestroyBTree(BTNode *&b) {
    if (b != NULL) {
        DestroyBTree(b->lchild);
        DestroyBTree(b->rchild);
        free(b);
        b = NULL;
    }
}


void AllPath1(BTNode *b, ElemType path[], int pathlen) {
    if (b != NULL) {
        // 如果 b 是叶子结点：直接输出 “叶->...->根”
        if (b->lchild == NULL && b->rchild == NULL) {
            printf("  %c到根结点逆路径：%c->", b->data, b->data);
            for (int i = pathlen - 1; i > 0; --i)
                printf("%c->", path[i]);
            if (pathlen > 0) printf("%c\n", path[0]);
            else printf("\n"); // 只有根一个结点时
        } else {
            // 非叶子：把当前结点压入祖先路径，递归扫描左右子树
            path[pathlen] = b->data;
            pathlen++;
            AllPath1(b->lchild, path, pathlen);
            AllPath1(b->rchild, path, pathlen);
        }
    }
}

void LongPath1(BTNode *b, ElemType path[], int pathlen,
               ElemType longpath[], int &longpathlen) {
    if (b == NULL) return;

    // 把当前结点加入路径（含当前结点）
    path[pathlen] = b->data;
    pathlen++;

    // 叶子：比较并更新“第一条最长路径”
    if (b->lchild == NULL && b->rchild == NULL) {
        if (pathlen > longpathlen) {
            for (int i = 0; i < pathlen; ++i)
                longpath[i] = path[i];
            longpathlen = pathlen;
        }
        return;
    }

    // 先序：先左后右
    LongPath1(b->lchild, path, pathlen, longpath, longpathlen);
    LongPath1(b->rchild, path, pathlen, longpath, longpathlen);
}


void AllPath2(BTNode *b) {
    BTNode *st[MaxSize];  // 栈保存“根->...->当前结点”路径
    int top = -1;
    BTNode *p = b;
    BTNode *r = NULL;     // r 指向刚刚访问过的结点

    while (p != NULL || top != -1) {
        // 沿左分支一路入栈
        while (p != NULL) {
            st[++top] = p;
            p = p->lchild;
        }

        // 查看栈顶
        p = st[top];

        // 若右子树不存在或已访问过，则访问该结点（后序“根”）
        if (p->rchild == NULL || p->rchild == r) {

            // 如果访问到的是叶子结点：输出叶->根逆路径
            if (p->lchild == NULL && p->rchild == NULL) {
                printf("  %c到根结点逆路径：%c->", p->data, p->data);
                for (int i = top - 1; i > 0; --i)
                    printf("%c->", st[i]->data);
                if (top > 0) printf("%c\n", st[0]->data);
                else printf("\n");
            }

            // 出栈访问
            top--;
            r = p;
            p = NULL; // 关键：防止重复走左路
        } else {
            // 转向处理右子树
            p = p->rchild;
        }
    }
}


typedef struct {
    BTNode *node;   // 队列中保存的结点指针
    int parent;     // 该结点在队列中的父结点下标（用于回溯到根）
} QNode;

void AllPath3(BTNode *b) {
    if (b == NULL) return;

    QNode Qu[MaxSize];
    int front = -1, rear = -1;

    // 根结点入队，父下标为 -1
    Qu[++rear].node = b;
    Qu[rear].parent = -1;

    while (front != rear) {
        front++;
        BTNode *cur = Qu[front].node;

        // 若为叶子：沿 parent 追溯输出叶->根逆路径
        if (cur->lchild == NULL && cur->rchild == NULL) {
            printf("  %c到根结点逆路径：", cur->data);
            int p = front;
            while (Qu[p].parent != -1) {
                printf("%c->", Qu[p].node->data);
                p = Qu[p].parent;
            }
            printf("%c\n", Qu[p].node->data);
        }

        // 左孩子入队
        if (cur->lchild != NULL) {
            Qu[++rear].node = cur->lchild;
            Qu[rear].parent = front;
        }
        // 右孩子入队
        if (cur->rchild != NULL) {
            Qu[++rear].node = cur->rchild;
            Qu[rear].parent = front;
        }
    }
}


int main() {
    BTNode *b = NULL;
    ElemType path[MaxSize], longpath[MaxSize];
    int longpathlen = 0;

    CreateBTree(b, "A(B(D,E(H(J,K(L,M(,N))))),C(F,G(,I))))");
    printf("A(B(D,E(H(J,K(L,M(,N))))),C(F,G(,I))))\n\n");


    printf("叶结点到根结点逆路径如下：\n");
    AllPath1(b, path, 0);

    // 第一条最长逆路径（先序）
    LongPath1(b, path, 0, longpath, longpathlen);
    printf("第一条最长逆路径长度：%d\n", longpathlen);
    printf("第一条最长逆路径：");
    for (int i = longpathlen - 1; i >= 0; --i) {
        printf("%c", longpath[i]);
        if (i != 0) printf("->");
    }
    printf("\n");

    printf("\n后序非递归遍历方法：\n");
    AllPath2(b);

    printf("\n层次遍历方法：\n");
    AllPath3(b);

    DestroyBTree(b);
    return 0;
}

