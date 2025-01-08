#include "TaskManager.h"
#include "MainWindow.h"
#include <chrono>
#include <ctime>
#include <iostream>
#include <sched.h>

int main()
{
    MainWindow window;
    window.run();
    return 0;
}
