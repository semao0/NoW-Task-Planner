#pragma once
#include "GUIManager.h"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>
#include "TaskManager.h"
#include "ScrollableList.h"
#include "TextInput.h"

class EditWindow
{
private:
    GUIManager EditElemets;
    sf::RenderWindow window;

public:
    EditWindow(Task& task, TaskManager& tasks, ScrollableList& Scroll, Task* MainTask = nullptr);
    void run();

private:
    void render();
    void handleEvents();
    Task& selectedTask;
    void createLabel(int x, int y, int weight, int height, const std::string& text);

    std::shared_ptr<TextInput>
    createTextInput(int x, int y, int weight, int height, int maxChars, const std::string& text);
};