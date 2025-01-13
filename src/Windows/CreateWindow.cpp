#include "CreateWindow.h"
#include "CalendareWidget.h"
#include "ScrollableList.h"
#include "TaskManager.h"
#include "Label.h"
#include "guiManager.h"
#include "Button.h"
#include "TextInput.h"
#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <iostream>
#include <memory>

CreateWindow::CreateWindow(TaskManager &tasks, ScrollableList& Scroll) : window(sf::VideoMode(1000, 700), "NoW - Create task")
{
    auto nameinput = std::make_shared<TextInput>(400, 100, 450, 40);
    CreateElemets.addElement(nameinput);
    auto namelabel = std::make_shared<Label>(100, 100, 100, 40, "Name:");
    CreateElemets.addElement(namelabel);

    auto descinput = std::make_shared<TextInput>(400, 200, 450, 40);
    CreateElemets.addElement(descinput);
    auto desclabel = std::make_shared<Label>(100, 200, 100, 40, "Description:");
    CreateElemets.addElement(desclabel);

    auto calendarewidget = std::make_shared<CalendareWidget>(395, 300, 280, 100);
    CreateElemets.addElement(calendarewidget);
    auto deadlinelabel = std::make_shared<Label>(100, 300, 100, 40, "Deadline:");
    CreateElemets.addElement(deadlinelabel);

    auto button =
        std::make_shared<Button>(810, 630, 170, 40, "        Create", [nameinput, descinput, calendarewidget, &tasks = tasks, &window = window, &Scroll = Scroll]() {
             Task newtask {nameinput->getText(), descinput->getText(), calendarewidget->getSelectedDate()};
             tasks.addTask(newtask);
             tasks.saveTasks();
             window.close();
             Scroll.setTasks(tasks);
             }, 20);
    CreateElemets.addElement(button);
}

void CreateWindow::run()
{
    while (window.isOpen())
    {
        handleEvents();
        render();
    }
}
void CreateWindow::handleEvents()
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            window.close();
        }
        CreateElemets.handleEvent(event);
    }
}
void CreateWindow::render()
{
    window.clear(sf::Color::White);
    CreateElemets.draw(window);
    window.display();
}
