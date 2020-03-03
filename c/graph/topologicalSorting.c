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

  while (top != 0) {
    // 出堆疊
    gettop = stack[top--];
    // 列印此頂點
    printf("%d -> ", GL->adjList[gettop].data);
    // 統計輸出頂點數
    count++;

    // 走訪此頂點的邊集合
    for (e = GL->adjList[gettop].firstedge; e; e = e->next) {
      k = e->adjvex;

      // 將 k 號頂點的鄰接點之內分支度減1
      if (!(--GL->adjList[k].in))
        // 若為0則入堆疊，以便在下次迴圈時輸出
        stack[++top] = k;
    }
  }
  free(stack);

  // 如果 count 小於頂點數，表示有環回路存在
  if (count < GL->numVertexes)
    return ERROR;
  else
    return OK;
}
