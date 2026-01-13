#include <stdio.h>
#include "clinklist.cpp"   

int main() {
    LinkNode *h = NULL;
    ElemType e = 0;

    // 1. 初始化循环链表 h
    printf("（1）初始化循环链表 h\n");
    InitList(h);

    // 2. 依次采用尾插法插入 a、b、c、d、e 元素
    printf("（2）依次采用尾插法插入 a、b、c、d、e 元素\n");
    ElemType arr[] = {'a', 'b', 'c', 'd', 'e'}; 
    CreateListR(h, arr, 5);

    // 3. 输出循环链表 h
    printf("（3）输出循环链表 h: ");
    DispList(h);

    // 4. 输出循环链表 h 的长度
    printf("（4）循环链表 h 长度: %d\n", ListLength(h));

    // 5. 判断循环链表 h 是否为空
    printf("（5）循环链表 h 是否为空: %s\n", ListEmpty(h) ? "是" : "否");

    // 6. 输出循环链表 h 的第 3 个元素
    if (GetElem(h, 3, e)) {
        printf("（6）循环链表 h 的第 3 个元素: %c\n", (char)e);
    } else {
        printf("（6）获取第 3 个元素失败\n");
    }

    // 7. 输出元素 a 的位置
    int pos = LocateElem(h, 'a');
    printf("（7）元素 a 的位置: %d\n", pos);

    // 8. 在第 4 个元素的位置上插入 f 元素
    if (ListInsert(h, 4, 'f')) {
        printf("（8）在第 4 个元素的位置上插入 f 元素\n");
    } else {
        printf("（8）插入失败\n");
    }

    // 9. 输出循环链表 h
    printf("（9）输出循环链表 h: ");
    DispList(h);

    // 10. 删除循环链表 h 的第 3 个元素
    if (ListDelete(h, 3, e)) {
        printf("（10）删除循环链表 h 的第 3 个元素: %c\n", (char)e);
    } else {
        printf("（10）删除第 3 个元素失败\n");
    }

    // 11. 输出循环链表 h
    printf("（11）输出循环链表 h: ");
    DispList(h);

    // 12. 释放循环单链表 h
    DestroyList(h);
    printf("（12）释放循环链表 h\n");

    return 0;
}

