#pragma once
#include "GUIManager.h"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>
#include "TaskManager.h"
#include "ScrollableList.h"

class EditWindow
{
private:
    GUIManager EditElemets;
    sf::RenderWindow window;

public:
    EditWindow(Task& task, TaskManager& tasks, ScrollableList& Scroll);
    void run();

private:
    void render();
    void handleEvents();
    Task& selectedTask;
};