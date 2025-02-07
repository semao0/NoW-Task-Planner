#ifndef CREATEWINDOW_H
#define CREATEWINDOW_H
#include "guiManager.h"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>
#include "TaskManager.h"
#include "ScrollableList.h"

class CreateWindow
{
private:
    guiManager CreateElemets;
    sf::RenderWindow window;

public:
    CreateWindow(TaskManager& tasks, ScrollableList& Scroll, bool isMain, Task* MainTask = nullptr);
    void run();

private:
    void render();
    void handleEvents();
};
#endif