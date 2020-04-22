#include <stdio.h>
#include <stdlib.h>

// 定義雜湊長為陣列的長度
#define HASHSIZE 12
#define NULLKEY -32768
#define OK 1
#define SUCCESS 1
#define UNSUCCESS 0

// Status 是函數的型態，其值是函數結果狀態碼，如 OK 等
typedef int Status;

typedef struct {
  // 資料元素儲存基址，動態分配陣列
  int *elem;
  // 目前資料元素個數
  int count;
} HashTable;

// 雜湊表長度，全局變數
int m = 0;

// 初始化雜湊表
Status InitHashTable(HashTable *H) {
  int i;

  m = HASHSIZE;
  H->count = m;
  H->elem = (int *)malloc(m * sizeof(int));

  for (i = 0; i < m; i++)
    H->elem[i] = NULLKEY;

  return OK;
}

// 雜湊函數
int Hash(int key) {
  // 除法求餘數
  return key % m;
}

// 雜湊表查找關鍵字
Status SearchHash(HashTable H, int key, int *addr) {
  // 求雜湊位址
  *addr = Hash(key);

  // 如果不為空，則衝突
  while (H.elem[*addr] != key) {
    // 開放位址法的線性探測
    *addr = (*addr + 1) % m;

    // 如果迴圈回到原點
    if (H.elem[*addr] == NULLKEY || *addr == Hash(key))
      // 則說明關鍵字不存在
      return UNSUCCESS;
  }

  return SUCCESS;
}

// 插入鍵值進雜湊表
void InsertHash(HashTable *H, int key) {
  // 求雜湊位置
  int addr = Hash(key);

  // 如果不為空，則碰撞
  while (H->elem[addr] != NULLKEY) {
    // 開放位址法的線性探測
    addr = (addr + 1) % m;
  }
  // 直到有空位後插入鍵值
  H->elem[addr] = key;
}

int main() {
  int arr[HASHSIZE] = {12, 67, 56, 16, 25, 37, 22, 29, 15, 47, 48, 34};
  int i, p, key, result;
  HashTable H;
  key = 39;

  InitHashTable(&H);

  for (i = 0; i < m; i++)
    InsertHash(&H, arr[i]);

  result = SearchHash(H, key, &p);

  if (result)
    printf("查找 %d 的地址為：%d \n", key, p);
  else
    printf("查找 %d 失敗。\n", key);

  for (i = 0; i < m; i++) {
    key = arr[i];
    SearchHash(H, key, &p);
    printf("查找 %d 的地址為：%d \n", key, p);
  }

  return 0;
}
