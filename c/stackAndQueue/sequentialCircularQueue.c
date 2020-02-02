/*
 * 環狀佇列的順序儲存結構
 */

// 狀態碼
#define ERROR 0
// 儲存空間初始分配量
#define MAXSIZE 20
// 狀態碼
#define OK 1

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

// 回傳 Q 的元素個數，也就是佇列的目前長度
int QueueLength(SqQueue Q) { return (Q.rear - Q.front + MAXSIZE) % MAXSIZE; }

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
