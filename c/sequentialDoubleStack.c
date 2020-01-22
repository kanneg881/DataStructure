/*
 * 兩堆疊共用空間
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
// 兩堆疊共用空間結構
typedef struct {
  SElemType data[MAXSIZE];
  // 堆疊 1 堆疊頂端指標
  int top1;
  // 堆疊 2 堆疊頂端指標
  int top2;
} SqDoubleStack;

// 刪除 S 的堆疊頂端元素
Status Pop(SqDoubleStack *S, SElemType *e, int stackNumber) {
  if (stackNumber == 1) {
    // 說明堆疊 1 已經是空堆疊，溢出
    if (S->top1 == -1)
      return ERROR;

    // 將堆疊 1 的堆疊頂端元素出堆疊
    *e = S->data[S->top1--];
  } else if (stackNumber == 2) {
    // 說明堆疊 2 已經是空堆疊，溢出
    if (S->top2 == MAXSIZE)
      return ERROR;

    // 將堆疊 2 的堆疊頂端元素出堆疊
    *e = S->data[S->top2++];
  }

  return OK;
}

// 插入元素 e 為新的堆疊頂端元素
Status Push(SqDoubleStack *S, SElemType e, int stackNumber) {
  // 堆疊已滿，不能再 push 新元素了
  if (S->top1 + 1 == S->top2)
    return ERROR;
  // 堆疊 1 有元素進堆疊
  if (stackNumber == 1)
    // 若是堆疊 1，則先 top1 + 1 後再給陣列元素傳值
    S->data[++S->top1] = e;
  // 堆疊 2 有元素進堆疊
  else if (stackNumber == 2)
    // 若是堆疊 2，則先 top1 - 1 後再給陣列元素傳值
    S->data[--S->top2] = e;

  return OK;
}
