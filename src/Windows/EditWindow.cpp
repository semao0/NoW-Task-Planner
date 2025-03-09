#include "EditWindow.h"
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
EditWindow::EditWindow(Task& task, TaskManager& tasks, ScrollableList& Scroll, Task* MainTask)
    : window(sf::VideoMode(1000, 700), "NoW - Edit task", sf::Style::Titlebar | sf::Style::Close), selectedTask(task)
{
    auto nameinput = createTextInput(400, 75, 450, 40, 35, selectedTask.getName());

    createLabel(100, 75, 100, 40, "Name:");

    auto descinput = 
    createTextInput(400, 175, 450, 40, 100, selectedTask.getDescription());

    createLabel(100, 175, 100, 40, "Description:");

    auto calendarwidget = std::make_shared<CalendarWidget>(395, 275, 280, 100);
    EditElemets.addElement(calendarwidget);
    calendarwidget->setDate(selectedTask.getDeadline());

    createLabel(100, 275, 100, 40, "Deadline:");

    auto buttonSave = std::make_shared<Button>(
        810,
        630,
        170,
        40,
        "Save",
        [&task, nameinput, descinput, calendarwidget, this, &tasks, &Scroll, MainTask]()
        {
            if (!nameinput->checkBeforeCreate() || !descinput->checkBeforeCreate())
            {
                return;
            }
            task.setDeadLine(calendarwidget->getSelectedDate());
            task.setName(nameinput->getText());
            task.setDescription(descinput->getText());
            window.close();
            if(MainTask != nullptr)
            {
                MainTask->updateSubTask(task);
                tasks.updateTask(*MainTask);
                tasks.saveTasks();
                return;
            }
            else
            {
                tasks.updateTask(task);
                tasks.saveTasks();
            }
            Scroll.setTasks(tasks);
        },
        20);
    EditElemets.addElement(buttonSave);
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
        EditElemets.handleEvent(event);
    }
}
void EditWindow::render()
{
    window.clear(sf::Color::White);
    EditElemets.draw(window);
    window.display();
}

void EditWindow::createLabel(int x, int y, int weight, int height, const std::string& text)
{
    EditElemets.addElement(std::make_shared<Label>(x, y, weight, height, text));
}

std::shared_ptr<TextInput> EditWindow::createTextInput(int x, int y, int weight, int height, int maxChars, const std::string& text)
{
    auto input = std::make_shared<TextInput>(x, y, weight, height, maxChars);
    input->setText(text);
    EditElemets.addElement(input);
    return input;
}