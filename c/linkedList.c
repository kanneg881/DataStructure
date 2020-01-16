#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// 狀態碼
#define ERROR 0
// 狀態碼
#define OK 1

// ElemType型別根據實際情況而定，這裡假設為 int
typedef int ElemType;
// 狀態類型
typedef int Status;
// 線性串列的單鏈節串列儲存結構
typedef struct node {
  ElemType data;
  struct node *next;
} Node;
// 定義 LinkList
typedef Node *LinkList;

// 將 L 重置為空串列
Status ClearList(LinkList *L) {
  LinkList p, q;

  // p 指向第一個節點
  p = (*L)->next;

  while (p) {
    q = p->next;
    free(p);
    p = q;
  }

  // 首節點指標欄位為空
  (*L)->next = NULL;

  return OK;
}

// 隨機產生 n 個元素的值，建立一個有首節點的單向鏈結串列 L (頭插法)
void CreateListHead(LinkList *L, int n) {
  LinkList p;
  int i;

  *L = (LinkList)malloc(sizeof(Node));
  // 先建立一個有首節點的單向鏈結串列
  (*L)->next = NULL;

  for (i = 0; i < n; i++) {
    // 產生新節點
    p = (LinkList)malloc(sizeof(Node));
    // 隨機產生 100 以內的數字
    p->data = arc4random() % 100 + 1;
    p->next = (*L)->next;
    // 插入到串列的前端
    (*L)->next = p;
  }
}

// 隨機產生 n 個元素的值，建立一個有首節點的單向鏈結串列 L (尾插法)
void CreateListTail(LinkList *L, int n) {
  LinkList p, r;
  int i;

  // L 為整個鏈結串列
  *L = (LinkList)malloc(sizeof(Node));
  // r 為指向尾部的節點
  r = *L;

  for (i = 0; i < n; i++) {
    // 產生新節點
    p = (Node *)malloc(sizeof(Node));
    // 隨機產生 100 以內的數字
    p->data = arc4random() % 100 + 1;
    // 將尾端節點的指標指向新節點
    r->next = p;
    // 將目前的新節點定義為尾端節點
    r = p;
  }

  // 表示目前鏈結串列結束
  r->next = NULL;
}

// 用 e 傳回 L 中第 i 個資料元素的值
Status GetElem(LinkList L, int i, ElemType *e) {
  // 計數器
  int j;
  // 宣告一個指標 p
  LinkList p;

  // 讓 p 指向鏈結串列 L 的第一個節點
  p = L->next;
  j = 1;

  // p 不為空，並且計數器 j 還沒有等於 i 時，迴圈繼續
  while (p && j < i) {
    // 讓 p 指向下一個節點
    p = p->next;
    ++j;
  }

  // 第 i 個元素不存在
  if (!p || j > i)
    return ERROR;

  // 取得第 i 個元素的資料
  *e = p->data;

  return OK;
}

// 刪除 L 的第 i 個資料元素，並用 e 傳回其值，L 的長度減 1
Status ListDelete(LinkList *L, int i, ElemType *e) {
  int j;
  LinkList p, q;

  p = *L;
  j = 1;

  // 尋找第 i 個節點
  while (p->next && j < i) {
    p = p->next;
    ++j;
  }

  // 第 i 個元素不存在
  if (!(p->next) || j > i)
    return ERROR;

  q = p->next;
  // 將 q 的後繼變成 p 的後繼
  p->next = q->next;
  // 將 q 節點中的資料給 e
  *e = q->data;
  // 讓系統回收此節點，釋放記憶體
  free(q);

  return OK;
}

// 在 L 中第 i 個位置之前插入新的資料元素 e，L 的長度加 1
Status ListInsert(LinkList *L, int i, ElemType e) {
  int j;
  LinkList p, s;

  p = *L;
  j = 1;

  // 尋找第 i 個節點
  while (p && j < i) {
    p = p->next;
    ++j;
  }

  // 第 i 個元素不存在
  if (!p || j > i)
    return ERROR;

  // 產生新節點(C 語言標準函式)
  s = (LinkList)malloc(sizeof(Node));
  s->data = e;
  // 將 p 的後繼節點變成 s 的後繼
  s->next = p->next;
  // 將 s 變成 p 的後繼
  p->next = s;

  return OK;
}

int main() {}
