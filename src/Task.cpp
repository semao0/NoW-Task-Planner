#include "Task.h"

Task::Task(const std::string& name, const std::string& description)
    : name(name), description(description), isCompleted(false)
{
}

void Task::setDeadLine(const std::chrono::system_clock::time_point& newDeadLine)
{
    deadline = newDeadLine;
}

std::chrono::duration<double> Task::getTimeLeft() const
{
    return deadline - std::chrono::system_clock::now();
}

bool Task::isDeadLineMissed() const
{
    return deadline < std::chrono::system_clock::now();
}

void Task::addSubtasks(Task* subtask)
{
    subtasks.push_back(subtask);
}

void Task::markCompleted()
{
    isCompleted = true;
}

std::string Task::getName() const
{
    return name;
}

std::string Task::getDescription() const
{
    return description;
}

std::chrono::system_clock::time_point Task::getDeadline() const
{
    return deadline;
}

std::vector<Task*> Task::getSubtasks() const
{
    return subtasks;
}