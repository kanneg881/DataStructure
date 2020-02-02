/*
 * 堆疊的順序儲存結構
 */

// 狀態碼
#define ERROR 0
// 儲存空間初始分配量
#define MAXSIZE 20
// 狀態碼
#define OK 1

// SElemType 類型根據實際情形而定，這裡假設為 int
typedef int SElemType;
// 狀態類型
typedef int Status;
typedef struct {
  SElemType data[MAXSIZE];
  // 用於堆疊頂端指標
  int top;
} SqStack;

// 刪除 S 的堆疊頂端元素，用 e 返回其值
Status Pop(SqStack *S, SElemType *e) {
  // 堆疊為空
  if (S->top == -1)
    return ERROR;

  // 將要刪除的堆疊頂端元素傳給 e
  *e = S->data[S->top];
  // 堆疊頂端指標 - 1
  S->top--;

  return OK;
}

// 插入元素 e 為新的堆疊頂端元素
Status Push(SqStack *S, SElemType e) {
  // 堆疊是滿的
  if (S->top == MAXSIZE - 1)
    return ERROR;

  // 堆疊頂端指標 + 1
  S->top++;
  // 將新插入元素推入到堆疊頂端空間
  S->data[S->top] = e;

  return OK;
}
