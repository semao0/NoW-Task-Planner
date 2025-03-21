#pragma once

#include "Task.h"
#include <chrono>
#include <nlohmann/json_fwd.hpp>
#include <vector>
#include <nlohmann/json.hpp>

class TaskManager
{
private:
    std::vector<Task> tasks;
    std::vector<Task> archiveTasks;

public:
    void addTask(const Task& task);
    void addTaskRev(const Task& task);
    void removeTask(const Task& task);
    void updateTask(const Task& updatedTask);
    void checkDeadlines();
    std::vector<Task>& getActiveTasks();
    std::vector<Task>& getArchiveTasks();
    std::vector<Task> getAllTasks();
    int getCountActiveTasks() const;
    int getCountArchiveTasks() const;
    int getCountAllTasks() const;
    std::vector<Task>& getTasks(bool isArchive);
    int getCountTasks(bool isArchive);

    void loadTasks();
    void saveTasks() const;
    void clearTasks();

    nlohmann::json serializeTask(const Task& task) const;
    Task deserializeTask(const nlohmann::json& taskJson);

    void SaveYearMonthDayJson(const std::chrono::year_month_day& deadline, nlohmann::json& taskJson) const;
    std::chrono::year_month_day LoadYearMonthDayJson(const nlohmann::json& taskJson) const;

    nlohmann::json saveCurrentId() const;
    int loadCurrentId(const nlohmann::json& CurrentIdJson) const;

    void archiveTask(Task& task);
    void activatedTask(Task& task);
    void activatedOrArchivatedTask(Task& task, bool isCompleted);
};