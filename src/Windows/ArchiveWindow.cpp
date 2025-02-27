#include "ArchiveWindow.h"
#include "CreateWindow.h"
#include "ScrollableList.h"
#include "InfoWindow.h"
#include "TaskManager.h"
#include "guiManager.h"
#include "Button.h"
#include "TextInput.h"
#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <iostream>
#include "EditWindow.h"
#include <memory>

ArchiveWindow::ArchiveWindow()
    : window(sf::VideoMode(1000, 700), "NoW", sf::Style::Titlebar | sf::Style::Close), selectedTask(dummyTask)
{
    dummyTask.setDeadLine(
        std::chrono::year_month_day{std::chrono::year(1970), std::chrono::month(1), std::chrono::day(1)});
    Scroll = std::make_shared<ScrollableList>(20, 20, 600, 600, 100, true);
    Scroll->onClickCallback = [this](int index)
    {
        if (!ArhiveTasks.getArchiveTasks().empty() && index >= 0)
        {
            selectedTask = ArhiveTasks.getArchiveTasks()[index];
        }
        else
        {
            selectedTask = dummyTask;
        }
    };
    auto buttonEdit = std::make_shared<Button>(
        810,
        70,
        170,
        40,
        "Edit task",
        [this]()
        {
            Scroll->onClickCallback(Scroll->getIndex());

            if (!selectedTask.isEmpty())
            {
                auto window = std::make_shared<EditWindow>(selectedTask, ArhiveTasks, *Scroll);
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
        [this, &Scroll = Scroll, &tasks = ArhiveTasks]()
        {
            Scroll->onClickCallback(Scroll->getIndex());

            if (!selectedTask.isEmpty())
            {
                auto window = std::make_shared<InfoWindow>(selectedTask, *Scroll, tasks);
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
    ArchiveElemets.addElement(Scroll);
    ArhiveTasks.loadTasks();
    Scroll->setTasks(ArhiveTasks);
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