#ifndef TASKMANAGER_H
#define TASKMANAGER_H

#include "Task.h"
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

    void loadTasks();
    void saveTasks() const;
    void clearTasks();

    nlohmann::json serializeTask(const Task* task) const;
    Task* deserializeTask(const nlohmann::json& taskJson);
};
#endif