#ifndef TASKMANAGER_H
#define TASKMANAGER_H

#include "Task.h"
#include <chrono>
#include <nlohmann/json_fwd.hpp>
#include <vector>
#include <nlohmann/json.hpp>

class TaskManager
{
private:
    std::vector<Task*> tasks;

public:
    void addTask(Task* task);
    void removeTask(Task* task);
    void checkDeadlines();
    const std::vector<Task*>& getTasks() const;
    const int getCountTasks() const;

    void loadTasks();
    void saveTasks() const;
    void clearTasks();

    nlohmann::json serializeTask(const Task* task) const;
    Task* deserializeTask(const nlohmann::json& taskJson);
    void SaveYearMonthDayJson(const std::chrono::year_month_day& deadline, nlohmann::json& taskJson) const;
    std::chrono::year_month_day LoadYearMonthDayJson(const nlohmann::json& taskJson) const;
};
#endif