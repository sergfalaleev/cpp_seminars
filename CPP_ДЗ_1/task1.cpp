#include <iomanip>
#include <iostream>

int max(const int &a, const int &b) {
  if (a < b) {
    return b;
  }
  return a;
}

int min(const int &a, const int &b) {
  if (a > b) {
    return b;
  }
  return a;
}

double averageArray(const int *arr, int &n) {
  double average = 0;
  for (int i = 0; i < n; i++) {
    average += arr[i];
  }
  average = average / n;
  return average;
}

int minArray(const int *arr, int &n) {
  int minimum = arr[0];

  for (int i = 0; i < n; i++) {
    minimum = min(minimum, arr[i]);
  }
  return minimum;
}

int maxArray(const int *arr, int &n) {
  int maximum = arr[0];
  for (int i = 0; i < n; i++) {
    maximum = max(maximum, arr[i]);
  }
  return maximum;
}

int belowZeroArray(const int *arr, int &n) {
  int cnt_below_zero = 0;
  for (int i = 0; i < n; i++) {
    if (arr[i] < 0) {
      cnt_below_zero++;
    }
  }
  return cnt_below_zero;
}

int main() {
  int n;
  std::cin >> n;
  int *arr = new int[n];
  for (int i = 0; i < n; i++) {
    std::cin >> arr[i];
  }
  std::cout << std::fixed << std::setprecision(1) << averageArray(arr, n)
            << "\n";
  std::cout << minArray(arr, n) << ' ' << maxArray(arr, n) << "\n";
  std::cout << belowZeroArray(arr, n) << "\n";

  delete[] arr;
  return 0;
}