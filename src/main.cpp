#include "TaskManager.h"
#include "MainWindow.h"
#include <chrono>
#include <iostream>

int main()
{
    std::cout << "Рабочая директория: " << std::filesystem::current_path() << std::endl;
    MainWindow window;
    window.run();

    return 0;
}
