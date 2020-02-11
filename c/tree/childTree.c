// 樹的孩子標記法結構定義
#define MAX_TREE_SIZE 100

// 樹節點的資料型別，目前暫定為整數型
typedef int TElemType;
// 孩子節點
typedef struct CTNode {
  int child;
  struct CTNode *next;
} * ChildPtr;
// 樹的孩子兄弟標記法結構定義
typedef struct CSNode {
  TElemType data;
  struct CSNode *firstchild, *rightsib;
} CSNode, *CSTree;
// 表頭結構
typedef struct {
  TElemType data;
  ChildPtr firstchild;
} CTBox;
// 樹結構
typedef struct {
  // 節點陣列
  CTBox nodes[MAX_TREE_SIZE];
  // 根的位置和節點數
  int r, n;
} CTree;
