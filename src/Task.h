#pragma once

#include <string>
#include <vector>
#include <chrono>
class Task
{
private:
    int id;
    std::string name;
    std::string description;
    std::vector<Task> subtasks;
    bool status;
    std::chrono::year_month_day deadline;
    static int currentId;

public:
    bool operator==(const Task& other) const;
    Task& operator=(const Task& other);
    Task(const std::string& name,
         const std::string& description,
         std::chrono::year_month_day a,
         int id,
         bool status = false);

    void updateSubTask(const Task& subtask);
    void removeSubtask(const Task& subTask);

    void setDeadLine(const std::chrono::year_month_day);
    std::chrono::days getTimeLeft() const;
    bool isDeadLineActive() const;
    int getId() const;
    void setName(const std::string& name);
    void setDescription(const std::string& description);

    void addSubtasks(const Task& subtask);
    void addSubtasks(const std::vector<Task>& subtask);
    void toggleCompletion();
    std::string getName() const;
    std::string getDescription() const;
    std::chrono::year_month_day getDeadline() const;
    std::vector<Task> getSubtasks() const;
    bool isEmpty() const;
    bool isCompleted() const;

    static void setCurrentId(const int id)
    {
        currentId = id;
    }

    static int getCurrentId()
    {
        return currentId;
    }

    static int generateUniqueId()
    {
        return ++currentId;
    }
};