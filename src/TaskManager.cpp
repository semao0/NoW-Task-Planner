#include "TaskManager.h"
#include "Task.h"
#include <algorithm>
#include <chrono>
#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>
#include <stdexcept>

using json = nlohmann::json;

void TaskManager::addTask(const Task& task)
{
    if (task.isCompleted())
    {
        ArchiveTasks.insert(ArchiveTasks.begin(), task);
    }
    else
    {
        tasks.insert(tasks.begin(), task);
    }
}
void TaskManager::removeTask(const Task& task)
{
    auto removeFromList = [](std::vector<Task>& list, const Task& task)
    {
        auto it = std::remove(list.begin(), list.end(), task);
        if (it != list.end())
        {
            list.erase(it, list.end());
        }
    };
    removeFromList(tasks, task);
    removeFromList(ArchiveTasks, task);
}
std::vector<Task>& TaskManager::getActiveTasks()
{
    return tasks;
}

std::vector<Task>& TaskManager::getArchiveTasks()
{
    return ArchiveTasks;
}

std::vector<Task> TaskManager::getAllTasks()
{
    std::vector<Task> allTasks = tasks;
    allTasks.insert(allTasks.end(), ArchiveTasks.begin(), ArchiveTasks.end());
    return allTasks;
}

const int TaskManager::getCountActiveTasks() const
{
    return tasks.size();
}

const int TaskManager::getCountArchiveTasks() const
{
    return ArchiveTasks.size();
}

const int TaskManager::getCountAllTasks() const
{
    return ArchiveTasks.size() + tasks.size();
}

void TaskManager::saveTasks() const
{
    json j;
    j["tasks"] = json::array();
    j["archivetasks"] = json::array();
    j["currentid"] = saveCurrentId();

    for (const auto task : tasks)
    {
        j["tasks"].push_back(serializeTask(task));
    }

    for (const auto task : ArchiveTasks)
    {
        j["archivetasks"].push_back(serializeTask(task));
    }
    std::ofstream file("tasks.json", std::ios::trunc);
    if (!file.is_open())
    {
        throw std::runtime_error("Не удалость открыть файл tasks.json для записи!");
    }
    file << j.dump(4);
    file.close();
}

void TaskManager::loadTasks()
{
    std::ifstream file("tasks.json");

    if (!file.is_open())
    {
        throw std::runtime_error("Не удалось открыть файл tasks.json для чтения!");
    }
    if (file.peek() == std::ifstream::traits_type::eof())
    {
        file.close();
        return;
    }
    json j;
    file >> j;
    file.close();
    file.clear();

    tasks.clear();
    ArchiveTasks.clear();
    if (j.contains("tasks"))
    {
        for (const auto& taskJson : j["tasks"])
        {
            tasks.push_back(deserializeTask(taskJson));
        }
    }

    if (j.contains("archivetasks"))
    {
        for (const auto& taskJson : j["archivetasks"])
        {
            ArchiveTasks.push_back(deserializeTask(taskJson));
        }
    }

    if (j.contains("currentid") && j["currentid"].is_number_integer())
    {
        Task::setCurrentId(j["currentid"]);
    }
}

json TaskManager::serializeTask(const Task& task) const
{
    json taskJson;
    taskJson["name"] = task.getName();
    taskJson["description"] = task.getDescription();
    taskJson["status"] = task.isCompleted();
    taskJson["id"] = task.getId();
    SaveYearMonthDayJson(task.getDeadline(), taskJson);
    taskJson["subtasks"] = json::array();

    for (const auto& subtask : task.getSubtasks())
    {
        taskJson["subtasks"].push_back(serializeTask(subtask));
    }
    return taskJson;
}

json TaskManager::saveCurrentId() const
{
    return Task::getCurrentId();
}

int TaskManager::loadCurrentId(const json& data) const
{
    if (data.is_number_integer())
    {
        return data.get<int>();
    }
    return 0;
}

Task TaskManager::deserializeTask(const json& taskJson)
{
    std::chrono::year_month_day deadline;
    if (taskJson.contains("year") && taskJson.contains("day"), taskJson.contains("month"))
    {
        deadline = LoadYearMonthDayJson(taskJson);
    }
    else
    {
        deadline = {std::chrono::year(1970), std::chrono::month(1), std::chrono::day(1)};
    }

    bool status = taskJson.value("status", false);
    int id = taskJson.value("id", -1);
    Task task(taskJson["name"], taskJson["description"], deadline, id, status);
    if (taskJson.contains("subtasks") && taskJson["subtasks"].is_array())
    {
        task.getSubtasks().reserve(taskJson["subtasks"].size());
        for (const auto subtasksJson : taskJson["subtasks"])
        {
            task.addSubtasks(deserializeTask(subtasksJson));
        }
    }

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

    if (month < 1 || month > 12 || day < 1 || day > 31)
    {
        throw std::invalid_argument("Некоректная дата в JSON!");
    }
    return std::chrono::year_month_day{std::chrono::year{year}, std::chrono::month{month}, std::chrono::day{day}};
}

void TaskManager::clearTasks()
{
    std::ofstream file("tasks.json", std::ios::trunc);
    file << "[]";
    file.close();
}

void TaskManager::updateTask(const Task& updatedTask)
{
    auto updateInList = [](std::vector<Task>& list, const Task& updatedTask)
    {
        for (auto& task : list)
        {
            if (task == updatedTask)
            {
                task = updatedTask;
                return;
            }
        }
    };

    updateInList(tasks, updatedTask);
    updateInList(ArchiveTasks, updatedTask);
}

void TaskManager::archiveTask(Task& task)
{
    auto it = std::find(tasks.begin(), tasks.end(), task);
    if (it != tasks.end())
    {
        ArchiveTasks.push_back(*it);
        tasks.erase(it);
        it->revCompleted();
        updateTask(*it);
    }
}

void TaskManager::activatedTask(Task& task)
{
    auto it = std::find(ArchiveTasks.begin(), ArchiveTasks.end(), task);
    if (it != ArchiveTasks.end())
    {
        tasks.push_back(*it);
        ArchiveTasks.erase(it);
        it->revCompleted();
        updateTask(*it);
    }
}

std::vector<Task>& TaskManager::getTasks(bool isArchive)
{
    return isArchive ? ArchiveTasks : tasks;
}

int TaskManager::getCountTasks(bool isArchive)
{
    return isArchive ? ArchiveTasks.size() : tasks.size();
}

void TaskManager::activatedOrArchivatedTask(Task& task, bool isCompleted)
{
    auto& listFrom = isCompleted ? ArchiveTasks : tasks;
    auto& listTo = isCompleted ? tasks : ArchiveTasks;

    auto it = std::find_if(listFrom.begin(), listFrom.end(),
                           [&task](const Task& t) { return t == task; });

    if (it != listFrom.end())
    {
        it->revCompleted();
        listTo.push_back(std::move(*it));
        listFrom.erase(it);
    }
}
