#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int f(char *str, char xCh, int *pos) {
    int count = 0;
    int i;
    for (i = 0; str[i] !='\0'; i++) {
        if (str[i] == xCh) {
            count++;
            if (pos != NULL) {
                pos[count - 1] = i;
            }
        }
    }return count;
}
int main() {
    char str[128];
    char xCh;
    int pos[128];
    int i,count;
    while (1) {system("cls");
        printf("请输入被查找的字符串：");scanf("%s", str);
        printf("请输入待查找的字符：");scanf(" %c", &xCh);
        count = f(str, xCh, pos);
        if (count == 0) {
            printf("未找到字符%c\n", xCh);
        } else {
            printf("字符%c出现了%d次，位置分别为：", xCh, count);
            for (i = 0; i < count; i++) {
                printf("%d ", pos[i]);
            }printf("\n");
        }
    getchar();
    getchar();
    } 
    return 0;
}
