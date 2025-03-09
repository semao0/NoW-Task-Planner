#include "MainWindow.h"
#include "ArchiveWindow.h"
#include "CreateWindow.h"
#include "ScrollableList.h"
#include "InfoWindow.h"
#include "TaskManager.h"
#include "GUIManager.h"
#include "Button.h"
#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/VideoMode.hpp>
#include "EditWindow.h"
#include <memory>

MainWindow::MainWindow()
    : window(sf::VideoMode(1000, 700), "NoW", sf::Style::Titlebar | sf::Style::Close),
      dummyTask("Dummy",
                "No description",
                std::chrono::year_month_day{std::chrono::year(1970), std::chrono::month(1), std::chrono::day(1)},
                -1,
                false),
      selectedTask(&dummyTask)
{
    Scroll = std::make_shared<ScrollableList>(20, 20, 600, 600, 100, true, false);
    Scroll->onClickCallback = [this](int index)
    {
        auto& activeTask = tasks.getActiveTasks();
        if (!activeTask.empty() && index >= 0 && index < static_cast<int>(activeTask.size()))
        {
            selectedTask = &activeTask[index];
        }
        else
        {
            selectedTask = &dummyTask;
        }
    };
    Scroll->onCheckBoxToggle = [this](Task& t)
    {
        tasks.activatedOrArchivatedTask(t, t.isCompleted());
        tasks.saveTasks();
        removeSelection();
    };

    MainElemets.addElement(Scroll);

    createButton(810,
                 645,
                 170,
                 40,
                 "Info",
                 [this]()
                 {
                     Scroll->onClickCallback(Scroll->getIndex());

                     if (!selectedTask->isEmpty())
                     {
                         auto window = std::make_shared<InfoWindow>(*selectedTask, *Scroll, tasks);
                         window->run();
                     }
                     else
                     {
                         errorManager.showError("SelectedTask clear!");
                     }
                 });
    createButton(810,
                 70,
                 170,
                 40,
                 "Edit task",
                 [this]()
                 {
                     Scroll->onClickCallback(Scroll->getIndex());

                     if (!selectedTask->isEmpty())
                     {
                         auto window = std::make_shared<EditWindow>(*selectedTask, tasks, *Scroll);
                         window->run();
                     }
                     else
                     {
                         errorManager.showError("SelectedTask clear!");
                     }
                 });
    createButton(810,
                 15,
                 170,
                 40,
                 "Create new task",
                 [this]()
                 {
                     tasks.loadTasks();
                     Scroll->onClickCallback(Scroll->getIndex());
                     auto window = std::make_shared<CreateWindow>(tasks, *Scroll);
                     window->run();
                 });

    createButton(810,
                 350,
                 170,
                 40,
                 "Archive",
                 [this]()
                 {
                     auto window = std::make_shared<ArchiveWindow>(tasks, *Scroll);
                     window->run();
                     tasks.loadTasks();
                     Scroll->setTasks(tasks);
                 });

    createButton(810,
                 595,
                 170,
                 40,
                 "Delete task",
                 [this]()
                 {
                     Scroll->onClickCallback(Scroll->getIndex());

                     if (!selectedTask->isEmpty())
                     {
                         tasks.removeTask(*selectedTask);
                         tasks.saveTasks();
                         Scroll->setTasks(tasks);
                         removeSelection();
                     }
                     else
                     {
                         errorManager.showError("SelectedTask clear!");
                     }
                 });

    tasks.loadTasks();
    Scroll->setTasks(tasks);
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
            return;
        }
        MainElemets.handleEvent(event);
    }
}
void MainWindow::render()
{
    window.clear(sf::Color::White);
    MainElemets.draw(window);

    errorManager.draw(window);
    errorManager.update();

    window.display();
}

void MainWindow::createButton(
    float x, float y, float hight, float weight, const std::string& text, const std::function<void()> OnCLick)
{
    MainElemets.addElement(std::make_shared<Button>(x, y, hight, weight, text, OnCLick, 20));
}

void MainWindow::removeSelection()
{
    selectedTask = &dummyTask;
    Scroll->setSelectedIndex(-1);
}