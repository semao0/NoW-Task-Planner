#include "CreateWindow.h"
#include "CalendarWidget.h"
#include "ScrollableList.h"
#include "TaskManager.h"
#include "Label.h"
#include "GUIManager.h"
#include "Button.h"
#include "TextInput.h"
#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <memory>

CreateWindow::CreateWindow(TaskManager& tasks, ScrollableList& Scroll, Task* MainTask)
    : window(sf::VideoMode(1000, 700), "NoW - Create task", sf::Style::Titlebar | sf::Style::Close)
{
    if (MainTask == nullptr)
    {
        isMain = true;
    }
    else
    {
        isMain = false;
    }
    auto nameinput = std::make_shared<TextInput>(400, 100, 450, 35, 35);
    CreateElemets.addElement(nameinput);
    auto namelabel = std::make_shared<Label>(100, 100, 100, 40, "Name:");
    CreateElemets.addElement(namelabel);

    auto descinput = std::make_shared<TextInput>(400, 200, 450, 35, 100);
    CreateElemets.addElement(descinput);
    auto desclabel = std::make_shared<Label>(100, 200, 100, 40, "Description:");
    CreateElemets.addElement(desclabel);

    auto calendarwidget = std::make_shared<CalendarWidget>(395, 300, 280, 100);
    CreateElemets.addElement(calendarwidget);
    auto deadlinelabel = std::make_shared<Label>(100, 300, 100, 40, "Deadline:");
    CreateElemets.addElement(deadlinelabel);

    auto button = std::make_shared<Button>(
        810,
        630,
        170,
        40,
        "Create",
        [nameinput, descinput, calendarwidget, &tasks, &window = window, &Scroll = Scroll, this, MainTask]()
        {
            if (!nameinput->checkBeforeCreate() || !descinput->checkBeforeCreate())
            {
                return;
            }
            Task newtask{nameinput->getText(),
                         descinput->getText(),
                         calendarwidget->getSelectedDate(),
                         Task::generateUniqueId()};
            if (isMain)
            {
                tasks.addTask(newtask);
                Scroll.setTasks(tasks);
            }
            else
            {
                MainTask->addSubtasks(newtask);
                tasks.updateTask(*MainTask);
            }
            window.close();
            tasks.saveTasks();
            tasks.loadTasks();
        },
        20);
    CreateElemets.addElement(std::move(button));
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