#include "TaskManager.h"
#include <chrono>

int main()
{
    TaskManager manager;

    auto task1 = new Task("Finish Project", "Complete the task planner project");
    auto now = std::chrono::system_clock::now();
    task1->setDeadLine(now + std::chrono::hours(2));

    manager.addTask(task1);

    manager.checkDeadlines();
    return 0;
}
