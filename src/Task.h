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
    std::vector<Task*> subtasks;
    bool isCompleted;
    std::chrono::system_clock::time_point deadline;

public:
    Task(const std::string& name, const std::string& description);

    void setDeadLine(const std::chrono::system_clock::time_point& newDeadLine);
    std::chrono::duration<double> getTimeLeft() const;
    bool isDeadLineMissed() const;

    void addSubtasks(Task* subtask);
    void markCompleted();
    std::string getName() const;
    std::string getDescription() const;
    std::chrono::system_clock::time_point getDeadline() const;
    std::vector<Task*> getSubtasks() const;
};
#endif