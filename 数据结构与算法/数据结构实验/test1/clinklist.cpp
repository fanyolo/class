#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef int ElemType;

typedef struct LNode {
    ElemType data;
    struct LNode *next;
} LinkNode;

// 1. 初始化循环链表
void InitList(LinkNode *&L) {
    L = (LinkNode *)malloc(sizeof(LinkNode));
    if (!L) return;
    L->next = L;  // 指向自己形成循环
}

// 2. 尾插法创建/追加循环链表（更稳：可在已有链表末尾继续追加）
void CreateListR(LinkNode *&L, const ElemType a[], int n) {
    if (L == NULL) InitList(L);
    if (L == NULL) return;

    LinkNode *r = L;
    // 找到当前尾结点
    while (r->next != L) r = r->next;

    for (int i = 0; i < n; i++) {
        LinkNode *s = (LinkNode *)malloc(sizeof(LinkNode));
        if (!s) return;
        s->data = a[i];
        s->next = L;     // 关键：始终保持循环结构
        r->next = s;
        r = s;
    }
}

// 3. 输出循环链表（按字符显示：a b c...）
void DispList(LinkNode *L) {
    if (L == NULL || L->next == L) {
        printf("空链表\n");
        return;
    }
    LinkNode *p = L->next;
    while (p != L) {
        printf("%c ", (char)p->data);
        p = p->next;
    }
    printf("\n");
}

// 4. 获取循环链表长度
int ListLength(LinkNode *L) {
    if (L == NULL) return 0;
    int len = 0;
    LinkNode *p = L->next;
    while (p != L) {
        len++;
        p = p->next;
    }
    return len;
}

// 5. 判断循环链表是否为空
bool ListEmpty(LinkNode *L) {
    return (L == NULL) || (L->next == L);
}

// 6. 获取第i个元素（1-based）
bool GetElem(LinkNode *L, int i, ElemType &e) {
    if (L == NULL || i < 1) return false;
    LinkNode *p = L->next;
    int j = 1;
    while (p != L && j < i) {
        p = p->next;
        j++;
    }
    if (p == L) return false;
    e = p->data;
    return true;
}

// 7. 查找元素e的位置（1-based，找不到返回0）
int LocateElem(LinkNode *L, ElemType e) {
    if (L == NULL) return 0;
    LinkNode *p = L->next;
    int i = 1;
    while (p != L) {
        if (p->data == e) return i;
        p = p->next;
        i++;
    }
    return 0;
}

// 8. 在第i个位置插入元素e（1-based，可在尾部插入 i=len+1）
bool ListInsert(LinkNode *&L, int i, ElemType e) {
    if (L == NULL || i < 1) return false;

    LinkNode *p = L;
    int j = 0;  // 头结点视作第0个

    // 找到第i-1个结点
    while (p->next != L && j < i - 1) {
        p = p->next;
        j++;
    }
    if (j != i - 1) return false; // i 超界

    LinkNode *s = (LinkNode *)malloc(sizeof(LinkNode));
    if (!s) return false;

    s->data = e;
    s->next = p->next;
    p->next = s;
    return true;
}

// 9. 删除第i个元素（1-based）
bool ListDelete(LinkNode *&L, int i, ElemType &e) {
    if (L == NULL || i < 1) return false;

    LinkNode *p = L;
    int j = 0;

    // 找到第i-1个结点
    while (p->next != L && j < i - 1) {
        p = p->next;
        j++;
    }
    if (p->next == L || j != i - 1) return false; // i 超界/不存在

    LinkNode *q = p->next;
    e = q->data;
    p->next = q->next;
    free(q);
    return true;
}

// 10. 释放循环链表
void DestroyList(LinkNode *&L) {
    if (L == NULL) return;

    LinkNode *p = L->next;
    while (p != L) {
        LinkNode *q = p;
        p = p->next;
        free(q);
    }
    free(L);
    L = NULL;
}

