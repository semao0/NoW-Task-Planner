#include "Task.h"
#include <bits/chrono.h>
#include <chrono>

Task::Task(
    const std::string& name, const std::string& description, std::chrono::year_month_day deadline, int id, bool status)
    : name(name), description(description), status(status), deadline(deadline.year(), deadline.month(), deadline.day()),
      id(id)
{
}
//Task::Task(const std::string& name, const std::string& description, std::chrono::year_month_day deadline, bool status)
    //: name(name), description(description), status(status), deadline(deadline.year(), deadline.month(), deadline.day()),
     // id(generateUniqueId())
//{
//}

//Task::Task() :id(generateUniqueId()){} 
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

void Task::revCompleted()
{
    status = !status;
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
    return this->getId() == other.getId()? true : false;
}

Task& Task::operator=(const Task& other)
{
    this->name = other.name;
    this->description = other.description;
    this->deadline = other.deadline;
    this->status = other.status;
    this->id = other.id;

    this->subtasks.clear();
    for (auto task : other.subtasks)
    {
        this->addSubtasks(task);
    }

    return *this;
}

bool Task::isEmpty() const
{
    return name.empty() && description.empty() &&
           deadline == std::chrono::year_month_day{std::chrono::year(1970), std::chrono::month(1), std::chrono::day(1)} || id == -1;
}

bool Task::isCompleted() const
{
    return status;
}

int Task::currentId = 0;

int Task::getId() const
{
    return this->id;
}