#pragma once
#include "GUIManager.h"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>
#include "TaskManager.h"
#include "ScrollableList.h"
#include "TextInput.h"

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
    void createLabel(int x, int y, int weight, int height, const std::string& text);

    std::shared_ptr<TextInput>
    createTextInput(int x, int y, int weight, int height, int maxChars);
};