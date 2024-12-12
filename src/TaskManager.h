#ifndef TASKMANAGER_H
#define TASKMANAGER_H

#include "Task.h"
#include <vector>

class TaskManager
{
private:
    std::vector<Task*> tasks;

public:
void addTask(Task* task);
void removeTask(Task* task);
void checkDeadlines();
const std::vector<Task*>& getTasks() const;
};
#endif