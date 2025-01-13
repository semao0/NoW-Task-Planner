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
#include <memory>

MainWindow::MainWindow() : window(sf::VideoMode(1000, 700), "NoW")
{
    Scroll = std::make_shared<ScrollableList>(20, 20, 600, 600, 100);
    auto button = std::make_shared<Button>(
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
    MainElemets.addElement(button);
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
