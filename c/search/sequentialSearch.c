// 循序搜尋，a 為陣列，n 為要搜尋的陣列長度，key 為要搜尋的關鍵字
int Sequential_Search(int *a, int n, int key) {
  int i;

  for (i = 1; i <= n; i++)
    if (a[i] == key)
      return i;

  return 0;
}

// 有衛兵循序搜尋
int Sequential_Search2(int *a, int n, int key) {
  int i;
  // 設定 a[0] 為關鍵字值，我們稱之為「衛兵」
  a[0] = key;
  // 迴圈從陣列尾部開始
  i = n;

  while (a[i] != key)
    i--;

  // 回傳 0 則說明搜尋失敗
  return i;
}
