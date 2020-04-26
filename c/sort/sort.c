#include <stdio.h>
#include <stdlib.h>

#define FALSE 0
// 陣列長度臨界值
#define MAX_LENGTH_INSERT_SORT 7
// 用於待排序陣列個數的最大值，可根據需要修改
#define MAXSIZE 10
#define TRUE 1

typedef int Status;

typedef struct {
  // 用於儲存待排序陣列，r[0] 作為衛兵或臨時變數
  int r[MAXSIZE + 1];
  // 用於記錄序列的長度
  int length;
} SqList;

// 交換 L 中陣列 r 的編號為 i 和 j 的值
void swap(SqList *L, int i, int j) {
  int temp = L->r[i];

  L->r[i] = L->r[j];
  L->r[j] = temp;
}

// 對序列 L 做交換排序(氣泡排序初階版)
void BubbleSort0(SqList *L) {
  int i, j;

  for (i = 1; i < L->length; i++) {
    for (j = i + 1; j <= L->length; j++) {
      if (L->r[i] > L->r[j]) {
        // 交換 L->r[i] 與 L->r[j] 的值
        swap(L, i, j);
      }
    }
  }
}

// 對序列 L 做氣泡排序
void bubbleSort(SqList *L) {
  int i, j;

  for (i = 1; i < L->length; i++) {
    // 注意 j 是由後往前迴圈
    for (j = L->length - 1; j >= i; j--) {
      // 若前者大於後者(注意這裡與上一次演算法的差異)
      if (L->r[j] > L->r[j + 1]) {
        // 交換 L->r[j] 與 L->r[j + 1] 的值
        swap(L, j, j + 1);
      }
    }
  }
}

// 對序列 L 作改進氣泡演算法
void bubbleSort2(SqList *L) {
  int i, j;
  // flag 用來作為標記
  Status flag = TRUE;

  // 若 flag 為 true，則有過資料交換，否則退出迴圈
  for (i = 1; i < L->length && flag; i++) {
    // 初始為 false
    flag = FALSE;

    for (j = L->length - 1; j >= i; j++) {
      if (L->r[j] > L->r[j + 1]) {
        // 交換 L->r[j] 與 L->r[j + 1] 的值
        swap(L, j, j + 1);
        // 如果有交換資料，則 flag 為 true
        flag = TRUE;
      }
    }
  }
}

// 對序列 L 做簡單選擇排序
void selectSort(SqList *L) {
  int i, j, min;

  for (i = 1; i < L->length; i++) {
    // 將當前編號定義為最小值編號
    min = i;

    // 迴圈之後的資料
    for (j = i + 1; j <= L->length; j++) {
      // 如果有小於當前最小值的鍵值
      if (L->r[min] > L->r[j])
        // 將此鍵值得編號傳給 min
        min = j;
    }

    // 若 min 不等於 i，說明找到最小值，交換
    if (i != min)
      // 交換 L->r[i] 與 L->r[min] 的值
      swap(L, i, j);
  }
}

// 對序列 L 做直接插入排序
void insertSort(SqList *L) {
  int i, j;

  for (i = 2; i <= L->length; i++) {
    // 需將 L->r[i] 插入有序子序列
    if (L->r[i] < L->r[i - 1]) {
      // 設置衛兵
      L->r[0] = L->r[i];

      for (j = i - 1; L->r[j] > L->r[0]; j--)
        // 紀錄後移
        L->r[j + 1] = L->r[j];
      // 插入到正確位置
      L->r[j + 1] = L->r[0];
    }
  }
}

// 對序列 L 做 Shell 排序
void ShellSort(SqList *L) {
  int i, j;
  int increment = L->length;

  do {
    // 增量排序
    increment = increment / 3 + 1;

    for (i = increment + 1; i <= L->length; i++) {
      // 需將 L->r[i] 插入有序增量子序列
      if (L->r[i] < L->r[i - increment]) {
        // 暫存在 L->r[0]
        L->r[0] = L->r[i];

        for (j = i - increment; j > 0 && L->r[0] < L->r[j]; j -= increment)
          // 紀錄後移，搜尋插入位置
          L->r[j + increment] = L->r[j];
        // 插入
        L->r[j + increment] = L->r[0];
      }
    }
  } while (increment > 1);
}

/*
 * 已知 L->r[s..m] 中紀錄的鍵值除 L->r[s] 之外均滿足堆積的定義，
 * 本函式調整 L->r[s] 的鍵值，使 L->r[s..m] 成為一個最大堆積
 */
void heapAdjust(SqList *L, int s, int m) {
  int temp, j;
  temp = L->r[s];

  // 沿鍵值較大的孩子節點向下篩選
  for (j = 2 * s; j <= m; j *= 2) {
    if (j < m && L->r[j] < L->r[j + 1])
      // j 為鍵值中較大的紀錄的編號
      ++j;

    if (temp >= L->r[j])
      // rc 應插入在位置 s 上
      break;
    L->r[s] = L->r[j];
    s = j;
  }
  // 插入
  L->r[s] = temp;
}

// 對序列 L 進行堆積排序
void heapSort(SqList *L) {
  int i;

  // 把 L 中的 r 構建成一個最大堆積
  for (i = L->length / 2; i > 0; i--)
    heapAdjust(L, i, L->length);

  for (i = L->length; i > 1; i--) {
    // 將堆積中的首紀錄和目前未經排序子序列的最後一個紀錄交換
    swap(L, 1, i);
    // 將 L->r[1..i-1] 重新調整為最大序列
    heapAdjust(L, 1, i - 1);
  }
}

// 將有序的 SR[i..m] 和 SR[m+1..n] 合併為有序的 TR[i..n]
void merge(int SR[], int TR[], int i, int m, int n) {
  int j, k, l;

  // 將 SR 中記錄由小到大合併入 TR
  for (j = m + 1, k = i; i <= m && j <= n; k++) {
    if (SR[i] < SR[j])
      TR[k] = SR[i++];
    else
      TR[k] = SR[j++];
  }

  if (i <= m) {
    for (l = 0; l <= m - i; l++)
      // 將剩餘的 SR[i..m] 複製到 TR
      TR[k + l] = SR[i + l];
  }

  if (j <= n) {
    for (l = 0; l <= n - j; l++)
      // 將剩餘的 SR[j..n] 複製到 TR
      TR[k + l] = SR[j + l];
  }
}

// 將 SR[s..t] 合併排序為 TR1[s..t]
void MSort(int SR[], int TR1[], int s, int t) {
  int m;
  int TR2[MAXSIZE + 1];

  if (s == t)
    TR1[s] = SR[s];
  else {
    // 將 SR[s..t] 平分為 SR[s..m] 和 SR[m+1..t]
    m = (s + t) / 2;
    // 遞迴地將 SR[s..m] 合併為有序的 TR2[s..m]
    MSort(SR, TR2, s, m);
    // 遞迴地將 SR[m+1..t] 合併為有序的 TR2[m+1..t]
    MSort(SR, TR2, m + 1, t);
    // 將 TR2[s..m] 和 TR2[m+1..t] 合併到 TR1[s..t]
    merge(TR2, TR1, s, m, t);
  }
}

// 對序列 L 做合併排序
void mergeSort(SqList *L) { MSort(L->r, L->r, 1, L->length); }

// 將 SR[] 中相鄰長度為 s 的子序列兩兩合併到 TR[]
void MergePass(int SR[], int TR[], int s, int n) {
  int i = 1;
  int j;

  // 兩兩合併
  while (i <= n - 2 * s + 1) {
    merge(SR, TR, i, i + s - 1, i + 2 * s - 1);
    i = i + 2 * s;
  }

  // 合併最後兩個序列
  if (i < n - s + 1)
    merge(SR, TR, i, i + s - 1, n);

  // 若最後只剩下單個子序列
  else
    for (j = i; j <= n; j++)
      TR[j] = SR[j];
}

// 對序列 L 做合併非遞迴排序
void MergeSort2(SqList *L) {
  // 申請額外空間
  int *TR = (int *)malloc(L->length * sizeof(int));
  int k = 1;

  while (k < L->length) {
    MergePass(L->r, TR, k, L->length);
    // 子序列長度加倍
    k = 2 * k;
    MergePass(TR, L->r, k, L->length);
    // 子序列長度加倍
    k = 2 * k;
  }
  // 使用完畢要釋放記憶體，以免資料外洩
  free(TR);
}

/*
 * 交換序列 L 中子序列的紀錄，使基準記錄到位，並回傳其所在位置
 * 此時在它之前(後)的紀錄均不大(小)於它。
 */
int Partition(SqList *L, int low, int high) {
  int pivotkey;
  // 計算陣列中間的元素的編號
  int m = low + (high - low) / 2;

  if (L->r[low] > L->r[high])
    // 交換左端與右端資料，保證左端較小
    swap(L, low, high);

  if (L->r[m] > L->r[high])
    // 交換中間與右端資料，保證中間較小
    swap(L, high, m);

  if (L->r[m] > L->r[low])
    // 交換中間與左端資料，保證左端較小
    swap(L, m, low);
  // 用子序列的第一個紀錄做基準紀錄
  pivotkey = L->r[low];
  // 將基準鍵值備份到 L->r[0]
  L->r[0] = pivotkey;

  // 從序列的兩端交替地向中間掃描
  while (low < high) {
    while (low < high && L->r[high] >= pivotkey)
      high--;
    // 採用替換而不是交換的方式進行操作
    L->r[low] = L->r[high];

    while (low < high && L->r[low] <= pivotkey)
      low++;
    // 採用替換而不是交換的方式進行操作
    L->r[high] = L->r[low];
  }
  // 將基準數值替換回 L.r[low]
  L->r[low] = L->r[0];

  // 返回基準所在位置
  return low;
}

// 對序列 L 中的子序列 L->r[low..high] 做快速排序
void QSort(SqList *L, int low, int high) {
  int pivot;

  // 當 high - low 大於常數時，用快速排序
  if ((high - low) > MAX_LENGTH_INSERT_SORT) {
    while (low < high) {
      // 將 L->r[low..high] 一分為二，算出基準值 pivot
      pivot = Partition(L, low, high);
      // 對低於基準值的子序列遞迴排序
      QSort(L, low, pivot - 1);
      // 末端遞迴
      low = pivot + 1;
    }
  } else
    insertSort(L);
}

// 對序列 L 做快速排序
void quickSort(SqList *L) { QSort(L, 1, L->length); }
