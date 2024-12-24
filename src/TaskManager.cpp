#include "TaskManager.h"
#include <algorithm>
#include <chrono>
#include <fstream>
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

void TaskManager::saveTasks() const
{
    json j = json::array();

    for (const auto* task : tasks)
    {
        j.push_back(serializeTask(task));
    }

    std::ofstream file("tasks.json", std::ios::trunc);
    file << j.dump(4);
    file.close();
}

void TaskManager::loadTasks()
{
    std::ifstream file("tasks.json");

    if (file)
    {
        json j;
        file >> j;
        file.close();
        file.clear();

        for (const auto& taskJson : j)
            tasks.push_back(deserializeTask(taskJson));
    }
}

json TaskManager::serializeTask(const Task* task) const
{
    json taskJson;
    taskJson["name"] = task->getName();
    taskJson["description"] = task->getDescription();
    taskJson["deadline"] =
        std::chrono::duration_cast<std::chrono::seconds>(task->getDeadline().time_since_epoch()).count();
    taskJson["subtasks"] = json::array();

    for (const auto* subtask : task->getSubtasks())
    {
        taskJson["subtasks"].push_back(serializeTask(subtask));
    }

    return taskJson;
}

Task* TaskManager::deserializeTask(const json& taskJson)
{
    Task* task = new Task(taskJson["name"], taskJson["description"]);

    std::chrono::seconds deadline_seconds(taskJson["deadline"]);
    task->setDeadLine(std::chrono::system_clock::time_point(deadline_seconds));

    for (const auto& subtasksJson : taskJson["subtasks"])
        task->addSubtasks(deserializeTask(subtasksJson));

    return task;
}

void TaskManager::clearTasks()
{
    std::ofstream file("tasks.json", std::ios::trunc);
    file << "[]";
    file.close();
}