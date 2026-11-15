# Структура проекта Fleet

Программа читает команды из `stdin` и ведёт учёт парка кикшеринга.

## Исходники

- `Errors.hpp` — исключения: базовый `FleetError`, от него `InspectionError` (отказ техосмотра) и `CommandError` (плохая команда, аргументы или id).
- `Items.hpp` — классы техники. Интерфейсы `InventoryItem` и `EnergyConsumer`; `Item` (id, имя) → `Transport` (простота 1..10) → `Bike`, `ElectricScooter`, `ElectricBike`, `Monocycle`; а также `Helmet` и `DockStation`. Электрическая техника наследует ещё и `EnergyConsumer`. Здесь же `operator<<` и `operator<` (по id).
- `Registry.hpp` — шаблоны: `Registry<T, Cap>` (массив фиксированного размера, журнал отклонённых id) и `sumEnergy(container)` (сумма энергии).
- `ServiceCenter.hpp` — парк: `items_` (`shared_ptr`), витрина `focus_` (`weak_ptr`), журнал `rejected_`. Новая техника приходит как `unique_ptr` и проходит техосмотр (отказ, если в имени есть `broken`), шлемы и станции добавляются без него.
- `main.cpp` — построчно разбирает команды (`add`, `list`, `novice`, `energy`, `report`, `rejected`, `focus`, `remove`, `show_focus`, `quit`) и печатает `error: ...` в единственном `catch`.

## Прочее

- `README.md` — сборка, команды, схема наследования, креативная часть.
- `.gitignore` — исключает бинарник `fleet`.
- `tests/` — сценарии `example`, `focus` (с `.expected`) и `errors` (без `.expected`).
