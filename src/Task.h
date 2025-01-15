#ifndef TASK_H
#define TASK_H

#include <string>
#include <vector>
#include <chrono>
class Task
{
private:
    std::string name;
    std::string description;
    std::vector<Task> subtasks;
    bool isCompleted;
    std::chrono::year_month_day deadline;

public:
    bool operator==(const Task& other) const;
    Task(const std::string& name, const std::string& description, std::chrono::year_month_day a);

    void setDeadLine(const std::chrono::year_month_day);
    std::chrono::days getTimeLeft() const;
    bool isDeadLineActive() const;

    void addSubtasks(const Task& subtask);
    void markCompleted();
    std::string getName() const;
    std::string getDescription() const;
    std::chrono::year_month_day getDeadline() const;
    std::vector<Task> getSubtasks() const;
};
#endif