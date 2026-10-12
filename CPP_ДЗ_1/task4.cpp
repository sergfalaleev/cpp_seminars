#include <iostream>
// это журнал школьный. первый индекс - индекс недели, второй - дня на этой
// неделе, третий - пара в этот день и там хранится количество человек на этой
// паре сначала ввод, потом запрос запрос имеет вид (1/2) w d, если в начале 1 -
// сумма по всем парам всех дней недели w, 2 - сумма по всем парам дня d недели
// w в конце освобождение памяти
int main() {
  // ввод
  int weeks;
  int days;
  int pairs;
  std::cin >> weeks >> days >> pairs;

  int*** log = new int**[weeks];
  for (int w = 0; w < weeks; w++) {
    log[w] = new int*[days];
    for (int d = 0; d < days; d++) {
      log[w][d] = new int[pairs];
      for (int p = 0; p < pairs; p++) {
        log[w][d][p] = 0;
        std::cin >> log[w][d][p];
      }
    }
  }
  // запрос
  int depth;
  int w;
  int d;
  int sum;
  std::cin >> depth >> w >> d;
  // ответ на запрос
  void* part = log[w - 1];
  if (depth == 2) {
    part = log[w - 1][d - 1];
  }

  if (depth == 1) {
    int** week = static_cast<int**>(part);
    for (int j = 0; j < days; j++) {
      for (int k = 0; k < pairs; k++) {
        sum += week[j][k];
      }
    }
  } else {
    int* day = static_cast<int*>(part);
    for (int k = 0; k < pairs; k++) {
      sum += day[k];
    }
  }
  std::cout << sum << "\n";

  // освобождение
  for (int w = 0; w < weeks; w++) {
    for (int d = 0; d < days; d++) {
      delete[] log[w][d];
    }
    delete[] log[w];
  }
  delete[] log;
  return 0;
}
