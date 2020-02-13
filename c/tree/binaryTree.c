// 二元樹的二元鏈結串列節點結構定義

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

// 樹節點的資料型別，目前暫定為整數型
typedef char TElemType;
/*
 * Link == 0 表示指向左右孩子指標
 * Thread == 1 表示指向前驅者或後繼者的引線
 */
typedef enum { Link, Thread } PointerTag;
// 二元引線儲存節點結構
typedef struct BiThrNode {
  // 節點資料
  TElemType data;
  // 左右孩子指標
  struct BiThrNode *lchild, *rchild;
  // 左標誌
  PointerTag LTag;
  // 右標誌
  PointerTag RTag;
} BiThrNode, *BiThrTree;
// 節點結構
typedef struct BiTNode {
  // 節點資料
  TElemType data;
  // 左右孩子的指標
  struct BiTNode *lchild, *rchild;
} BiTNode, *BiTree;

// 構造二元鏈結串列表示二元樹 T
void CreateBitTree(BiTree *T) {
  TElemType ch;
  scanf("%c", &ch);

  if (ch == '#')
    *T = NULL;
  else {
    *T = (BiTree)malloc(sizeof(BiTNode));

    if (!*T)
      exit(EXIT_FAILURE);
    // 生成根節點
    (*T)->data = ch;
    // 構造左子樹
    CreateBitTree(&(*T)->lchild);
    // 構造右子樹
    CreateBitTree(&(*T)->rchild);
  }
}

// 二元樹的中序走訪遞迴演算法
void InOrderTraverse(BiTree T) {
  if (T == NULL)
    return;
  // 中序走訪左子樹
  InOrderTraverse(T->lchild);
  // 顯示節點資料，可以更改為其他對節點的操作
  printf("%c", T->data);
  // 最後中序走訪右子樹
  InOrderTraverse(T->rchild);
}

// 全欄變數，始終指向剛剛拜訪過的節點
BiThrTree pre;
// 中序走訪進行中序引線化
void InThreading(BiThrTree p) {
  if (p) {
    // 遞迴左子樹引線化
    InThreading(p->lchild);

    // 沒有左孩子
    if (!p->lchild) {
      // 前驅引線
      p->LTag = Thread;
      // 左孩子指標指向前驅
      p->lchild = pre;
    }

    // 前驅沒有右孩子
    if (!pre->rchild) {
      // 後繼引線
      pre->RTag = Thread;
      // 前驅右孩子指標指向後繼者(目前的節點p)
      pre->rchild = p;
    }
    // 保持 pre 指向 p 的前驅者
    pre = p;
    // 遞迴右子樹引線化
    InThreading(p->rchild);
  }
}

// 二元樹的後序走訪遞迴演算法
void PostOrderTraverse(BiTree T) {
  if (T == NULL)
    return;
  // 先後序走訪左子樹
  PostOrderTraverse(T->lchild);
  // 再後序走訪右子樹
  PostOrderTraverse(T->rchild);
  // 顯示節點資料，可以更改為其他對節點的操作
  printf("%c", T->data);
}

// 二元樹的前序走訪遞迴演算法
void PreOrderTraverse(BiTree T) {
  if (T == NULL)
    return;
  // 顯示節點資料，可以更改為其他對節點的操作
  printf("%c", T->data);
  // 再前序走訪左子樹
  PreOrderTraverse(T->lchild);
  // 最後前序走訪右子樹
  PreOrderTraverse(T->rchild);
}
