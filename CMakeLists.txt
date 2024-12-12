cmake_minimum_required(VERSION 3.10)
project(TaskPlanner)

# Указываем стандарт C++
set(CMAKE_C_COMPILER "/usr/bin/clang")
set(CMAKE_CXX_COMPILER "/usr/bin/clang++")
set(CMAKE_CXX_STANDARD 17)

# Добавляем исходные файлы
add_executable(TaskPlanner src/main.cpp)

# Подключаем SFML
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)
target_link_libraries(TaskPlanner sfml-graphics sfml-window sfml-system)