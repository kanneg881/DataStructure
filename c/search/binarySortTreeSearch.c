// 二元樹的二元鏈結串列節點結構定義

#include <stddef.h>
#include <stdlib.h>

#define FALSE 0
#define TRUE 1

typedef int Status;

// 節點結構
typedef struct BiTNode {
  // 節點資料
  int data;
  // 左右孩子指標
  struct BiTNode *lchild, *rchild;
} BiTNode, *BiTree;

// 從二元搜尋樹中刪除節點 p，並重接它的左或右子樹
Status Delete(BiTree *p) {
  BiTree q, s;

  // 右子樹空則只需重接它的左子樹
  if ((*p)->rchild == NULL) {
    q = *p;
    *p = (*p)->lchild;
    free(q);
  }
  // 只需重接它的右子樹
  else if ((*p)->lchild == NULL) {
    q = *p;
    *p = (*p)->rchild;
    free(q);
  }
  // 左右子樹均不空
  else {
    q = *p;
    s = (*p)->lchild;

    // 轉左側，然後向右側直到盡頭（找待刪節點的前驅）
    while (s->rchild) {
      q = s;
      s = s->rchild;
    }
    // s 指向被刪節點的直接前驅
    (*p)->data = s->data;

    if (q != *p)
      // 重接 q 的右子樹
      q->rchild = s->lchild;
    else
      // 重接 q 的左子樹
      q->lchild = s->lchild;
    free(s);
  }
  return TRUE;
}

/*
 * 若二元搜尋樹 T 中存在鍵值等於 key 的資料元素時，則刪除
 * 該資料元素節點，並回傳 TRUE，否則回傳 FALSE。
 */
Status DeleteBST(BiTree *T, int key) {
  // 不存在鍵值等於 key 的資料元素
  if (!*T)
    return FALSE;
  else {
    // 找到鍵值等於 key 的資料元素
    if (key == (*T)->data)
      return Delete(T);
    else if (key < (*T)->data)
      return DeleteBST(&(*T)->lchild, key);
    else
      return DeleteBST(&(*T)->rchild, key);
  }
}

/*
 * 遞迴搜尋二元搜尋樹 T 中是否存在 key
 * 指標 f 指向 T 的雙親，其初始調用值為 NULL
 * 若搜尋成功，則指標 p 指向該資料元素節點，並回傳 TRUE
 * 否則指標 p 指向搜尋路徑上訪問的最後一個節點並回傳 FALSE
 */
Status SearchBST(BiTree T, int key, BiTree f, BiTree *p) {
  // 搜尋不成功
  if (!T) {
    *p = f;

    return FALSE;
  }
  // 搜尋成功
  else if (key == T->data) {
    *p = T;

    return TRUE;
  } else if (key < T->data)
    // 在左子樹中繼續搜尋
    return SearchBST(T->lchild, key, T, p);
  else
    // 在右子樹中繼續搜尋
    return SearchBST(T->rchild, key, T, p);
}

/*
 * 當二元搜尋樹 T 中不存在鍵值等於 key 的資料元素時
 * 插入 key 並回傳 TRUE，否則回傳 FALSE
 */
Status InsertBST(BiTree *T, int key) {
  BiTree p, s;

  // 搜尋不成功
  if (!SearchBST(*T, key, NULL, &p)) {
    s = (BiTree)malloc(sizeof(BiTNode));
    s->data = key;
    s->lchild = s->rchild = NULL;

    if (!p)
      // 插入 s 為新的跟節點
      *T = s;
    else if (key < p->data)
      // 插入 s 為左孩子
      p->lchild = s;
    else
      // 插入 s 為右孩子
      p->rchild = s;

    return TRUE;
  } else
    // 樹中已經有鍵值相同的節點，不再插入
    return FALSE;
}

int main(void) {
  int i;
  int a[10] = {62, 88, 58, 47, 35, 73, 51, 99, 37, 93};
  BiTree T = NULL;

  for (i = 0; i < 10; i++)
    InsertBST(&T, a[i]);

  return 0;
}
