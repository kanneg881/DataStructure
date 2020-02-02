/*
 * 堆疊的鏈結儲存結構
 */

#include <stdlib.h>

// 狀態碼
#define ERROR 0
// 狀態碼
#define OK 1

// SElemType 類型根據實際情形而定，這裡假設為 int
typedef int SElemType;
// 狀態類型
typedef int Status;

typedef struct StackNode {
  SElemType data;
  struct StackNode *next;
} StackNode, *LinkStackPtr;

typedef struct LinkStack {
  LinkStackPtr top;
  int count;
} LinkStack;

// 刪除 S 的堆疊頂元素，用 e 返回其值
Status Pop(LinkStack *S, SElemType *e) {
  LinkStackPtr p;

  if (StackEmpty(*S))
    return ERROR;

  *e = (*S).top->data;
  // 將堆疊頂節點傳給p
  p = (*S).top;
  // 使得堆疊頂指標下移一位，指向後一節點
  (*S).top = (*S).top->next;

  // 釋放節點 p
  free(p);
  (*S).count--;

  return OK;
}

// 插入元素 e 為新的堆疊頂元素
Status Push(LinkStack *S, SElemType e) {
  LinkStackPtr s = (LinkStackPtr)malloc(sizeof(StackNode));
  s->data = e;
  // 把目前的堆疊頂元素傳給新節點的直接後繼者
  s->next = S->top;
  // 將新的節點 s 傳給堆疊頂指標
  S->top = s;
  S->count++;

  return OK;
}
