#include <iomanip>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>

#include "Items.hpp"
#include "ServiceCenter.hpp"

static void checkArgs(std::istringstream& in) {
  std::string extra;
  if (!in || in >> extra) {
    throw CommandError("bad arguments");
  }
}

static void addCommand(ServiceCenter& center, std::istringstream& in) {
  std::string kind, id, name;
  double energy;
  int score;
  in >> kind >> id >> name;

  if (kind == "scooter") {
    in >> energy >> score;
    checkArgs(in);
    center.addTransport(
        std::make_unique<ElectricScooter>(id, name, energy, score));
  } else if (kind == "bike") {
    in >> score;
    checkArgs(in);
    center.addTransport(std::make_unique<Bike>(id, name, score));
  } else if (kind == "ebike") {
    in >> energy >> score;
    checkArgs(in);
    center.addTransport(
        std::make_unique<ElectricBike>(id, name, energy, score));
  } else if (kind == "helmet") {
    checkArgs(in);
    center.add(std::make_unique<Helmet>(id, name));
  } else if (kind == "dock") {
    in >> energy;
    checkArgs(in);
    center.add(std::make_unique<DockStation>(id, name, energy));
  } else if (kind == "monocycle") {
    in >> energy >> score;
    checkArgs(in);
    center.addTransport(std::make_unique<Monocycle>(id, name, energy, score));
  } else {
    throw CommandError("unknown kind " + kind);
  }
}

// Возвращает false на команде quit.
static bool runCommand(ServiceCenter& center, const std::string& line) {
  std::istringstream in(line);
  std::string command;
  in >> command;

  if (command.empty()) {
    return true;
  } else if (command == "quit") {
    return false;
  } else if (command == "add") {
    addCommand(center, in);
  } else if (command == "list") {
    for (const auto& item : center.sortedItems()) {
      std::cout << *item << '\n';
    }
  } else if (command == "novice") {
    for (const auto& item : center.sortedItems()) {
      if (item->isNoviceFriendly()) std::cout << *item << '\n';
    }
  } else if (command == "energy") {
    std::cout << std::fixed << std::setprecision(1) << center.totalEnergy()
              << '\n';
  } else if (command == "report") {
    std::cout << std::fixed << std::setprecision(1) << center.count() << ' '
              << center.totalEnergy() << '\n';
  } else if (command == "rejected") {
    std::cout << center.rejected();
  } else if (command == "focus") {
    std::string id;
    in >> id;
    checkArgs(in);
    center.setFocus(id);
  } else if (command == "remove") {
    std::string id;
    in >> id;
    checkArgs(in);
    center.remove(id);
  } else if (command == "show_focus") {
    auto item = center.focus();
    if (item) {
      std::cout << *item << " (" << item->describe() << ")\n";
    } else {
      std::cout << "expired\n";
    }
  } else {
    throw CommandError("unknown command " + command);
  }
  return true;
}

int main() {
  ServiceCenter center;
  std::string line;
  while (std::getline(std::cin, line)) {
    try {
      if (!runCommand(center, line)) {
        break;
      }
    } catch (const FleetError& error) {
      std::cout << "error: " << error.what() << '\n';
    }
  }
}
