/*
 * 雙向鏈結串列儲存結構
 */

// ElemType型別根據實際情況而定，這裡假設為 int
typedef int ElemType;

/*
 * 線性表的雙向鏈結串列儲存結構
 */
typedef struct DulNode {
  ElemType data;
  // 直接前驅指標
  struct DulNode *prior;
  // 直接後繼指標
  struct DulNode *next;
} DulNode, *DuLinkList;
