#include <stdio.h>

// 狀態碼
#define ERROR 0
#define FALSE 0
// 儲存空間初始分配量
#define MAXSIZE 20
// 狀態碼
#define OK 1
#define TRUE 1

// ElemType型別根據實際情況而定，這裡假設為 int
typedef int ElemType;
// 狀態類型
typedef int Status;
// 順序線性串列
typedef struct {
  // 陣列儲存資料元素，最大值為 MAXSIZE
  ElemType data[MAXSIZE];
  // 線性串列的目前長度
  int length;
} SqList;

// 將順序線性串列 L 中的第 i 個位置的元素值傳回給 e
Status GetElem(SqList L, int i, ElemType *e) {
  // 如果順序線性串列 L 已存在，1 ≤ i ≤ ListLength(L)
  if (L.length == 0 || i < 1 || i > L.length)
    return ERROR;
  // 用 e 傳回 L 中第 i 個資料元素的值
  *e = L.data[i - 1];

  return OK;
}

// 在順序線性串列 L 中的第 i 個位置插入新元素 e
Status ListInsert(SqList *L, int i, ElemType e) {
  // 順序線性串列已經滿
  if (L->length == MAXSIZE)
    return ERROR;

  // 當 i 比第一個位置小或比最後一位置的後一位置還要大時
  if (i < 1 || i > L->length + 1)
    return ERROR;

  // 若插入數據位置不在串列尾
  if (i <= L->length) {
    // 將要插入位置之後的數據元素向後移一位
    for (int k = L->length - 1; k >= i - 1; k--) {
      L->data[k + 1] = L->data[k];
    }
  }

  // 將新元素插入
  L->data[i - 1] = e;
  L->length++;

  return OK;
}

// 刪除順序線性串列 L 中，第 i 個位置的元素，並用 e 傳回其值
Status ListDelete(SqList *L, int i, ElemType *e) {
  // 順序線性串列為空
  if (L->length == 0)
    return ERROR;

  // 刪除位置不正確
  if (i < 1 || i > L->length)
    return ERROR;

  *e = L->data[i - 1];

  // 如果刪除的不是最後位置
  if (i < L->length) {
    // 將刪除位置的後繼元素前移
    for (int k = i; k < L->length; k++)
      L->data[k - 1] = L->data[k];
  }

  L->length--;

  return OK;
}

int main() {

  return 0;
}
