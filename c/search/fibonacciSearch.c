int F[9] = {0, 1, 1, 2, 3, 5, 8, 13, 21};

// 費氏搜尋法
int Fibonacci_Search(int *a, int n, int key) {
  int low, high, mid, i, k;
  // 定義最低編號為記錄首位
  low = 1;
  // 定義最高編號為記錄末位
  high = n;
  k = 0;

  // 計算 n 位於費伯納西數列的位置
  while (n > F[k] - 1)
    k++;

  // 將不全的數值補全
  for (i = n; i < F[k] - 1; i++)
    a[i] = a[n];

  while (low <= high) {
    // 計算目前分割的編號
    mid = low + F[k - 1] - 1;

    // 若搜尋紀錄小於目前分割紀錄
    if (key < a[mid]) {
      // 最高編號調整到分割編號 mid - 1 處
      high = mid - 1;
      // 費伯納西數列編號減一位
      k = k - 1;
    }

    // 若搜尋紀錄大於目前分割紀錄
    else if (key > a[mid]) {
      // 最低編號調整到分割編號 mid + 1 處
      low = mid + 1;
      // 費伯納西數列編號減兩位
      k = k - 2;
    }

    else {
      if (mid <= n)
        // 若相等則說明 mid 即為搜尋到的位置
        return mid;

      else
        // 若 mid > n 說明是補全數值，回傳 n
        return n;
    }
  }
  return 0;
}
