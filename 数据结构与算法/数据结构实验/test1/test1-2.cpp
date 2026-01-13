#include <iostream>
using namespace std;

#define M 4
#define N 4
#define MaxSize 100

// 1=墙, 0=路; 外围加一圈1作边框
int mg[M + 2][N + 2] = {
    {1,1,1,1,1,1},
    {1,0,0,0,1,1},
    {1,0,1,0,0,1},
    {1,0,0,0,1,1},
    {1,1,0,0,0,1},
    {1,1,1,1,1,1}
};

struct Node {
    int i, j;
    int di; // 方向索引
};

Node St[MaxSize], Path[MaxSize];
int top = -1;
int countPath = 1;
int minlen = MaxSize;

// 方向：上、右、下、左
int dii[4] = {-1, 0, 1, 0};
int djj[4] = {0, 1, 0, -1};

// 打印坐标序列
void printCoords(const Node st[], int len) {
    for (int k = 0; k < len; k++)
        cout << "(" << st[k].i << "," << st[k].j << ") ";
    cout << "\n";
}

// 打印迷宫（#=墙, 空格=路, *=路径）
void printMazeWithPath(const Node st[], int len) {
    int show[M + 2][N + 2];
    for (int i = 0; i < M + 2; i++)
        for (int j = 0; j < N + 2; j++)
            show[i][j] = mg[i][j];

    for (int k = 0; k < len; k++) {
        show[st[k].i][st[k].j] = 2;
    }

    for (int i = 1; i <= M; i++) {
        for (int j = 1; j <= N; j++) {
            if (show[i][j] == 1) cout << "# ";
            else if (show[i][j] == 2) cout << "* ";
            else cout << "  ";
        }
        cout << "\n";
    }
}

// 同时输出：坐标 + 迷宫图
void printBoth(const Node st[], int len) {
    cout << "坐标序列：";
    printCoords(st, len);
    cout << "迷宫标记（#墙, *路径）：\n";
    printMazeWithPath(st, len);
}

void dispapath() {
    int len = top + 1;
    cout << "第" << countPath++ << "条路径：\n";
    printBoth(St, len);
    cout << "\n";

    if (len < minlen) {
        for (int k = 0; k < len; k++) Path[k] = St[k];
        minlen = len;
    }
}

// 输出第一条最短路径
void dispminpath() {
    cout << "最短路径如下：\n";
    cout << "长度：" << minlen << "\n";
    printBoth(Path, minlen);
}

// 非递归 DFS + 回溯
void mgpath(int xi, int yi, int xe, int ye) {
    int i, j, i1, j1, di;
    bool find;

    top++;
    St[top].i = xi; St[top].j = yi; St[top].di = -1;
    mg[xi][yi] = -1; // 已走

    while (top > -1) {
        i = St[top].i; j = St[top].j;
        di = St[top].di;

        // 到达出口
        if (i == xe && j == ye) {
            dispapath();
            mg[i][j] = 0;     // 恢复出口
            top--;            // 回退
            continue;
        }

        find = false;
        while (di < 3 && !find) {
            di++;
            i1 = i + dii[di];
            j1 = j + djj[di];
            if (mg[i1][j1] == 0) find = true;
        }

        if (find) {
            St[top].di = di;          // 更新当前格已尝试方向
            top++;
            St[top].i = i1; St[top].j = j1; St[top].di = -1;
            mg[i1][j1] = -1;          // 进栈并标记走过
        } else {
            mg[i][j] = 0;             // 死路，恢复为可走
            top--;
        }
    }

    dispminpath();
}

int main() {
    cout << "迷宫所有路径如下：\n\n";
    mgpath(1, 1, M, N);
    return 0;
}

