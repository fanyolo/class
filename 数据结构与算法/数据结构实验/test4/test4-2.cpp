#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAXN 200

void PrintArray(int a[], int n) {
    for (int i = 0; i < n; i++) printf("%4d", a[i]);
    printf("\n");
}


int IsSorted(int a[], int n) {
    for (int i = 1; i < n; i++) if (a[i-1] > a[i]) return 0;
    return 1;
}


void CopyArray(int dst[], int src[], int n) {
    for (int i = 0; i < n; i++) dst[i] = src[i];
}

//冒泡排序：无交换提前结束 
void BubbleSortPretty(int a[], int n) {
    int i, j, temp;
    int pass = 0;
    long long cmp = 0, swp = 0;
    clock_t start, end;

    printf("\n冒泡排序:每趟结果（若某趟无交换则提前结束）：\n");
    printf("初始：");
    PrintArray(a, n);

    start = clock();

    for (i = 0; i < n - 1; i++) {
        int flag = 0;
        for (j = 0; j < n - 1 - i; j++) {
            cmp++;
            if (a[j] > a[j + 1]) {
                temp = a[j]; a[j] = a[j + 1]; a[j + 1] = temp;
                swp++;
                flag = 1;
            }
        }
        pass++;
        printf("第 %d 趟：", pass);
        PrintArray(a, n);

        if (flag == 0) {  // 本趟没有发生交换，说明已经有序
            printf("（本趟无交换，排序已完成，提前结束）\n");
            break;
        }
    }

    end = clock();

    printf("结果：");
    PrintArray(a, n);
    printf("趟数=%d, 比较次数=%lld, 交换次数=%lld, 用时=%.3f ms\n",
           pass, cmp, swp, 1000.0 * (end - start) / CLOCKS_PER_SEC);
}

//插入排序：每趟输出，统计移动次数 
void InsertSortPretty(int a[], int n) {
    int i, j, key;
    int pass = 0;
    long long cmp = 0, mov = 0;
    clock_t start, end;

    printf("\n直接插入排序:每趟结果：\n");
    printf("初始：");
    PrintArray(a, n);

    start = clock();

    for (i = 1; i < n; i++) {
        key = a[i];
        j = i - 1;
        int movedThisPass = 0;

        while (j >= 0) {
            cmp++;
            if (a[j] > key) {
                a[j + 1] = a[j];
                mov++;
                movedThisPass = 1;
                j--;
            } else {
                break;
            }
        }
        a[j + 1] = key;

        pass++;
        printf("第 %d 趟：", pass);
        PrintArray(a, n);
        if (!movedThisPass) {
            printf("（本趟无需移动元素）\n");
        }

        // 如果你也想“完全有序就提前停”，打开下面两行：
        // if (IsSorted(a, n)) { printf("（整体已排序，提前结束）\n"); break; }
    }

    end = clock();

    printf("结果：");
    PrintArray(a, n);
    printf("趟数=%d, 比较次数=%lld, 移动次数=%lld, 用时=%.3f ms\n",
           pass, cmp, mov, 1000.0 * (end - start) / CLOCKS_PER_SEC);
}

//快速排序：只在数组变化时输出 
int ArraysEqual(int a[], int b[], int n) {
    for (int i = 0; i < n; i++) if (a[i] != b[i]) return 0;
    return 1;
}

int Partition(int a[], int low, int high, long long *cmp, long long *mov) {
    int pivot = a[low];
    while (low < high) {
        while (low < high) { (*cmp)++; if (a[high] >= pivot) high--; else break; }
        if (low < high) { a[low] = a[high]; (*mov)++; low++; }

        while (low < high) { (*cmp)++; if (a[low] <= pivot) low++; else break; }
        if (low < high) { a[high] = a[low]; (*mov)++; high--; }
    }
    a[low] = pivot; (*mov)++;
    return low;
}

void QuickSortCorePretty(int a[], int low, int high, int n,
                         int *cnt, long long *cmp, long long *mov) {
    if (low >= high) return;

   
    int before[MAXN];
    for (int i = 0; i < n; i++) before[i] = a[i];

    int pivot = Partition(a, low, high, cmp, mov);


    if (!ArraysEqual(before, a, n)) {
        (*cnt)++;
        printf("第 %d 次划分：", *cnt);
        PrintArray(a, n);
    }

    QuickSortCorePretty(a, low, pivot - 1, n, cnt, cmp, mov);
    QuickSortCorePretty(a, pivot + 1, high, n, cnt, cmp, mov);
}

void QuickSortPretty(int a[], int n) {
    clock_t start, end;
    int cnt = 0;
    long long cmp = 0, mov = 0;

    printf("\n快速排序:每次有效划分结果：\n");
    printf("初始：");
    PrintArray(a, n);

    start = clock();
    QuickSortCorePretty(a, 0, n - 1, n, &cnt, &cmp, &mov);
    end = clock();

    printf("结果：");
    PrintArray(a, n);
    printf("有效划分次数=%d, 比较次数=%lld, 移动次数=%lld, 用时=%.3f ms\n",
           cnt, cmp, mov, 1000.0 * (end - start) / CLOCKS_PER_SEC);
}

int main() {
    int n;
    int origin[MAXN], a[MAXN], b[MAXN], c[MAXN];

    printf("请输入 n（建议 <= 30，便于观察输出）：");
    if (scanf("%d", &n) != 1 || n <= 0 || n > MAXN) {
        printf("n 输入不合法。\n");
        return 0;
    }

    srand((unsigned)time(NULL));

    printf("\n随机生成的序列（1~999）：\n");
    for (int i = 0; i < n; i++) {
        origin[i] = rand() % 999 + 1;
        printf("%4d", origin[i]);
    }
    printf("\n");

    CopyArray(a, origin, n);
    CopyArray(b, origin, n);
    CopyArray(c, origin, n);

    BubbleSortPretty(a, n);
    InsertSortPretty(b, n);
    QuickSortPretty(c, n);

    printf("\n比较说明:\n");
    printf("1）冒泡：若某趟无交换则提前结束；一般交换多、效率低。\n");
    printf("2）插入：趟数通常为 n-1，但当序列接近有序时移动次数很少。\n");
    printf("3）快排：递归分区，平均效率高；本程序只输出有效划分避免冗余。\n");

    return 0;
}

