#include "ArchiveWindow.h"
#include "ScrollableList.h"
#include "InfoWindow.h"
#include "TaskManager.h"
#include "guiManager.h"
#include "Button.h"
#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <iostream>
#include "EditWindow.h"
#include <memory>

ArchiveWindow::ArchiveWindow(TaskManager& tasks, ScrollableList& MainScroll)
    : window(sf::VideoMode(1000, 700), "NoW - Archive", sf::Style::Titlebar | sf::Style::Close), tasks(tasks),
      dummyTask("Dummy",
                "No description",
                std::chrono::year_month_day{std::chrono::year(1970), std::chrono::month(1), std::chrono::day(1)},
                -1,
                false),
      selectedTaskArc(&dummyTask)
{
    ScrollArchive = std::make_shared<ScrollableList>(20, 20, 600, 600, 100, true, true);
    ScrollArchive->onClickCallback = [this, &tasks](int index)
    {
        if (!tasks.getArchiveTasks().empty() && index >= 0)
        {
            selectedTaskArc = &tasks.getArchiveTasks()[index];
        }
        else
        {
            selectedTaskArc = &dummyTask;
        }
    };
    ScrollArchive->onCheckBoxToggle = [this, &tasks, &MainScroll](Task& t)
    {
        tasks.activatedOrArchivatedTask(t, t.isCompleted());
        tasks.saveTasks();
    };
    auto buttonEdit = std::make_shared<Button>(
        810,
        70,
        170,
        40,
        "Edit task",
        [this, &tasks]()
        {
            ScrollArchive->onClickCallback(ScrollArchive->getIndex());

            if (!selectedTaskArc->isEmpty())
            {
                auto window = std::make_shared<EditWindow>(*selectedTaskArc, tasks, *ScrollArchive);
                window->run();
            }
            else
            {
                std::cout << "SelectedTasks clear!" << std::endl;
            }
        },
        20);
    auto buttonInfo = std::make_shared<Button>(
        810,
        645,
        170,
        40,
        "Info",
        [this, &tasks]()
        {
            ScrollArchive->onClickCallback(ScrollArchive->getIndex());

            if (!selectedTaskArc->isEmpty())
            {
                auto window = std::make_shared<InfoWindow>(*selectedTaskArc, *ScrollArchive, tasks);
                window->run();
            }
            else
            {
                std::cout << "SelectedTasks clear!" << std::endl;
            }
        },
        20);
    ArchiveElemets.addElement(buttonInfo);
    ArchiveElemets.addElement(buttonEdit);
    ArchiveElemets.addElement(ScrollArchive);
    tasks.loadTasks();
    ScrollArchive->setTasks(tasks);
}

void ArchiveWindow::run()
{
    while (window.isOpen())
    {
        handleEvents();
        render();
    }
}
void ArchiveWindow::handleEvents()
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            window.close();
        }
        ArchiveElemets.handleEvent(event);
    }
}
void ArchiveWindow::render()
{
    window.clear(sf::Color::White);
    ArchiveElemets.draw(window);
    window.display();
}