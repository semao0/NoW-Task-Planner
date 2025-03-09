#include "Task.h"
#include <chrono>

Task::Task(
    const std::string& name, const std::string& description, std::chrono::year_month_day deadline, int id, bool status)
    : name(name), description(description), status(status), deadline(deadline), id(id)
{
}
void Task::setDeadLine(const std::chrono::year_month_day newDeadLine)
{
    deadline = newDeadLine;
}

std::chrono::days Task::getTimeLeft() const
{
    auto now = floor<std::chrono::days>(std::chrono::system_clock::now());
    auto deadline_days = std::chrono::sys_days(deadline);
    if (deadline_days < now)
    {
        return std::chrono::days(0);
    }
    return deadline_days - now;
}

bool Task::isDeadLineActive() const
{
    auto now = floor<std::chrono::days>(std::chrono::system_clock::now());
    return std::chrono::sys_days(deadline) >= now;
}

void Task::addSubtasks(const Task& subtask)
{
    subtasks.push_back(subtask);
}

void Task::addSubtasks(const std::vector<Task>& subtasks)
{
    this->subtasks.insert(this->subtasks.end(), subtasks.begin(), subtasks.end());
}

void Task::toggleCompletion()
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
    return this->getId() == other.getId();
}

Task& Task::operator=(const Task& other)
{
    if (this != &other)
    {
        this->name = other.name;
        this->description = other.description;
        this->deadline = other.deadline;
        this->status = other.status;
        this->id = other.id;

        this->subtasks = other.subtasks;
    }

    return *this;
}

bool Task::isEmpty() const
{
    return name.empty() && description.empty() &&
               deadline ==
                   std::chrono::year_month_day{std::chrono::year(1970), std::chrono::month(1), std::chrono::day(1)} ||
           id == -1;
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

void Task::setName(const std::string& name)
{
    this->name = name;
}
void Task::setDescription(const std::string& description)
{
    this->description = description;
}

void Task::updateSubTask(const Task& subtask)
{
    for(auto& sub : subtasks)
    {
        if(sub.id == subtask.getId())
        {
                sub = subtask;
                return;
        }
    }
}

void Task::removeSubtask(const Task& subTask)
{
    auto it = std::find(subtasks.begin(), subtasks.end(), subTask);
    if(it != subtasks.end())
    {
        subtasks.erase(it);
    }
}