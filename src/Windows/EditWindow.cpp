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
#include <memory>
EditWindow::EditWindow(Task& task, TaskManager& tasks, ScrollableList& Scroll)
    : window(sf::VideoMode(1000, 700), "NoW - Edit task", sf::Style::Titlebar | sf::Style::Close), selectedTask(task)
{
    auto nameinput = std::make_shared<TextInput>(400, 100, 450, 40);
    nameinput->setText(selectedTask.getName());
    EditElemets.addElement(nameinput);
    auto namelabel = std::make_shared<Label>(100, 100, 100, 40, "Name:", false);
    EditElemets.addElement(namelabel);

    auto descinput = std::make_shared<TextInput>(400, 200, 450, 40);
    descinput->setText(selectedTask.getDescription());
    EditElemets.addElement(descinput);
    auto desclabel = std::make_shared<Label>(100, 200, 100, 40, "Description:", false);
    EditElemets.addElement(desclabel);

    auto calendarewidget = std::make_shared<CalendareWidget>(395, 300, 280, 100);
    EditElemets.addElement(calendarewidget);
    calendarewidget->setDate(selectedTask.getDeadline());
    auto deadlinelabel = std::make_shared<Label>(100, 300, 100, 40, "Deadline:", false);
    EditElemets.addElement(deadlinelabel);

    auto buttonSave = std::make_shared<Button>(
        810,
        630,
        170,
        40,
        "Save",
        [&task, nameinput, descinput, calendarewidget, this, &tasks, &Scroll]()
        {
            Task newtask(nameinput->getText(), descinput->getText(), calendarewidget->getSelectedDate(), task.getId());
            tasks.removeTask(task);
            tasks.addTask(newtask);
            tasks.clearTasks();
            tasks.saveTasks();
            window.close();
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
