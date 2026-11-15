#pragma once

#include <algorithm>
#include <cctype>
#include <memory>
#include <string>
#include <vector>

#include "Errors.hpp"
#include "Items.hpp"
#include "Registry.hpp"

class ServiceCenter {
 public:
  void addTransport(std::unique_ptr<Transport> transport) {
    inspect(*transport);
    add(std::move(transport));
  }

  void add(std::unique_ptr<InventoryItem> item) {
    if (find(item->inventoryId())) {
      throw CommandError("duplicate id");
    }
    items_.push_back(std::move(item));
  }

  void remove(const std::string& id) {
    for (size_t i = 0; i < items_.size(); i++) {
      if (items_[i]->inventoryId() == id) {
        items_.erase(items_.begin() + i);
        return;
      }
    }
    throw CommandError("no position");
  }

  std::vector<std::shared_ptr<InventoryItem>> sortedItems() const {
    auto sorted = items_;
    std::sort(sorted.begin(), sorted.end(),
              [](const auto& a, const auto& b) { return *a < *b; });
    return sorted;
  }

  void setFocus(const std::string& id) {
    auto item = find(id);
    if (!item) {
      throw CommandError("no position");
    }
    focus_ = item;
  }

  std::shared_ptr<InventoryItem> focus() const { return focus_.lock(); }
  double totalEnergy() const { return sumEnergy(items_); }
  int count() const { return items_.size(); }
  const Registry<std::string, 32>& rejected() const { return rejected_; }

 private:
  void inspect(const Transport& transport) {
    std::string name = transport.name();
    for (char& c : name) {
      c = std::tolower(static_cast<unsigned char>(c));
    }
    if (name.find("broken") != std::string::npos) {
      rejected_.add(transport.inventoryId());
      throw InspectionError();
    }
  }

  std::shared_ptr<InventoryItem> find(const std::string& id) const {
    for (const auto& item : items_) {
      if (item->inventoryId() == id) {
        return item;
      }
    }
    return nullptr;
  }

  std::vector<std::shared_ptr<InventoryItem>> items_;
  std::weak_ptr<InventoryItem> focus_;
  Registry<std::string, 32> rejected_;
};
