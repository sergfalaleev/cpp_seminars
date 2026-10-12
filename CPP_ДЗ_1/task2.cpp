#include <iostream>
bool Deposit(int &sum) {
  int k = 0;
  std::cin >> k;
  if (k <= 0) {
    return false;
  }
  sum += k;
  return true;
}

bool Withdraw(int &sum) {
  int k = 0;
  std::cin >> k;
  if (k > sum or k <= 0) {
    return false;
  }
  sum -= k;
  return true;
}

bool Balance(int &sum) {
  std::cout << sum << "\n";
  return true;
}

bool Reset(int &sum) {
  sum = 0;
  return true;
}

bool Increase(int &sum) {
  sum++;
  return true;
}

int main() {
  const char commands[] = {'d', 'w', 'b', 'r', 'i'};
  bool (*const functions[])(int &sum) = {Deposit, Withdraw, Balance, Reset,
                                         Increase};
  int sum = 0;
  const int cntFunc = sizeof(commands);
  char cmd[20];
  while (std::cin >> cmd) {
    if (cmd[0] == 's') {
      break;
    }
    bool ok = false;
    for (int i = 0; i < cntFunc; i++) {
      if (cmd[0] == commands[i]) {
        ok = functions[i](sum);
        break;
      }
    }
    if (not ok) {
      std::cout << "error" << "\n";
    }
  }
  return 0;
}
