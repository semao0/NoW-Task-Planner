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
    auto nameinput = createTextInput(400, 75, 450, 35, 35);
    
    createLabel(100, 75, 100, 40, "Name:");

    auto descinput = createTextInput(400, 175, 450, 35, 100);
    
    createLabel(100, 175, 100, 40, "Description:");

    auto calendarwidget = std::make_shared<CalendarWidget>(395, 275, 280, 100);
    CreateElemets.addElement(calendarwidget);
    
    createLabel(100, 275, 100, 40, "Deadline:");

    auto button = std::make_shared<Button>(
        810,
        630,
        170,
        40,
        "Create",
        [nameinput, descinput, calendarwidget, &tasks, &window = window, &Scroll, this, MainTask]()
        {
            if (!nameinput->checkBeforeCreate() || !descinput->checkBeforeCreate())
            {
                return;
            }
            Task newtask{nameinput->getText(),
                         descinput->getText(),
                         calendarwidget->getSelectedDate(),
                         Task::generateUniqueId()};
            if (MainTask == nullptr)
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

void CreateWindow::createLabel(int x, int y, int weight, int height, const std::string& text)
{
    CreateElemets.addElement(std::make_shared<Label>(x, y, weight, height, text));
}

std::shared_ptr<TextInput> CreateWindow::createTextInput(int x, int y, int weight, int height, int maxChars)
{
    auto input = std::make_shared<TextInput>(x, y, weight, height, maxChars);
    CreateElemets.addElement(input);
    return input;
}