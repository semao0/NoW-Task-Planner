#include "TaskManager.h"
#include <algorithm>
#include <iostream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

void TaskManager::addTask(Task* task)
{
    tasks.push_back(task);
}
void TaskManager::removeTask(Task* task)
{
    tasks.erase(std::remove(tasks.begin(), tasks.end(), task), tasks.end());
}
void TaskManager::checkDeadlines()
{
    for (auto* task : tasks)
    {
        if (task->isDeadLineMissed())
        {
            std::cout << "Дедлайн задачи \"" << task->getName() << "\" истек!" << std::endl;
        }
        else
        {
            std::cout << "Дедлайн задачи \"" << task->getName() << "\" еще не истек!" << std::endl;
        }
    }
}
const std::vector<Task*>& TaskManager::getTasks() const
{
    return tasks;
}

void TaskManager::loadTasks() 
{

}

void TaskManager::saveTasks() const
{

}