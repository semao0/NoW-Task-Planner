cmake_minimum_required(VERSION 3.10)
project(NoW-Task-Planner)

# Указываем стандарт C++
set(CMAKE_CXX_STANDARD 20)

# Настройка компиляторов (если нужно)
set(CMAKE_C_COMPILER "/usr/bin/clang")
set(CMAKE_CXX_COMPILER "/usr/bin/clang++")

# Экспортируем команду компиляции (для инструментов анализа)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Указываем путь к SFML, если установлена вручную, иначе используем глобальную установку
set(SFML_DIR "/path_to_libraries/SFML-2.6.0/lib/cmake/SFML")
find_package(SFML 2.5 REQUIRED COMPONENTS graphics window system)

# Указываем путь к nlohmann_json, если библиотека не установлена через пакетный менеджер
# Если библиотека установлена глобально, можно пропустить этот шаг
set(NLOHMANN_JSON_DIR "/path/to/nlohmann_json")
find_package(nlohmann_json 3.10 REQUIRED PATHS ${NLOHMANN_JSON_DIR})

# Создаем исполняемый файл
add_executable(NoW-Task-Planner
    src/main.cpp
    src/Windows/MainWindow.cpp
    src/Windows/InfoWindow.cpp
    src/Windows/ArchiveWindow.cpp
    src/Windows/CreateWindow.cpp
    src/Windows/EditWindow.cpp
    src/Task.cpp
    src/TaskManager.cpp
    src/Elements/ScrollableList.cpp
    src/Elements/CalendarWidget.cpp
    src/Elements/FontManager.cpp
    src/Elements/ErrorManager.cpp
)

# Подключаем библиотеки
target_link_libraries(NoW-Task-Planner
    PRIVATE
        sfml-graphics
        sfml-window
        sfml-system
        nlohmann_json::nlohmann_json
)

# Добавление заголовочных файлов
target_include_directories(NoW-Task-Planner PRIVATE
    ${CMAKE_SOURCE_DIR}/src/Elements
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/src/Windows
)