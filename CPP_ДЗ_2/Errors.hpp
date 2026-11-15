#pragma once
// std::exception
// └── FleetError        — общий базис
//     ├── InspectionError — техосмотр отклонил транспорт
//     └── CommandError    — плохая команда или аргументы: неизвестная команда,
//                           простота вне 1..10, энергия < 0, id занят или не найден

#include <exception>
#include <string>

class FleetError : public std::exception {
public:
  FleetError(const std::string &message) : message_(message) {}
  const char *what() const noexcept override { return message_.c_str(); }

private:
  std::string message_;
};

class InspectionError : public FleetError {
public:
  InspectionError() : FleetError("inspection rejected") {}
};

class CommandError : public FleetError {
public:
  CommandError(const std::string &message) : FleetError(message) {}
};
