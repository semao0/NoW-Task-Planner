#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "ScrollableList.h"
#include "guiManager.h"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>
#include "TaskManager.h"

class MainWindow
{
private:
    guiManager MainElemets;
    sf::RenderWindow window;
    TaskManager tasks;
    std::shared_ptr<ScrollableList> Scroll;
    Task selectedTask;

public:
    MainWindow();
    void run();

private:
    void render();
    void handleEvents();
};
#endif