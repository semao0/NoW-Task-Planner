#include "MainWindow.h"
#include "ArchiveWindow.h"
#include "CreateWindow.h"
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

MainWindow::MainWindow()
    : window(sf::VideoMode(1000, 700), "NoW", sf::Style::Titlebar | sf::Style::Close),
      dummyTask("Dummy",
                "No description",
                std::chrono::year_month_day{std::chrono::year(1970), std::chrono::month(1), std::chrono::day(1)},
                -1,
                false),
      selectedTask(&dummyTask)
{
    Scroll = std::make_shared<ScrollableList>(20, 20, 600, 600, 100, true, false);
    Scroll->onClickCallback = [this](int index)
    {
        if (!tasks.getActiveTasks().empty() && index >= 0)
        {
            selectedTask = &tasks.getActiveTasks()[index];
        }
        else
        {
            selectedTask = &dummyTask;
        }
    };
    Scroll->onCheckBoxToggle = [this](Task& t)
    {
        tasks.activatedOrArchivatedTask(t, t.isCompleted());
        tasks.saveTasks();
    };

    auto buttonCreate = std::make_shared<Button>(
        810,
        15,
        170,
        40,
        "Create new task",
        [this, &Scroll = Scroll]()
        {
            tasks.loadTasks();
            Scroll->onClickCallback(Scroll->getIndex());
            auto window = std::make_shared<CreateWindow>(tasks, *Scroll);
            window->run();
        },
        20);
    auto buttonEdit = std::make_shared<Button>(
        810,
        70,
        170,
        40,
        "Edit task",
        [this]()
        {
            Scroll->onClickCallback(Scroll->getIndex());

            if (!selectedTask->isEmpty())
            {
                auto window = std::make_shared<EditWindow>(*selectedTask, tasks, *Scroll);
                window->run();
            }
            else
            {
                std::cout << "SelectedTasks clear!" << std::endl;
            }
        },
        20);
    auto buttonArchive = std::make_shared<Button>(
        810,
        450,
        170,
        40,
        "Archive",
        [this]()
        {
            auto window = std::make_shared<ArchiveWindow>(tasks, *Scroll);
            window->run();
            tasks.loadTasks();
            Scroll->setTasks(tasks);
        },
        20);
    auto buttonInfo = std::make_shared<Button>(
        810,
        645,
        170,
        40,
        "Info",
        [this, &Scroll = Scroll, &tasks = tasks]()
        {
            Scroll->onClickCallback(Scroll->getIndex());

            if (!selectedTask->isEmpty())
            {
                auto window = std::make_shared<InfoWindow>(*selectedTask, *Scroll, tasks);
                window->run();
            }
            else
            {
                std::cout << "SelectedTasks clear!" << std::endl;
            }
        },
        20);
    MainElemets.addElement(buttonInfo);
    MainElemets.addElement(buttonEdit);
    MainElemets.addElement(buttonCreate);
    MainElemets.addElement(Scroll);
    MainElemets.addElement(buttonArchive);
    tasks.loadTasks();
    Scroll->setTasks(tasks);
}

void MainWindow::run()
{
    while (window.isOpen())
    {
        handleEvents();
        render();
    }
}
void MainWindow::handleEvents()
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            window.close();
        }
        MainElemets.handleEvent(event);
    }
}
void MainWindow::render()
{
    window.clear(sf::Color::White);
    MainElemets.draw(window);
    window.display();
}