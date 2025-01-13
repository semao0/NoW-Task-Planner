#include "TaskManager.h"
#include "Task.h"
#include <algorithm>
#include <chrono>
#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

void TaskManager::addTask(const Task& task)
{
    tasks.push_back(task);
}
void TaskManager::removeTask(const Task& task)
{
    tasks.erase(std::remove(tasks.begin(), tasks.end(), task), tasks.end());
}
void TaskManager::checkDeadlines()
{
    for (auto* task : tasks)
    {
        if (!task->isDeadLineActive())
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

const int TaskManager::getCountTasks() const
{
    return tasks.size();
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
    SaveYearMonthDayJson(task->getDeadline(), taskJson);
    taskJson["subtasks"] = json::array();

    for (const auto* subtask : task->getSubtasks())
    {
        taskJson["subtasks"].push_back(serializeTask(subtask));
    }

    return taskJson;
}

Task* TaskManager::deserializeTask(const json& taskJson)
{
    Task* task = new Task(taskJson["name"], taskJson["description"], LoadYearMonthDayJson(taskJson));

    for (const auto& subtasksJson : taskJson["subtasks"])
        task->addSubtasks(deserializeTask(subtasksJson));

    return task;
}

void TaskManager::SaveYearMonthDayJson(const std::chrono::year_month_day& deadline, nlohmann::json& taskJson) const
{
    taskJson["year"] = int(deadline.year());
    taskJson["month"] = unsigned(deadline.month());
    taskJson["day"] = unsigned(deadline.day());
}
std::chrono::year_month_day TaskManager::LoadYearMonthDayJson(const nlohmann::json& taskJson) const
{
    int year = taskJson["year"];
    unsigned month = taskJson["month"];
    unsigned day = taskJson["day"];
    return std::chrono::year_month_day{std::chrono::year{year}, std::chrono::month{month}, std::chrono::day{day}};
}

void TaskManager::clearTasks()
{
    std::ofstream file("tasks.json", std::ios::trunc);
    file << "[]";
    file.close();
}