// 樹的雙親標記法節點結構定義
#define MAX_TREE_SIZE 100

// 樹節點的資料型別，目前暫定為整數型
typedef int TElemType;
// 節點結構
typedef struct PTNode {
  // 節點資料
  TElemType data;
  // 雙親位置
  int parent;
} PTNode;
// 樹結構
typedef struct {
  // 節點陣列
  PTNode nodes[MAX_TREE_SIZE];
  // 根的位置和節點數
  int r, n;
} PTree;
