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
#include <iomanip>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
InfoWindow::InfoWindow(Task& task, ScrollableList& Scroll, TaskManager& tasks, bool IsSubTask)
    : window(sf::VideoMode(1000, 700), "NoW - Task Information", sf::Style::Titlebar | sf::Style::Close),
      dummyTask("Dummy",
                "No description",
                std::chrono::year_month_day{std::chrono::year(1970), std::chrono::month(1), std::chrono::day(1)},
                -1,
                false),
      selectedTask(&task), selectedSubTask(&dummyTask)
{
    subtasks = task.getSubtasks();
    auto namelabeltask = std::make_shared<Label>(400, 100, 100, 40, selectedTask->getName());
    InfoElemets.addElement(namelabeltask);
    auto namelabel = std::make_shared<Label>(100, 100, 100, 40, "Name:");
    InfoElemets.addElement(namelabel);

    auto desclabeltask = std::make_shared<Label>(400, 150, 100, 40, selectedTask->getDescription());
    InfoElemets.addElement(desclabeltask);
    desclabeltask->wrapText();
    auto desclabel = std::make_shared<Label>(100, 150, 100, 40, "Description:");
    InfoElemets.addElement(desclabel);

    std::ostringstream deadline;
    deadline << std::setw(2) << std::setfill('0') << static_cast<unsigned>(selectedTask->getDeadline().day()) << '-'
             << std::setw(2) << std::setfill('0') << static_cast<unsigned>(selectedTask->getDeadline().month()) << '-'
             << static_cast<int>(selectedTask->getDeadline().year());
    std::string deadlinestr = deadline.str();

    auto deadlinelabeltask = std::make_shared<Label>(400, 300, 100, 40, deadlinestr);
    InfoElemets.addElement(deadlinelabeltask);
    auto deadlinelabel = std::make_shared<Label>(100, 300, 100, 40, "Deadline:");
    InfoElemets.addElement(deadlinelabel);

    auto buttonSave = std::make_shared<Button>(810, 630, 170, 40, "Back", [&window = window]() { window.close(); }, 20);
    InfoElemets.addElement(buttonSave);

    if (!IsSubTask)
    {
        auto buttonInfo = std::make_shared<Button>(
            810,
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
                    std::cout << "SelectedSubTask clear!" << std::endl;
                }
            },
            20);
        InfoElemets.addElement(buttonInfo);

        ScrollInfo = std::make_shared<ScrollableList>(100, 400, 600, 270, 90);
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

        auto buttonCreateSubtask = std::make_shared<Button>(
            810,
            580,
            170,
            40,
            "Create subtask",
            [&Scroll = Scroll, &task = task, &tasks = tasks, this]()
            {
                auto window = std::make_shared<CreateWindow>(tasks, *ScrollInfo, &task);
                window->run();
                subtasks = task.getSubtasks();
                ScrollInfo->setTasks(subtasks);
            },
            20);
        InfoElemets.addElement(buttonCreateSubtask);
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
    window.display();
}
