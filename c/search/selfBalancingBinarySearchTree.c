// AVL 平衡二元樹

#include <stdio.h>
#include <stdlib.h>

// 等高
#define EH 0
#define FALSE 0
// 左高
#define LH +1
// 右高
#define RH -1
#define TRUE 1

// Status 是函數的型態，其值是函數結果狀態碼，如 OK 等
typedef int Status;

// 節點結構
typedef struct BiTNode {
  // 節點資料
  int data;
  // 節點的平衡因子
  int bf;
  // 左右孩子指標
  struct BiTNode *lchild, *rchild;
} BiTNode, *BiTree;

/*
 * 對以 P 為根的二元排序作左旋轉處理，
 * 處理之後，P 指向新的樹根節點，及旋轉處理之前的右子樹的根節點0
 */
void L_Rotate(BiTree *P) {
  BiTree R;
  // R 指向 P 的右子樹根節點
  R = (*P)->rchild;
  // R 的左子樹掛接為 P 的右子樹
  (*P)->rchild = R->lchild;
  R->lchild = (*P);
  // P 指向新的根節點
  *P = R;
}

/*
 * 對以 p 為根的二元搜尋樹做右旋轉處理，
 * 處理之後，p 指向新的樹根節點，及旋轉處理之前的左子樹的根節點
 */
void R_Rotate(BiTree *P) {
  BiTree L;
  // L 指向 P 的左子樹根節點
  L = (*P)->lchild;
  // L 的右子樹掛接為 p 的左子樹
  (*P)->lchild = L->rchild;
  L->rchild = (*P);
  // P 指向新的根節
  *P = L;
}

/*
 * 對以指標 T 所指節點為根的二元樹作左旋轉平衡處理，
 * 本演算法結束時，指標 T 指向新的根節點
 */
void LeftBalance(BiTree *T) {
  BiTree L, Lr;
  // L 指向 T 的左子樹根節點
  L = (*T)->lchild;

  // 檢查 T 的左子樹的平衡度，並作相應的平衡處理
  switch (L->bf) {
  // 新節點插入在 T 的左孩子的左子樹上，要做單右旋轉處理
  case LH:
    (*T)->bf = L->bf = EH;
    R_Rotate(T);
    break;
  // 新節點插入在 T 的左孩子的右子樹上，要做雙旋轉處理
  case RH:
    // Lr 指向 T 的左孩子的右子樹的根節點
    Lr = L->rchild;

    // 修改 T 及其左孩子的平衡因子
    switch (Lr->bf) {
    case LH:
      (*T)->bf = L->bf = EH;
      R_Rotate(T);
      break;
    case EH:
      (*T)->bf = L->bf = EH;
      break;
    case RH:
      (*T)->bf = EH;
      L->bf = LH;
      break;
    }
    Lr->bf = EH;
    // 對 T 的左子樹作左旋轉平衡處理
    L_Rotate(&(*T)->lchild);
    // 對 T 做右旋轉平衡處理
    R_Rotate(T);
  }
}

/*
 * 對以指標 T 所指節點為根的二元樹作右旋轉平衡處理，
 * 本演算法結束時，指標 T 指向新的根節點
 */
void RightBalance(BiTree *T) {
  BiTree R, Rl;
  // R 指向 T 的右子樹根節點
  R = (*T)->rchild;

  // 檢查 T 的右子樹的平衡度，並作相應的平衡處理
  switch (R->bf) {
  // 新節點插入在 T 的右孩子的右子樹上，要做單左旋轉處理
  case RH:
    (*T)->bf = R->bf = EH;
    L_Rotate(T);
    break;
  // 新節點插入在 T 的右孩子的左子樹上，要做雙旋轉處理
  case LH:
    // Rl 指向 T 的右孩子的左子樹的根節點
    Rl = R->lchild;

    // 修改 T 及其右孩子的平衡因子
    switch (Rl->bf) {
    case RH:
      (*T)->bf = LH;
      R->bf = EH;
      break;
    case EH:
      (*T)->bf = R->bf = EH;
      break;
    case LH:
      (*T)->bf = EH;
      R->bf = RH;
      break;
    }
    Rl->bf = EH;
    // 對 T 的右子樹作右旋轉平衡處理
    R_Rotate(&(*T)->rchild);
    // 對 T 做左旋轉平衡處理
    L_Rotate(T);
  }
}

/*
 * 若在平衡的二元排序樹 T 中不存在和 e 有相同關鍵字的結點，
 * 則插入一個資料元素為 e 的新結點，並返回1，否則返回0。
 * 若因插入而使二元排序樹失去平衡，則做平衡旋轉處理，
 * 布林變量 taller 反映 T 長高與否。
 */
Status InsertAVL(BiTree *T, int e, Status *taller) {
  // 插入新結點，樹"長高"，置 taller 為 TRUE
  if (!*T) {
    *T = (BiTree)malloc(sizeof(BiTNode));
    (*T)->data = e;
    (*T)->lchild = (*T)->rchild = NULL;
    (*T)->bf = EH;
    *taller = TRUE;
  } else {
    // 樹中已存在和 e 有相同關鍵字的結點則不再插入
    if (e == (*T)->data) {
      *taller = FALSE;

      return FALSE;
    }

    // 應繼續在 T 的左子樹中進行搜索
    if (e < (*T)->data) {
      // 未插入
      if (!InsertAVL(&(*T)->lchild, e, taller))
        return FALSE;

      // 已插入到 T 的左子樹中且左子樹"長高"
      if (*taller)
        // 檢查 T 的平衡度
        switch ((*T)->bf) {
          // 原本左子樹比右子樹高，需要做左平衡處理
        case LH:
          LeftBalance(T);
          *taller = FALSE;
          break;
          // 原本左右子樹等高，現因左子樹增高而樹增高
        case EH:
          (*T)->bf = LH;
          *taller = TRUE;
          break;
          // 原本右子樹比左子樹高，現左、右子樹等高
        case RH:
          (*T)->bf = EH;
          *taller = FALSE;
          break;
        }
    }
    // 應繼續在 T 的右子樹中進行搜索
    else {
      // 未插入
      if (!InsertAVL(&(*T)->rchild, e, taller))
        return FALSE;

      // 已插入到 T 的右子樹且右子樹"長高"
      if (*taller)
        // 檢查 T 的平衡度
        switch ((*T)->bf) {
          // 原本左子樹比右子樹高，現左、右子樹等高
        case LH:
          (*T)->bf = EH;
          *taller = FALSE;
          break;
          // 原本左右子樹等高，現因右子樹增高而樹增高
        case EH:
          (*T)->bf = RH;
          *taller = TRUE;
          break;
          // 原本右子樹比左子樹高，需要做右平衡處理
        case RH:
          RightBalance(T);
          *taller = FALSE;
          break;
        }
    }
  }

  return TRUE;
}

int main(void) {
  int i;
  int a[10] = {3, 2, 1, 4, 5, 6, 7, 10, 9, 8};
  BiTree T = NULL;
  Status taller;

  for (i = 0; i < 10; i++) {
    InsertAVL(&T, a[i], &taller);
  }
  printf("本樣例建議斷點跟踪查看平衡二元樹結構");

  return 0;
}
