#include "EditWindow.h"
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
EditWindow::EditWindow() : window(sf::VideoMode(1000, 700), "NoW -  task")
{
    auto nameinput = std::make_shared<TextInput>(400, 100, 450, 40);
    nameinput.setString()
    EditElemets.addElement(nameinput);
    auto namelabel = std::make_shared<Label>(100, 100, 100, 40, "Name:");
    EditElemets.addElement(namelabel);

    auto descinput = std::make_shared<TextInput>(400, 200, 450, 40);
    EditElemets.addElement(descinput);
    auto desclabel = std::make_shared<Label>(100, 200, 100, 40, "Description:");
    EditElemets.addElement(desclabel);

    auto calendarewidget = std::make_shared<CalendareWidget>(395, 300, 280, 100);
    EditElemets.addElement(calendarewidget);
    auto deadlinelabel = std::make_shared<Label>(100, 300, 100, 40, "Deadline:");
    EditElemets.addElement(deadlinelabel);

    auto button = std::make_shared<Button>(
        810,
        630,
        170,
        40,
        "           Save",
        [nameinput, descinput, calendarewidget, &tasks = tasks, &window = window, &Scroll = Scroll]() {},
        20);
    EditElemets.addElement(button);
}

void EditWindow::run()
{
    while (window.isOpen())
    {
        handleEvents();
        render();
    }
}
void EditWindow::handleEvents()
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            window.close();
        }
        CrhandleEvent(event);
    }
}
void CreateWindow::render()
{
    window.clear(sf::Color::White);
    CreateElemets.draw(window);
    window.display();
}
