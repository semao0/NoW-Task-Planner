#include "InfoWindow.h"
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
#include <chrono>
#include <iomanip>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <type_traits>
InfoWindow::InfoWindow(Task& task) : window(sf::VideoMode(1000, 700), "NoW - Edit task", sf::Style::Titlebar | sf::Style::Close), selectedTask(task)
{
    auto namelabeltask = std::make_shared<Label>(400, 100, 100, 40, selectedTask.getName());
    InfoElemets.addElement(namelabeltask);
    auto namelabel = std::make_shared<Label>(100, 100, 100, 40, "Name:");
    InfoElemets.addElement(namelabel);

    auto desclabeltask = std::make_shared<Label>(400, 200, 100, 40, selectedTask.getDescription());
    InfoElemets.addElement(desclabeltask);
    auto desclabel = std::make_shared<Label>(100, 200, 100, 40, "Description:");
    InfoElemets.addElement(desclabel);

    std::ostringstream deadline;
    deadline << std::setw(2) << std::setfill('0') << static_cast<unsigned>(selectedTask.getDeadline().day()) << '-'
             << std::setw(2) << std::setfill('0') << static_cast<unsigned>(selectedTask.getDeadline().month()) << '-'
             << static_cast<int>(selectedTask.getDeadline().year());
    std::string deadlinestr = deadline.str();

    auto deadlinelabeltask = std::make_shared<Label>(400, 300, 100, 40, deadlinestr);
    InfoElemets.addElement(deadlinelabeltask);
    auto deadlinelabel = std::make_shared<Label>(100, 300, 100, 40, "Deadline:");
    InfoElemets.addElement(deadlinelabel);

    auto buttonSave =
        std::make_shared<Button>(810, 630, 170, 40, "           Back", [&window = window]() { window.close(); }, 20);
    InfoElemets.addElement(buttonSave);
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
