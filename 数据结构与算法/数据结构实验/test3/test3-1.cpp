#include <stdio.h>
#include <stdlib.h>

#define MAXV  20
#define MAXSIZE 100

typedef struct ArcNode {
    int adjvex;                 // 邻接点
    int w;                      // 权值
    struct ArcNode *nextarc;    // 下一条边
} ArcNode;

typedef struct VNode {
    ArcNode *firstarc;          // 顶点的第一条边
} VNode;

typedef struct AdjGraph {
    VNode adjlist[MAXV];        // 邻接表
    int n, e;                   // 顶点数、边数(弧数)
} AdjGraph;

int visited[MAXV];

void CreateAdjG(AdjGraph *G, int A[][MAXV], int n) {
    int i, j;
    ArcNode *p;

    G->n = n;
    G->e = 0;
    for (i = 0; i < n; i++)
        G->adjlist[i].firstarc = NULL;

    for (i = 0; i < n; i++) {
        for (j = n - 1; j >= 0; j--) {     // 从大到小扫描，配合头插
            if (A[i][j] != 0) {
                p = (ArcNode*)malloc(sizeof(ArcNode));
                if (!p) {
                    fprintf(stderr, "malloc failed\n");
                    exit(1);
                }
                p->adjvex = j;
                p->w = A[i][j];
                p->nextarc = G->adjlist[i].firstarc;
                G->adjlist[i].firstarc = p;
                G->e++;
            }
        }
    }
}

void DispEdges(AdjGraph *G) {
    int i;
    ArcNode *p;
    printf("图G的边集：\n");
    for (i = 0; i < G->n; i++) {
        p = G->adjlist[i].firstarc;
        while (p != NULL) {
            printf("%d -> %d (w=%d)\n", i, p->adjvex, p->w);
            p = p->nextarc;
        }
    }
}

void PathAll1(AdjGraph *G, int u, int v, int path[], int d) {
    ArcNode *p;
    int j, w;

    d++;
    path[d] = u;
    visited[u] = 1;

    if (u == v) {
        for (j = 0; j <= d; j++) printf("%3d", path[j]);
        printf("\n");
        visited[u] = 0;
        return;
    }

    p = G->adjlist[u].firstarc;
    while (p != NULL) {
        w = p->adjvex;
        if (visited[w] == 0)
            PathAll1(G, w, v, path, d);
        p = p->nextarc;
    }

    visited[u] = 0;
}

// 输出从u到v的所有长度为l1(边数)的简单路径
void PathAll2(AdjGraph *G, int u, int v, int l1, int path[], int d) {
    ArcNode *p;
    int j, w;

    visited[u] = 1;
    d++;
    path[d] = u;

    if (u == v && d == l1) {
        for (j = 0; j <= d; j++) printf("%3d", path[j]);
        printf("\n");
        visited[u] = 0;
        return;
    }

    // 剪枝：边数已经超过l1，或已经到l1但还没到v，都没必要再往下走
    if (d >= l1) {
        visited[u] = 0;
        return;
    }

    p = G->adjlist[u].firstarc;
    while (p != NULL) {
        w = p->adjvex;
        if (visited[w] == 0)
            PathAll2(G, w, v, l1, path, d);
        p = p->nextarc;
    }

    visited[u] = 0;
}



static void DFSPrintAllShortest(int s, int cur,
                                int pred[][MAXV], int predCnt[],
                                int path[], int len) {
    int i, k;
    path[len] = cur;

    if (cur == s) {
        // path是 v->...->s，逆序打印就是 s->...->v
        for (k = len; k >= 0; k--) printf("%3d", path[k]);
        printf("\n");
        return;
    }

    for (i = 0; i < predCnt[cur]; i++) {
        DFSPrintAllShortest(s, pred[cur][i], pred, predCnt, path, len + 1);
    }
}

void AllShortPaths(AdjGraph *G, int u, int v) {
    int dist[MAXV];
    int pred[MAXV][MAXV];
    int predCnt[MAXV];
    int q[MAXV];
    int front = 0, rear = 0;
    int i;
    ArcNode *p;

    for (i = 0; i < G->n; i++) {
        dist[i] = -1;
        predCnt[i] = 0;
    }

    dist[u] = 0;
    q[rear++] = u;

    // BFS：求dist，并记录所有最短前驱
    while (front < rear) {
        int x = q[front++];

        p = G->adjlist[x].firstarc;
        while (p != NULL) {
            int y = p->adjvex;

            if (dist[y] == -1) {
                dist[y] = dist[x] + 1;
                predCnt[y] = 0;
                pred[y][predCnt[y]++] = x;
                q[rear++] = y;
            } else if (dist[y] == dist[x] + 1) {
                if (predCnt[y] < MAXV) { // 防止越界
                    pred[y][predCnt[y]++] = x;
                }
            }

            p = p->nextarc;
        }
    }

    if (dist[v] == -1) {
        printf("无路径\n");
        return;
    }

  
    {
        int path[MAXV];
        DFSPrintAllShortest(u, v, pred, predCnt, path, 0);
    }
}

void DestroyAdjG(AdjGraph *G) {
    int i;
    ArcNode *p, *q;
    for (i = 0; i < G->n; i++) {
        p = G->adjlist[i].firstarc;
        while (p != NULL) {
            q = p->nextarc;
            free(p);
            p = q;
        }
        G->adjlist[i].firstarc = NULL;
    }
}

int main() {
    int i;
    int u = 5, v = 2, l1 = 3;
    int path[MAXV];
    AdjGraph G;

    int A[MAXV][MAXV] = {0};
    int n = 6;

    A[0][1] = 1; A[0][3] = 1;
    A[1][2] = 1;
    A[2][0] = 1; A[2][5] = 1;
    A[3][2] = 1; A[3][5] = 1;
    A[4][3] = 1;
    A[5][0] = 1; A[5][1] = 1; A[5][3] = 1; A[5][4] = 1;

    CreateAdjG(&G, A, n);

    DispEdges(&G);  

    printf("\n(1)从顶点%d到%d的所有路径：\n", u, v);
    for (i = 0; i < MAXV; i++) visited[i] = 0;
    PathAll1(&G, u, v, path, -1);

    printf("\n(2)从顶点%d到%d的所有长度为%d(边数)的路径：\n", u, v, l1);
    for (i = 0; i < MAXV; i++) visited[i] = 0;
    PathAll2(&G, u, v, l1, path, -1);

    printf("\n(3)从顶点%d到%d的所有最短路径：\n", u, v);
    AllShortPaths(&G, u, v);  

    DestroyAdjG(&G);
    return 0;
}

