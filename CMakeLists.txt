cmake_minimum_required(VERSION 3.10)
project(TaskPlanner)

# Указываем стандарт C++
set(CMAKE_C_COMPILER "/usr/bin/clang")
set(CMAKE_CXX_COMPILER "/usr/bin/clang++")
set(CMAKE_CXX_STANDARD 17)

# CMakeLists.txt
add_executable(TaskPlanner src/main.cpp src/Task.cpp src/TaskManager.cpp)

# Подключаем SFML
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)
target_link_libraries(TaskPlanner sfml-graphics sfml-window sfml-system)

# nlohmann_json
find_package(nlohmann_json 3.10.0 REQUIRED)
target_link_libraries(TaskPlanner nlohmann_json::nlohmann_json)