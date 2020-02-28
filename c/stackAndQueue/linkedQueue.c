#include <stdlib.h>

// 狀態碼
#define ERROR 0
// 狀態碼
#define OK 1
#define OVERFLOW 1

// QElemType 類型根據實際情形而定，這裡假設為 int
typedef int QElemType;
// 狀態類型
typedef int Status;

// 節點結構
typedef struct QNode {
  QElemType data;
  struct QNode *next;
} QNode, *QueuePtr;

// 佇列的鏈結串列結構
typedef struct {
  // 隊首、隊尾指標
  QueuePtr front, rear;
} LinkQueue;

// 若佇列不空，刪除 Q 的隊首元素，用 e 回傳其值
Status DeQueue(LinkQueue *Q, QElemType *e) {
  QueuePtr p;

  if (Q->front == Q->rear)
    return ERROR;
  // 將欲刪除的隊首節點暫存給 p
  p = Q->front->next;
  // 將欲刪除的隊首節點的值傳給 e
  *e = p->data;
  // 將原隊首節點的後繼者 p->next 傳給首節點的後繼者
  Q->front->next = p->next;

  // 若隊首就是隊尾，則刪除後將 rear 指向首節點
  if(Q->rear == p)
    Q->rear = Q->front;

  return OK;
}

// 插入元素 e 為 Q 的新的隊尾元素
Status EnQueue(LinkQueue *Q, QElemType e) {
  QueuePtr s = (QueuePtr)malloc(sizeof(QNode));

  if (!s)
    exit(OVERFLOW);
  s->data = e;
  s->next = NULL;
  // 把擁有元素 e 新節點 s 傳給原隊尾節點的後繼者
  Q->rear->next = s;
  // 把目前的 s 設置為隊尾節點，rear 指向 s
  Q->rear = s;

  return OK;
}
