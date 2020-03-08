// 二分搜尋法
int Binary_Search(int *a, int n, int key) {
  int low, high, mid;
  // 定義最低編號為記錄首位
  low = 1;
  // 定義最高編號為記錄末位
  high = n;

  while (low <= high) {
    // 內插
    mid = low + (high - low) * (key - a[low]) / (a[high] - a[low]);

    // 若搜尋值比中值小
    if (key < a[mid])
      // 最高編號調整到中位編號小一位
      high = mid - 1;

    // 若搜尋值比中值大
    else if (key > a[mid])
      // 最低編號調整到中位編號大一位
      low = mid + 1;

    else
      // 若相等則說明 mid 即為搜尋到的位置
      return mid;
  }
  return 0;
}
