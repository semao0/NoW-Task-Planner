#include "MainWindow.h"
#include "CreateWindow.h"
#include "ScrollableList.h"
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

MainWindow::MainWindow() : window(sf::VideoMode(1000, 700), "NoW", sf::Style::Titlebar | sf::Style::Close)
{
    Scroll = std::make_shared<ScrollableList>(20, 20, 600, 600, 100);
    Scroll->onClickCallback = [this](int index) { selectedTask = tasks.getTasks()[index]; };
    auto buttonCreate = std::make_shared<Button>(
        810,
        15,
        170,
        40,
        "Create new task",
        [this, &Scroll = Scroll]()
        {
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
            if (!selectedTask.isEmpty())
            {
                auto window = std::make_shared<EditWindow>(selectedTask);
                window->run();
            }
            else
            {
                std::cout << "SelectedTasks clear!" << std::endl;
            }
        },
        20);
    MainElemets.addElement(buttonEdit);
    MainElemets.addElement(buttonCreate);
    MainElemets.addElement(Scroll);
    tasks.loadTasks();
    Scroll->setTasks(tasks);
    tasks.saveTasks();
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
