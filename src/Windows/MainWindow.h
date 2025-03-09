#pragma once
#include "ErrorManager.h"
#include "ScrollableList.h"
#include "GUIManager.h"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Clock.hpp>
#include <memory>
#include "TaskManager.h"

class MainWindow
{
private:
    GUIManager MainElemets;
    sf::RenderWindow window;
    TaskManager tasks;
    std::shared_ptr<ScrollableList> Scroll;
    Task* selectedTask;

public:
    MainWindow();
    void run();

private:
    void render();
    void handleEvents();
    Task dummyTask;
    ErrorManager errorManager;
    void createButton(
        float x, float y, float hight, float weight, const std::string& text, const std::function<void()> OnCLick);

    void removeSelection();
};