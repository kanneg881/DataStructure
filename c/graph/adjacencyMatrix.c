#include <stdio.h>

// 狀態碼
#define ERROR 0
// 假值
#define FALSE 0
// 用 65535 來代表 ∞
#define INFINITY 65535
// 最大邊數
#define MAXEDGE 100
// 儲存空間初始分配量
#define MAXSIZE 20
// 最大頂點數，應由用戶定義
#define MAXVEX 100
// 狀態碼
#define OK 1
// 真值
#define TRUE 1

// 頂點型別應由用戶定義
typedef char VertexType;
// Boolean 是布林類型，其值是 TRUE 或 FALSE
typedef int Boolean;
// 邊上的權值型別應由用戶定義
typedef int EdgeType;
typedef int FloydPathmatrix[MAXVEX][MAXVEX];
typedef int FloydShortPathTable[MAXVEX][MAXVEX];
// 用於儲存最短路徑編號的陣列
typedef int Pathmatrix[MAXVEX];
// 用於儲存到各點最短路徑的權值和
typedef int ShortPathTable[MAXVEX];
// QElemType 類型根據實際情形而定，這裡假設為 int
typedef int QElemType;
// 狀態類型
typedef int Status;

// 對邊集合陣列 Edge 結構的定義
typedef struct {
  int begin;
  int end;
  int weight;
} Edge;
typedef struct {
  // 頂點集合
  VertexType vexs[MAXVEX];
  // 鄰接矩陣，可看作邊的集合
  EdgeType arc[MAXVEX][MAXVEX];
  // 圖形中目前的頂點數和邊數
  int numVertexes, numEdges;
} MGraph;
// 環狀佇列的順序儲存結構
typedef struct {
  QElemType data[MAXSIZE];
  // 首指標
  int front;
  // 尾指標，若佇列不為空，指向佇列尾元素的下一個位置
  int rear;
} SqQueue;

Boolean visited[MAXVEX];

// 搜尋連線頂點的尾部編號
int Find(int *parent, int f) {
  while (parent[f] > 0)
    f = parent[f];

  return f;
}

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

// 鄰接矩陣的廣度優先走訪演算法
void BFSTraverse(MGraph G) {
  int i, j;
  SqQueue Q;

  for (i = 0; i < G.numVertexes; i++)
    visited[i] = FALSE;
  // 初始化一輔助用的佇列
  InitQueue(&Q);

  // 對每一個頂點做迴圈
  for (i = 0; i < G.numVertexes; i++) {
    // 若是未拜訪過的就進行處理
    if (!visited[i]) {
      // 設定目前頂點為拜訪過
      visited[i] = TRUE;
      // 列印頂點，也可做其他操作
      printf("%c ", G.vexs[i]);
      // 將此頂點入佇列
      EnQueue(&Q, i);

      // 若目前佇列不為空
      while (Q.front != Q.rear) {
        // 將元素出佇列，傳值給 i
        DeQueue(&Q, &i);

        for (j = 0; j < G.numVertexes; j++) {
          // 判斷其他頂點若與目前頂點有邊存在且未拜訪過
          if (G.arc[i][j] == 1 && !visited[j]) {
            // 將找到的此頂點標記為已拜訪
            visited[j] = TRUE;
            // 列印頂點
            printf("%c ", G.vexs[i]);
            // 將找到的頂點入佇列
            EnQueue(&Q, j);
          }
        }
      }
    }
  }
}

// 建立無向網圖的鄰接矩陣表示
void CreateMGraph(MGraph *G) {
  int i, j, k, w;
  printf("輸入頂點數和邊數:\n");
  // 輸入頂點數和邊數
  scanf("%d,%d", &G->numVertexes, &G->numEdges);

  for (i = 0; i < G->numVertexes; ++i)
    scanf("%c", &G->vexs[i]);

  for (i = 0; i < G->numVertexes; i++)
    for (j = 0; j < G->numVertexes; j++)
      // 鄰接矩陣初始化
      G->arc[i][j] = INFINITY;

  // 讀入 numEdges 條邊，建立鄰接矩陣
  for (k = 0; k < G->numEdges; k++) {
    printf("輸入(vi,vj)上的編號i、編號j和權w:\n");
    // 輸入邊(vi,vj)上的權w
    scanf("%d,%d,%d", &i, &j, &w);
    G->arc[i][j] = w;
    // 因為是無向圖形，矩陣對稱
    G->arc[j][i] = G->arc[i][j];
  }
}

// 鄰接矩陣的深度優先走訪演算法
void DFS(MGraph G, int i) {
  int j;
  visited[i] = TRUE;
  // 列印頂點，也可做其他操作
  printf("%c ", G.vexs[i]);

  for (j = 0; j < G.numVertexes; j++)
    if (G.arc[i][j] == 1 && !visited[j])
      // 對未訪問的鄰接頂點遞迴呼叫
      DFS(G, j);
}

// 鄰接矩陣的深度走訪操作
void DFSTraverse(MGraph G) {
  int i;

  for (i = 0; i < G.numVertexes; i++)
    // 初始化所有頂點狀態都是未訪問過狀態
    visited[i] = FALSE;

  for (i = 0; i < G.numVertexes; i++)
    // 對未訪問過的頂點調用 DFS，若是連通圖，只會執行一次
    if (!visited[i])
      DFS(G, i);
}

// Prim 演算法生成最小展開樹
void MiniSpanTree_Prim(MGraph G) {
  int min, i, j, k;
  // 保存相關頂點編號
  int adjvex[MAXVEX];
  // 保存相關頂點間，邊的權值
  int lowcost[MAXVEX];
  /*
   * 初始化第一個權值為0，即 v0 加入展開數
   * lowcost 的值為0，在這裡就是此編號的頂點已經加入展開樹
   */
  lowcost[0] = 0;
  // 初始化第一個頂點編號為 0
  adjvex[0] = 0;

  // 迴圈除了編號為0以外的全部頂點
  for (i = 1; i < G.numVertexes; i++) {
    // 將 v0 頂點與之有邊的權值存入陣列
    lowcost[i] = G.arc[0][i];
    // 初始化都為 v0 的編號
    adjvex[i] = 0;
  }

  for (i = 1; i < G.numVertexes; i++) {
    /*
     * 初始化最小權值為∞
     * 通常設置一個不可能的極大數字如 32767、65535等
     */
    min = INFINITY;
    j = 1;
    k = 0;

    // 迴圈全部頂點
    while (j < G.numVertexes) {
      // 如果權值不為0且權值小於 min
      if (lowcost[j] != 0 && lowcost[j] < min) {
        // 則讓目前權值成為最小值
        min = lowcost[j];
        // 將目前最小值的編號存入 k
        k = j;
      }
      j++;
    }
    // 列印目前頂點邊中，權值最小的邊
    printf("(%d, %d)", adjvex[k], k);
    // 將目前頂點的權值設置為0，表示此頂點已經完成任務
    lowcost[k] = 0;

    // 迴圈所有頂點
    for (j = 1; j < G.numVertexes; j++) {
      // 若編號為 k 頂點各邊權值小於此前這些頂點未被加入展開樹權值
      if (lowcost[j] != 0 && G.arc[k][j] < lowcost[j]) {
        // 將較小權值存入 lowcost 相應位置
        lowcost[j] = G.arc[k][j];
        // 將編號為 k 的頂點存入 adjvex
        adjvex[j] = k;
      }
    }
  }
}

// Kruskal 演算法生成最小展開樹
void MiniSpanTree_Kruskal(MGraph G) {
  int i, n, m;
  // 定義邊集陣列，Edge 結構 begin, end, weight 均為整數型
  Edge edges[MAXEDGE];
  // 定義一個陣列來判斷邊與邊是否形成環路
  int parent[MAXVEX];

  // 此處省略將鄰接矩陣 G 轉化為邊集陣列 edges，並按權由小到大排序的程式碼

  for (i = 0; i < G.numVertexes; i++)
    // 初始化陣列值為 0
    parent[i] = 0;

  // 迴圈每一條邊
  for (i = 0; i < G.numEdges; i++) {
    n = Find(parent, edges[i].begin);
    m = Find(parent, edges[i].end);

    // 假如 n 與 m 不相等，則表示此邊沒有與現有的展開樹形成環路
    if (n != m) {
      /*
       * 將此邊的結束頂點放入編號為起點的 parent 中。
       * 表示此頂點已經在展開樹集合中
       */
      parent[n] = m;
      printf("(%d, %d) %d ", edges[i].begin, edges[i].end, edges[i].weight);
    }
  }
}

/*
 * Dijkstra 演算法，求有向網圖 G 的 v0 頂點到其餘頂點 v 最短路徑 P[v]
 * 及加權長度 D[v]
 * P[v] 的值為前驅頂點編號，D[v] 表示 v0 到 v 的最短路徑長度和。
 */
void ShortestPath_Dijkstra(MGraph G, int v0, Pathmatrix *P, ShortPathTable *D) {
  int v, w, k, min;
  // final[w] = 1 表示求得頂點 v0 至 vw 的最短路徑
  int final[MAXVEX];

  // 初始化數據
  for (v = 0; v < G.numVertexes; v++) {
    // 全部頂點初始化為未知最短路徑狀態
    final[v] = 0;
    // 將與 v0 點有連接的頂點加上權值
    (*D)[v] = G.arc[v0][v];
    // 初始化路徑陣列 P 為 0
    (*P)[v] = 0;
  }
  // v0 至 v0 路徑為 0
  (*D)[v0] = 0;
  // v0 至 v0 不需要求路徑
  final[v0] = 1;

  // 開始主迴圈，每次求得 v0 到某個 v 頂點的最短路徑
  for (v = 1; v < G.numVertexes; v++) {
    // 目前所知的距離 v0 頂點的最近距離
    min = INFINITY;

    // 尋找離 v0 最近的頂點
    for (w = 0; w < G.numVertexes; w++) {
      if (!final[w] && (*D)[w] < min) {
        k = w;
        // w 頂點距離 v0 頂點更近
        min = (*D)[w];
      }
    }
    // 將目前找到的最近的頂點設為 1
    final[k] = 1;

    // 修正當前最短路徑及距離
    for (w = 0; w < G.numVertexes; w++) {
      /*
       * 如果經過 v 頂點的路徑比現在這條路徑的長度短的話
       * 表示找到了更短的路徑，修改 D[w] 和 P[w]
       */
      if (!final[w] && (min + G.arc[k][w] < (*D)[w])) {
        // 修改目前路徑長度
        (*D)[w] = min + G.arc[k][w];
        (*P)[w] = k;
      }
    }
  }
}

/*
 * Floyd 演算法，求網圖 G 中各頂點 v 到其餘頂點 w 最短路徑 p[v][w]
 * 及加權長度 D[v][w]
 */
void ShortestPath_Floyd(MGraph G, FloydPathmatrix *P, FloydShortPathTable *D) {
  int v, w, k;

  // 初始化 D 與 P
  for (v = 0; v < G.numVertexes; ++v)
    for (w = 0; w < G.numVertexes; ++w) {
      // D[v][w] 值即為對應點之間的權值
      (*D)[v][w] = G.arc[v][w];
      // 初始化 P
      (*P)[v][w] = w;
    }

  for (k = 0; k < G.numVertexes; ++k)
    for (v = 0; v < G.numVertexes; ++v)
      for (w = 0; w < G.numVertexes; ++w) {
        // 如果經過編號為 k 的頂點路徑比原兩點之間路徑更短
        if ((*D)[v][w] > (*D)[v][k] + (*D)[k][w]) {
          // 將目前兩點之間的權值設定為更小的一點
          (*D)[v][w] = (*D)[v][k] + (*D)[k][w];
          // 路徑設定為經過編號為 k 的頂點
          (*P)[v][w] = (*P)[v][k];
        }
      }

  for (v = 0; v < G.numVertexes; ++v) {
    for (w = v + 1; w < G.numVertexes; w++) {
      printf("v%d-v%d weight: %d ", v, w, (*D)[v][w]);
      // 獲得第一個路徑頂點編號
      k = (*P)[v][w];
      // 列印起點
      printf(" path: %d", v);

      // 如果路徑頂點編號不是終點
      while (k != w) {
        // 列印路徑頂點
        printf(" -> %d", k);
        // 獲得下一個路徑頂點編號
        k = (*P)[k][w];
      }
      // 列印終點
      printf(" -> %d\n", w);
    }
    printf("\n");
  }
}
