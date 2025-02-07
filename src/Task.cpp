#include "Task.h"
#include <bits/chrono.h>
#include <chrono>
#include <cstddef>
#include <iterator>

Task::Task(const std::string& name, const std::string& description, std::chrono::year_month_day deadline)
    : name(name), description(description), isCompleted(false),
      deadline(deadline.year(), deadline.month(), deadline.day())
{
}

Task::Task() {}

void Task::setDeadLine(const std::chrono::year_month_day newDeadLine)
{
    deadline = newDeadLine;
}

std::chrono::days Task::getTimeLeft() const
{
    auto timenow = floor<std::chrono::days>(std::chrono::system_clock::now());
    std::chrono::sys_days deadline_days = std::chrono::sys_days(deadline);
    return deadline_days - timenow;
}

bool Task::isDeadLineActive() const
{
    auto daysnow = floor<std::chrono::days>(std::chrono::system_clock::now());
    std::chrono::year_month_day now{daysnow};
    return deadline >= now;
}

void Task::addSubtasks(const Task& subtask)
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

std::chrono::year_month_day Task::getDeadline() const
{
    return deadline;
}

std::vector<Task> Task::getSubtasks() const
{
    return subtasks;
}
bool Task::operator==(const Task& other) const
{
    if (this->name == other.name && this->description == other.description && this->deadline == other.deadline)
    {
        return true;
    }
    else
    {
        return false;
    }
}

Task& Task::operator=(const Task& other)
{
    this->name = other.name;
    this->description = other.description;
    this->deadline = other.deadline;

    this->subtasks.clear();
    for (auto task : other.subtasks)
    {
        this->addSubtasks(task);
    }

    return *this;
}

bool Task::isEmpty() const
{
    return name.empty() && description.empty();
}