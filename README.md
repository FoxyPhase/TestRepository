# 📜 Текстовая игра на C++ и MySQL

## 📌 Описание проекта
Эта текстовая игра разрабатывается на **C++** с использованием **только стандартной библиотеки** и **MySQL**. Проект включает в себя:
- 📖 **Главы** – сюжетная структура с различными событиями.
- 💬 **Диалоги** – интерактивное взаимодействие с персонажами.
- 🎭 **Выборы** – влияющие на ход истории и её исход.
- 🔑 **Вход и регистрация** – работа с базой данных MySQL для сохранения пользователей.

## 🛠️ Технологии
- **C++** (Standard Library only)
- **MySQL** (работа с базой данных)

## 📂 Структура проекта
```plaintext
📦 text_game
├── 📜 README.md          # Описание проекта
├── 📂 src                # Исходный код игры
│   ├── main.cpp         # Основной файл
│   ├── game.cpp         # Логика игры
│   ├── dialogs.cpp      # Диалоги и выборы
│   ├── database.cpp     # Работа с MySQL
│   └── utils.cpp        # Вспомогательные функции
├── 📂 include            # Заголовочные файлы
├── 📂 sql                # Скрипты для базы данных
│   ├── init.sql         # Инициализация таблиц
│   ├── queries.sql      # Запросы к базе данных
└── 📂 docs               # Документация
```

## 🚀 Запуск проекта
### 1️⃣ Установка зависимостей
Перед запуском убедитесь, что у вас установлены:
- **Компилятор C++** (g++, MSVC, Clang)
- **MySQL сервер**
- **MySQL Connector/C++**

### 2️⃣ Подключение базы данных
1. Запустите MySQL сервер.
2. Создайте базу данных с помощью `sql/init.sql`.
3. Настройте параметры подключения в `database.cpp`.

### 3️⃣ Компиляция и запуск
```sh
g++ -o game src/*.cpp -lmysqlclient
./game
```

## 📌 Фичи на будущее
- 🎮 **Инвентарь** – предметы, которые можно собирать и использовать.
- 🏆 **Система достижений** – награды за ключевые события.
- 🔄 **Сохранения и загрузка** – продолжение игры с сохранённого момента.

## 🤝 Контрибьютинг
Если хотите помочь с разработкой, создавайте **Issues** или **Pull Requests**! 😃
