#include "InfoWindow.h"
#include "ScrollableList.h"
#include "TaskManager.h"
#include "Label.h"
#include "GUIManager.h"
#include "Button.h"
#include "CreateWindow.h"
#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <chrono>
#include <format>
#include <functional>
#include <memory>
#include <string>
#include "EditWindow.h"
InfoWindow::InfoWindow(Task& task, ScrollableList& Scroll, TaskManager& tasks, bool IsSubTask)
    : window(sf::VideoMode(1000, 700), "NoW - Task Information", sf::Style::Titlebar | sf::Style::Close),
      dummyTask("Dummy",
                "No description",
                std::chrono::year_month_day{std::chrono::year(1970), std::chrono::month(1), std::chrono::day(1)},
                -1,
                false),
      selectedTask(&task), selectedSubTask(&dummyTask)
{
    subtasks = selectedTask->getSubtasks();

    createLabel(400, 75, 100, 40, selectedTask->getName());

    createLabel(100, 75, 100, 40, "Name:");

    createLabel(400, 125, 100, 40, selectedTask->getDescription(), true);

    createLabel(100, 125, 100, 40, "Description:");

    std::string deadlinestr = std::format("{:02}-{:02}-{}",
                                          static_cast<unsigned>(selectedTask->getDeadline().day()),
                                          static_cast<unsigned>(selectedTask->getDeadline().month()),
                                          static_cast<int>(selectedTask->getDeadline().year()));

    createLabel(400, 275, 100, 40, deadlinestr);

    createLabel(100, 275, 100, 40, "Deadline:");

    createButton(810, 630, 170, 40, "Back", [&window = window]() { window.close(); });

    if (!IsSubTask)
    {

        createButton(810,
                     530,
                     170,
                     40,
                     "Info",
                     [this, &tasks = tasks]()
                     {
                         ScrollInfo->onClickCallback(ScrollInfo->getIndex());

                         if (!selectedSubTask->isEmpty())
                         {
                             auto window = std::make_shared<InfoWindow>(*selectedSubTask, *ScrollInfo, tasks, true);
                             window->run();
                         }
                         else
                         {
                             errorManager.showError("SelectedTask clear!");
                         }
                     });

        ScrollInfo = std::make_shared<ScrollableList>(100, 375, 600, 270, 90);
        ScrollInfo->onClickCallback = [this](int index)
        {
            if (!subtasks.empty())
            {
                selectedSubTask = &subtasks[index];
            }
            else
            {
                selectedSubTask = &dummyTask;
            }
        };
        ScrollInfo->setTasks(subtasks);
        InfoElemets.addElement(ScrollInfo);

        createButton(810,
                     580,
                     170,
                     40,
                     "Create subtask",
                     [&Scroll = Scroll, &task = task, &tasks = tasks, this]()
                     {
                         auto window = std::make_shared<CreateWindow>(tasks, *ScrollInfo, &task);
                         window->run();
                         subtasks = selectedTask->getSubtasks();
                         ScrollInfo->setTasks(subtasks);
                     });
        createButton(810,
                     70,
                     170,
                     40,
                     "Edit subtask",
                     [this, &tasks, &task]()
                     {
                         ScrollInfo->onClickCallback(ScrollInfo->getIndex());

                         if (!selectedTask->isEmpty())
                         {
                             auto window = std::make_shared<EditWindow>(*selectedSubTask, tasks, *ScrollInfo, &task);
                             window->run();
                             subtasks = task.getSubtasks();
                             ScrollInfo->setTasks(subtasks);
                         }
                         else
                         {
                             errorManager.showError("SelectedSubTask clear!");
                         }
                     });
        createButton(810,
                     15,
                     170,
                     40,
                     "Delete subtask",
                     [this, &tasks]()
                     {
                         ScrollInfo->onClickCallback(ScrollInfo->getIndex());

                         if (!selectedTask->isEmpty())
                         {
                             selectedTask->removeSubtask(*selectedSubTask);
                             tasks.saveTasks();
                             subtasks = selectedTask->getSubtasks();
                             ScrollInfo->setTasks(subtasks);
                             removeSelection();
                         }
                         else
                         {
                             errorManager.showError("SelectedSubTask clear!");
                         }
                     });
    }
}

void InfoWindow::run()
{
    while (window.isOpen())
    {
        handleEvents();
        render();
    }
}

void InfoWindow::handleEvents()
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            window.close();
        }
        InfoElemets.handleEvent(event);
    }
}

void InfoWindow::render()
{
    window.clear(sf::Color::White);
    InfoElemets.draw(window);

    errorManager.draw(window);
    errorManager.update();

    window.display();
}

void InfoWindow::createLabel(int x, int y, int weight, int height, const std::string& text, bool wrap)
{
    auto label = std::make_shared<Label>(x, y, weight, height, text);
    InfoElemets.addElement(label);
    if (wrap)
    {
        label->wrapText();
    }
}

void InfoWindow::createButton(
    float x, float y, float hight, float weight, const std::string& text, const std::function<void()> OnCLick)
{
    InfoElemets.addElement(std::make_shared<Button>(x, y, hight, weight, text, OnCLick, 20));
}

void InfoWindow::removeSelection()
{
    selectedSubTask = &dummyTask;
    ScrollInfo->setSelectedIndex(-1);
}