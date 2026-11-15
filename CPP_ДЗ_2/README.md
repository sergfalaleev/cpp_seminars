# ФизКат

Учёт парка кикшеринга.

## Сборка и запуск

```sh
clang++ -std=c++17 -Wall main.cpp -o fleet
./fleet
```

## Команды

`add scooter|ebike id name energy score`, `add bike id name score`, `add helmet id name`,
`add dock id name energy`, `energy`, `report`, `novice`, `list`, `focus id`, `show_focus`,
`remove id`, `rejected`, `quit`. `add monocycle id name energy score` (это моя)

Техосмотр отклоняет транспорт, в имени которого есть `broken` (без учёта регистра).

## Наследование (`Items.hpp`)

```
InventoryItem (абстрактный)      EnergyConsumer (абстрактный)
└── Item (id и имя)                   │
    ├── Transport                     │
    │   ├── Bike                      │
    │   ├── ElectricScooter ──────────┤ множественное наследование
    │   ├── ElectricBike ─────────────┤
    │   └── Monocycle ────────────────┤
    ├── Helmet                        │
    └── DockStation ──────────────────┘
```

Ромба нет: `EnergyConsumer` не наследует `InventoryItem`, поэтому `virtual public` не нужен.

## Умные указатели (`ServiceCenter.hpp`)

- `unique_ptr` — новая единица до техосмотра. При отказе объект удаляется сам.
- `shared_ptr` — принятые единицы (`items_`).
- `weak_ptr` — витрина (`focus_`). После `remove` выводится `expired`.

## Исключения (`Errors.hpp`)

- `InspectionError` — техосмотр отклонил транспорт.
- `CommandError` — плохая команда или аргументы, занятый или ненайденный id.

## Шаблоны (`Registry.hpp`)

- `Registry<T, Cap>` — журнал id отклонённой техники, команда `rejected`.
- `sumEnergy(container)` — считает энергию для команд `energy` и `report`.

## Креативная часть

Новый класс Monocycle, по поведению схож с ElectricScooter, переопределен `isNoviceFriendly()`, возвращающий false. Команды `report` -- печатает количество itemов и их totalEnergy. `rejected` -- печатает id всей техники, которую отклонил техосмотр.

## Использование ИИ
ИИ добавил README.md, приводил примеры к коду, говорил с чего вообще начинать и составил план разработки. Также я просил проверять код на логические и стилевые ошибки.