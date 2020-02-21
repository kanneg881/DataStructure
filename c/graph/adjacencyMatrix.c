#include <stdio.h>

// 頂點型別應由用戶定義
typedef char VertexType;
// 邊上的權值型別應由用戶定義
typedef int EdgeType;

// 最大頂點數，應由用戶定義
#define MAXVEX 100
// 用 65535 來代表 ∞
#define INFINITY 65535

typedef struct {
  // 頂點集合
  VertexType vexs[MAXVEX];
  // 鄰接矩陣，可看作邊的集合
  EdgeType arc[MAXVEX][MAXVEX];
  // 圖形中目前的頂點數和邊數
  int numVertexes, numEdges;
} MGraph;

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
