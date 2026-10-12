#include <iomanip>
#include <iostream>

int Max(const int &a, const int &b) {
  if (a < b) {
    return b;
  }
  return a;
}

int Min(const int &a, const int &b) {
  if (a > b) {
    return b;
  }
  return a;
}

double AverageArray(const int *arr, int &n) {
  double average = 0;
  for (int i = 0; i < n; i++) {
    average += arr[i];
  }
  average = average / n;
  return average;
}

int MinArray(const int *arr, int &n) {
  int minimum = arr[0];

  for (int i = 0; i < n; i++) {
    minimum = Min(minimum, arr[i]);
  }
  return minimum;
}

int MaxArray(const int *arr, int &n) {
  int maximum = arr[0];
  for (int i = 0; i < n; i++) {
    maximum = Max(maximum, arr[i]);
  }
  return maximum;
}

int BelowZeroArray(const int *arr, int &n) {
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
  std::cout << std::fixed << std::setprecision(1) << AverageArray(arr, n)
            << "\n";
  std::cout << MinArray(arr, n) << ' ' << MaxArray(arr, n) << "\n";
  std::cout << BelowZeroArray(arr, n) << "\n";

  delete[] arr;
  return 0;
}