#pragma once
#include <ostream>

template <typename T, int Cap>
class Registry {
 public:
  void add(const T& value) {
    if (size_ < Cap) {
      data_[size_] = value;
      size_++;
    }
  }

  int size() const { return size_; }

  const T& operator[](int i) const { return data_[i]; }

  friend std::ostream& operator<<(std::ostream& os, const Registry& registry) {
    for (long long i = 0; i < registry.size(); i++) {
      os << registry[i] << "\n";
    }
    return os;
  }

 private:
  T data_[Cap];
  int size_ = 0;
};

template <typename Container>
double sumEnergy(const Container& items) {
  double total = 0.0;

  for (const auto& item : items) {
    total += item->dailyEnergy();
  }

  return total;
}
