#include <stdio.h>
#include <stdlib.h>

// 狀態碼
#define ERROR 0
// 假值
#define FALSE 0
// 儲存空間初始分配量
#define MAXSIZE 20
// 最大頂點數，應由用戶定義
#define MAXVEX 100
// 狀態碼
#define OK 1
// 真值
#define TRUE 1

// 頂點類型應由用戶定義
typedef char VertexType;
// Boolean 是布林類型，其值是 TRUE 或 FALSE
typedef int Boolean;
// 邊上的權值型別應由用戶定義
typedef int EdgeType;
// QElemType 類型根據實際情形而定，這裡假設為 int
typedef int QElemType;
// 狀態類型
typedef int Status;

// 環狀佇列的順序儲存結構
typedef struct {
  QElemType data[MAXSIZE];
  // 首指標
  int front;
  // 尾指標，若佇列不為空，指向佇列尾元素的下一個位置
  int rear;
} SqQueue;
// 邊串列節點
typedef struct EdgeNode {
  // 鄰接點欄位，儲存該頂點對應的編號
  int adjvex;
  // 用於存儲權值，若為非網圖可以省略
  EdgeType weight;
  // 鏈結欄位，指向下一個鄰接點
  struct EdgeNode *next;
} EdgeNode;

// 頂點串列節點
typedef struct VertexNode {
  // 頂點欄位，存儲頂點資訊
  VertexType data;
  // 邊串列的首指標
  EdgeNode *firstedge;
} VertexNode, AdjList[MAXVEX];

typedef struct {
  AdjList adjList;
  // 圖形中目前的頂點數和邊數
  int numVertexes, numEdges;
} GraphAdjList;

// 建立圖型的鄰接串列結構
void CreateALGraph(GraphAdjList *G) {
  int i, j, k;
  EdgeNode *e;
  printf("輸入頂點數和邊數:\n");
  // 輸入頂點數和邊數
  scanf("%d,%d", &G->numVertexes, &G->numEdges);

  // 讀入頂點資訊，建立頂點串列
  for (i = 0; i < G->numVertexes; i++) {
    // 輸入頂點資訊
    scanf("%c", &G->adjList[i].data);
    // 將邊串列置為空串列
    G->adjList[i].firstedge = NULL;
  }

  // 建立邊串列
  for (k = 0; k < G->numEdges; k++) {
    printf("輸入邊(vi,vj)上的頂點序號:\n");
    // 輸入邊(vi,vj)上的頂點序號
    scanf("%d,%d", &i, &j);
    // 向記憶體申請空間，產生邊串列節點
    e = (EdgeNode *)malloc(sizeof(EdgeNode));
    // 鄰接序號為j
    e->adjvex = j;
    // 將 e 的指標指向目前頂點上指向的節點
    e->next = G->adjList[i].firstedge;
    // 將目前頂點的指標指向 e
    G->adjList[i].firstedge = e;

    // 向記憶體申請空間，產生邊串列節點
    e = (EdgeNode *)malloc(sizeof(EdgeNode));
    // 鄰接序號為 i
    e->adjvex = i;
    // 將 e 的指標指向目前頂點上指向的節點
    e->next = G->adjList[j].firstedge;
    // 將節點頂點的指標指向 e
    G->adjList[j].firstedge = e;
  }
}

Boolean visited[MAXVEX];

// 刪除 Q 中隊首元素，用 e 回傳其值
Status DeQueue(SqQueue *Q, QElemType *e) {
  // 佇列為空的判斷
  if (Q->front == Q->rear)
    return ERROR;

  // 將隊頭元素傳給 e
  *e = Q->data[Q->front];
  // front 指標向後移一位置，若到最後則轉到陣列之首
  Q->front = (Q->front + 1) % MAXSIZE;

  return OK;
}

// 插入元素 e 為 Q 新的隊尾元素
Status EnQueue(SqQueue *Q, QElemType e) {
  // 佇列是否滿的判斷
  if ((Q->rear + 1) % MAXSIZE == Q->front)
    return ERROR;

  // 將元素 e 傳給隊尾
  Q->data[Q->rear] = e;
  // rear 指標向後移一位置，若到最後則轉到陣列之首
  Q->rear = (Q->rear + 1) % MAXSIZE;

  return OK;
}

// 初始化一個空佇列 Q
Status InitQueue(SqQueue *Q) {
  Q->front = 0;
  Q->rear = 0;

  return OK;
}

// 鄰接串列的廣度優先走訪演算法
void BFSTraverse(GraphAdjList GL) {
  int i;
  EdgeNode *p;
  SqQueue Q;

  for (i = 0; i < GL.numVertexes; i++)
    visited[i] = FALSE;
  // 初始化一輔助用的佇列
  InitQueue(&Q);

  // 對每一個頂點做迴圈
  for (i = 0; i < GL.numVertexes; i++) {
    // 若是未拜訪過的就進行處理
    if (!visited[i]) {
      visited[i] = TRUE;
      // 列印頂點，也可做其他操作
      printf("%c ", GL.adjList[i].data);
      // 將此頂點入佇列
      EnQueue(&Q, i);

      // 若目前佇列不為空
      while (Q.front != Q.rear) {
        DeQueue(&Q, &i);
        // 找到目前頂點的邊鏈結串列首指標
        p = GL.adjList[i].firstedge;

        while (p) {
          // 若此頂點未拜訪過
          if (!visited[p->adjvex]) {
            visited[p->adjvex] = TRUE;
            printf("%c ", GL.adjList[i].data);
            // 將此頂點入佇列
            EnQueue(&Q, p->adjvex);
          }
          // 指標指向下一個鄰接點
          p = p->next;
        }
      }
    }
  }
}

// 鄰接串列的深度優先走訪演算法
void DFS(GraphAdjList GL, int i) {
  EdgeNode *p;
  visited[i] = TRUE;
  // 列印頂點，也可做其他操作
  printf("%c ", GL.adjList[i].data);
  p = GL.adjList[i].firstedge;

  while (p) {
    if (!visited[p->adjvex])
      // 對未訪問的鄰接頂點遞迴呼叫
      DFS(GL, p->adjvex);
    p = p->next;
  }
}

// 鄰接串列的深度走訪操作
void DFSTraverse(GraphAdjList GL) {
  int i;

  for (i = 0; i < GL.numVertexes; i++)
    // 初始化所有頂點狀態都是未訪問過狀態
    visited[i] = FALSE;

  for (i = 0; i < GL.numVertexes; i++)
    // 對未訪問過的頂點調用 DFS，若是連通圖，只會執行一次
    if (!visited[i])
      DFS(GL, i);
}
