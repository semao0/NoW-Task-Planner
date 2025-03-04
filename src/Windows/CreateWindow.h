#pragma once
#include "GUIManager.h"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>
#include "TaskManager.h"
#include "ScrollableList.h"

class CreateWindow
{
private:
    GUIManager CreateElemets;
    sf::RenderWindow window;

public:
    CreateWindow(TaskManager& tasks, ScrollableList& Scroll, Task* MainTask = nullptr);
    void run();

private:
    void render();
    void handleEvents();
    bool isMain;
};