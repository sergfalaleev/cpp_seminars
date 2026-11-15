#pragma once
// Все классы парка.
//
// InventoryItem (абстрактный)      EnergyConsumer (абстрактный)
// └── Item (id и имя)                   │
//     ├── Transport (простота)          │
//     │   ├── Bike                      │
//     │   ├── ElectricScooter ──────────┤ множественное наследование
//     │   ├── ElectricBike ─────────────┤
//     │   └── Monocycle ────────────────┤
//     ├── Helmet                        │
//     └── DockStation ──────────────────┘

#include <iostream>
#include <string>

#include "Errors.hpp"

class InventoryItem {
 public:
  virtual ~InventoryItem() = default;
  virtual std::string inventoryId() const = 0;
  virtual std::string name() const = 0;
  virtual std::string describe() const = 0;

  virtual double dailyEnergy() const { return 0.0; }
  virtual bool isNoviceFriendly() const { return false; }
};

inline std::ostream& operator<<(std::ostream& os, const InventoryItem& item) {
  os << item.inventoryId() << ' ' << item.name();
  return os;
}

inline bool operator<(const InventoryItem& left, const InventoryItem& right) {
  return left.inventoryId() < right.inventoryId();
}

class EnergyConsumer {
 public:
  virtual ~EnergyConsumer() = default;
  virtual double dailyEnergy() const = 0;
};

inline double checkEnergy(double energy) {
  if (energy < 0) {
    throw CommandError("negative energy");
  }
  return energy;
}

class Item : public InventoryItem {
 public:
  Item(std::string id, std::string name) : id_(id), name_(name) {
    if (id.empty()) {
      throw CommandError("empty id");
    }
  }
  std::string inventoryId() const override { return id_; }
  std::string name() const override { return name_; }

 private:
  std::string id_;
  std::string name_;
};

class Transport : public Item {
 public:
  Transport(std::string id, std::string name, int score)
      : Item(id, name), score_(score) {
    if (score < 1 or score > 10) {
      throw CommandError("bad score");
    }
  }
  bool isNoviceFriendly() const override { return (score_ >= 6); }

 private:
  int score_;
};

class Bike : public Transport {
 public:
  using Transport::Transport;
  std::string describe() const override { return "bike"; }
};

class ElectricScooter : public Transport, public EnergyConsumer {
 public:
  ElectricScooter(std::string id, std::string name, double energy, int score)
      : Transport(id, name, score), energy_(checkEnergy(energy)) {}
  std::string describe() const override { return "electric scooter"; }
  double dailyEnergy() const override { return energy_; }

 private:
  double energy_;
};

class ElectricBike : public Transport, public EnergyConsumer {
 public:
  ElectricBike(std::string id, std::string name, double energy, int score)
      : Transport(id, name, score), energy_(checkEnergy(energy)) {}
  std::string describe() const override { return "electric bike"; }
  double dailyEnergy() const override { return energy_; }

 private:
  double energy_;
};

class Helmet : public Item {
 public:
  using Item::Item;
  std::string describe() const override { return "helmet"; }
};

class DockStation : public Item, public EnergyConsumer {
 public:
  DockStation(std::string id, std::string name, double energy)
      : Item(id, name), energy_(checkEnergy(energy)) {}
  std::string describe() const override { return "dock station"; }
  double dailyEnergy() const override { return energy_; }

 private:
  double energy_;
};

class Monocycle : public Transport, public EnergyConsumer {
 public:
  Monocycle(std::string id, std::string name, double energy, int score)
      : Transport(id, name, score), energy_(checkEnergy(energy)) {}
  std::string describe() const override { return "monocycle"; }
  double dailyEnergy() const override { return energy_; }
  bool isNoviceFriendly() const override { return false; }

 private:
  double energy_;
};
