#include <cstdio>
#include <cstdlib>

const int MAXV = 1010;
const int INF  = 0x3f3f3f3f;

int n, m;
int D[MAXV][MAXV], C[MAXV][MAXV];   // D: 距离(长度)  C: 花费
int s, t;

// Dijkstra：
void Dijkstra() {
    int dist[MAXV], cost[MAXV];
    int S[MAXV];                   
    int mindist, u;

    // 初始化 dist / cost / S
    for (int i = 1; i <= n; i++) {
        dist[i] = D[s][i];
        cost[i] = C[s][i];
        S[i] = 0;
    }
    dist[s] = 0;
    cost[s] = 0;
    S[s] = 1;

    // 主循环：执行 n-1 次
    for (int i = 1; i <= n - 1; i++) {
        mindist = INF;
        u = -1;

        // 在未加入S集合的点中，找 dist 最小的点 u
        for (int j = 1; j <= n; j++) {
            if (S[j] == 0 && dist[j] < mindist) {
                mindist = dist[j];
                u = j;
            }
        }

        // 找不到可达点，结束
        if (u == -1 || mindist == INF) break;

        // 将 u 加入 S 集合
        S[u] = 1;

        // 用 u 去松弛其他点
        for (int v = 1; v <= n; v++) {
            if (S[v] == 0 && D[u][v] < INF) {
                int d = dist[u] + D[u][v];
                int c = cost[u] + C[u][v];

                // 距离更短，更新
                if (d < dist[v]) {
                    dist[v] = d;
                    cost[v] = c;
                }
                // 距离相同，花费更小，更新
                else if (d == dist[v] && c < cost[v]) {
                    cost[v] = c;
                }
            }
        }
    }

   
    printf("\n求解说明\n");

    printf("规则：优先最短距离；若最短距离有多条路径，则取花费最少的一条\n");
    printf("起点：%d  终点：%d\n", s, t);

    printf("\n求解结果\n");
    if (dist[t] >= INF) {
        printf("从 %d 到 %d 不存在可达路径！\n", s, t);
    } else {
        printf("最短距离：%d\n", dist[t]);
        printf("对应花费：%d\n", cost[t]);
       
    }
  
}

int main() {
   
    if (freopen("test3-2.txt", "r", stdin) == NULL) {
        printf("无法打开 .txt，请确认文件与程序在同一目录。\n");
        return 0;
    }

    // 读 n, m
    if (scanf("%d%d", &n, &m) != 2) {
        printf("读取 n,m 失败，请检查 .txt 第一行格式。\n");
        return 0;
    }

    printf("读取数据说明\n");
    printf("\n数据格式：\n");
    printf("第一行：n m（点编号 1~n）\n");
    printf("接着 m 行：a b d p（无向边a-b，长度d，花费p）\n");
    printf("最后一行：s t（起点s，终点t）\n");
    

    printf("\n读取到：n = %d, m = %d\n", n, m);

    // 初始化矩阵为 INF（无边）
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            D[i][j] = INF;
            C[i][j] = INF;
        }
        D[i][i] = 0;
        C[i][i] = 0;
    }

    // 读取 m 条边
    int cnt = 0;
    for (int i = 0; i < m; i++) {
        int a, b, d, p;
        if (scanf("%d%d%d%d", &a, &b, &d, &p) != 4) {
            printf("第 %d 条边读取失败，请检查 .txt。\n", i + 1);
            return 0;
        }

        printf("第 %d 条边：(%d, %d)  长度=%d  花费=%d\n", ++cnt, a, b, d, p);

        // 无向图：对称赋值
      
        if (d < D[a][b] || (d == D[a][b] && p < C[a][b])) {
            D[a][b] = D[b][a] = d;
            C[a][b] = C[b][a] = p;
        }
    }

    // 读取 s, t
    if (scanf("%d%d", &s, &t) != 2) {
        printf("读取起点终点 s,t 失败，请检查 .txt 最后一行格式。\n");
        return 0;
    }
    printf("起点：%d  终点：%d\n", s, t);

    // 求解
    Dijkstra();

    return 0;
}

