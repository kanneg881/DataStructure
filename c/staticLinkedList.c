/*
 * 線性表的靜態鏈結串列儲存結構
 */

#include <stdio.h>

// 狀態碼
#define ERROR 0
// 假設鏈結串列的最大長度是 1000
#define MAXSIZE 1000
// 狀態碼
#define OK 1

// ElemType型別根據實際情況而定，這裡假設為 int
typedef int ElemType;
// 狀態類型
typedef int Status;
typedef struct {
  ElemType data;
  // 游標(Cursor)，為 0 時表示無指向
  int cur;
} Component, StaticLinkList[MAXSIZE];

/*
 * 若備用空間鏈結串列為非空，則傳回分配的節點編號，否則傳回 0
 */
int Malloc_SLL(StaticLinkList space) {
  /*
   * 目前陣列中，第一個元素的 cur 的內含值
   * 就是要傳回的第一個備用空間的編號
   */
  int i = space[0].cur;

  if (space[0].cur)
    /*
     * 由於要拿出一個分量來使用
     * 所以就得把它的下一個
     * 分量用來做備用
     */
    space[0].cur = space[i].cur;

  return i;
}

/*
 * 將一維陣列 space 中，各分量鏈結成一個備用鏈結串列，
 * space[0].cur 為首指標，0 表示空指標
 */
Status InitList(StaticLinkList space) {
  int i;

  for (i = 0; i < MAXSIZE; i++)
    space[i].cur = i + 1;

  // 目前靜態鏈結串列為空，最後一個元素的 cur 為 0
  space[MAXSIZE - 1].cur = 0;

  return OK;
}

/*
 * 將編號為 k 的空閒節點回收到備用鏈結串列
 */
void Free_SSL(StaticLinkList space, int k) {
  // 把第一個元素的 cur 值傳給要刪除的分量 cur
  space[k].cur = space[0].cur;
  // 把要刪除的分量編號傳給第一個元素的 cur
  space[0].cur = k;
}

/*
 * 傳回 L 中資料元素的個數
 */
int ListLength(StaticLinkList L) {
  int j = 0;
  int i = L[MAXSIZE - 1].cur;

  while (i) {
    i = L[i].cur;
    j++;
  }

  return j;
}

/*
 * 刪除在 L 中第 i 個資料元素 e
 */
Status ListDelete(StaticLinkList L, int i) {
  int j, k;
  if (i < 1 || i > ListLength(L))
    return ERROR;

  k = MAXSIZE - 1;

  for (j = 0; j <= i - 1; j++)
    k = L[k].cur;

  j = L[k].cur;
  L[k].cur = L[j].cur;
  Free_SSL(L, j);

  return OK;
}

/*
 * 在 L 中第 i 個位置之前插入新的資料元素 e
 */
Status ListInsert(StaticLinkList L, int i, ElemType e) {
  int j, k, l;
  // 注意 k 首先是最後一個元素的編號
  k = MAXSIZE - 1;

  if (i < 1 || i > ListLength(L) + 1)
    return ERROR;

  // 獲得空閒分量的編號
  j = Malloc_SLL(L);

  if (j) {
    return ERROR;
  }

  // 將資料傳給此分量的 data
  L[j].data = e;

  // 找到第 i 個元素之前的位置
  for (l = 1; l < i - 1; l++)
    k = L[k].cur;

  // 把第 i 個元素之前的 cur 傳給新元素的 cur
  L[j].cur = L[k].cur;
  // 把新元素的編號傳給第 i 個元素之前元素的 cur
  L[k].cur = j;

  return OK;
}
