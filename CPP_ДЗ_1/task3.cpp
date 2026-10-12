#include <cstring>
#include <iostream>
const int rows = 5;
const int cols = 10;
void Clear(char board[rows][cols]) {
  for (int y = 0; y < rows; y++) {
    for (int x = 0; x < cols; x++) {
      board[y][x] = ' ';
    }
  }
}
bool isInside(int x, int y) {
  return x >= 0 and x < cols and y >= 0 and y < rows;
}
bool Put(char board[rows][cols], int x, int y, char c) {
  if (not isInside(x, y)) {
    return false;
  }
  board[y][x] = c;
  return true;
}
bool Text(char board[rows][cols], int x, int y, const char word[]) {
  int len = strlen(word);

  if (not isInside(x, y) or not isInside(x + len - 1, y)) {
    return false;
  }
  for (int i = 0; i < len; i++) {
    Put(board, x + i, y, word[i]);
  }
  return true;
}

void Print(const char board[rows][cols]) {
  for (int y = 0; y < rows; y++) {
    for (int x = 0; x < cols; x++) {
      std::cout << board[y][x];
    }
    std::cout << "\n";
  }
}

int main() {
  char board[rows][cols];
  Clear(board);

  char cmd[20];
  while (std::cin >> cmd) {
    if (strcmp(cmd, "quit") == 0) {
      break;
    }
    if (strcmp(cmd, "clear") == 0) {
      Clear(board);
    } else if (strcmp(cmd, "put") == 0) {
      int x = 0;
      int y = 0;
      char c = ' ';
      std::cin >> x >> y >> c;
      if (not Put(board, x, y, c)) {
        std::cout << "error\n";
      }
    } else if (strcmp(cmd, "text") == 0) {
      int x = 0;
      int y = 0;
      char word[100];
      std::cin >> x >> y >> word;
      if (not Text(board, x, y, word)) {
        std::cout << "error" << "\n";
      }
    } else if (strcmp(cmd, "print") == 0) {
      Print(board);
    } else {
      std::cout << "error" << "\n";
    }
  }
  return 0;
}
