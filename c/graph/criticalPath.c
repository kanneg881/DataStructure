#include <stdio.h>
#include <stdlib.h>

#define ERROR 0
#define MAXVEX 100
#define OK 1

// 狀態類型
typedef int Status;

// 邊集合節點
typedef struct EdgeNode {
  // 鄰接點欄位，儲存該頂點對應的編號
  int adjvex;
  // 用於儲存權值，對於非網圖可以不需要
  int weight;
  // 指標欄位，指向下一個鄰接點
  struct EdgeNode *next;
} EdgeNode;

// 頂點集合節點
typedef struct VertexNode {
  // 頂點的內分支度
  int in;
  // 頂點欄位，儲存頂點資訊
  int data;
  // 邊集合首指標
  EdgeNode *firstedge;
} VertexNode, AdjList[MAXVEX];

typedef struct {
  AdjList adjList;
  // 圖形中目前的頂點數和邊數
  int numVertexes, numEdges;
} graphAdjList, *GraphAdjList;

// 事件最早發生時間和最晚發生時間陣列
int *etv, *ltv;
// 用於儲存拓墣序列的堆疊
int *stack2;
// 用於 stack2 的指標
int top2;

/*
 * 拓墣排序，若 GL 無環路，則輸出拓墣排序序列並回傳 OK
 * 若有環路，則回傳 ERROR
 */
Status TopologicalSort(GraphAdjList GL) {
  EdgeNode *e;
  int i, k, gettop;
  // 用於堆疊指標編號
  int top = 0;
  // 用於統計輸出頂點的個數
  int count = 0;
  // 建立堆疊儲存內分支度為0的頂點
  int *stack;
  stack = (int *)malloc(GL->numVertexes * sizeof(int));

  for (i = 0; i < GL->numVertexes; i++)
    if (GL->adjList[i].in == 0)
      // 將內分支度為0的頂點入堆疊
      stack[++top] = i;

  // 初始化為 0
  top2 = 0;
  // 事件最早發生時間陣列
  etv = (int *)malloc(GL->numVertexes * sizeof(int));

  for (i = 0; i < GL->numVertexes; i++)
    // 初始化為 0
    etv[i] = 0;
  // 初始化拓墣序列棧
  stack2 = (int *)malloc(GL->numVertexes * sizeof(int));

  while (top != 0) {
    // 出堆疊
    gettop = stack[top--];
    // 統計輸出頂點數
    count++;
    // 將彈出的頂點序號壓入拓墣序列的堆疊
    stack2[++top2] = gettop;

    // 走訪此頂點的邊集合
    for (e = GL->adjList[gettop].firstedge; e; e = e->next) {
      k = e->adjvex;

      // 將 k 號頂點的鄰接點之內分支度減1
      if (!(--GL->adjList[k].in))
        // 若為0則入堆疊，以便在下次迴圈時輸出
        stack[++top] = k;

      // 求個頂點事件最早發生時間值
      if ((etv[gettop] + e->weight > etv[k]))
        etv[k] = etv[gettop] + e->weight;
    }
  }
  free(stack);

  // 如果 count 小於頂點數，表示有環回路存在
  if (count < GL->numVertexes)
    return ERROR;
  else
    return OK;
}

// 求關鍵路徑，GL 為有向網，輸出 GL 的各項關鍵活動
void CriticalPath(GraphAdjList GL) {
  EdgeNode *e;
  int i, gettop, k, j;
  // 宣告活動最早發生時間和最晚發生間變數
  int ete, lte;

  // 求拓墣序列，計算陣列 etv 和 stack2 的值
  TopologicalSort(GL);

  for (i = 0; i < GL->numVertexes; i++)
    // 初始化 ltv
    ltv[i] = etv[GL->numVertexes - 1];

  // 計算 ltv
  while (top2 != 0) {
    // 將拓墣序列出堆疊，後進先出
    gettop = stack2[top2--];

    // 求個頂點事件的最晚發生時間 ltv 值
    for (e = GL->adjList[gettop].firstedge; e; e = e->next) {
      k = e->adjvex;

      if (ltv[k] - e->weight < ltv[gettop])
        // 求各頂點事件最晚發生時間 ltv 值
        ltv[gettop] = ltv[k] - e->weight;
    }
  }

  // 求 ete, lte 和關鍵活動
  for (j = 0; j < GL->numVertexes; j++)
    for (e = GL->adjList[j].firstedge; e; e = e->next) {
      k = e->adjvex;
      // 活動最早發生時間
      ete = etv[j];
      // 活動最晚發生時間
      lte = ltv[k] - e->weight;

      if (ete == lte)
        printf("<v%d,v%d> length: %d , ", GL->adjList[j].data,
               GL->adjList[k].data, e->weight);
    }
}
