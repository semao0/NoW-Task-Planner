#pragma once
#include "ErrorManager.h"
#include "GUIManager.h"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>
#include <memory>
#include <vector>
#include "TaskManager.h"
#include "ScrollableList.h"

class InfoWindow
{
private:
    GUIManager InfoElemets;
    sf::RenderWindow window;

public:
    InfoWindow(Task& task, ScrollableList& Scroll, TaskManager& tasks, bool IsSubTask = false);
    void run();

private:
    void render();
    void handleEvents();
    Task* selectedTask;
    Task* selectedSubTask;
    std::shared_ptr<ScrollableList> ScrollInfo;
    Task dummyTask;
    std::vector<Task> subtasks;
    ErrorManager errorManager;
    void createLabel(int x, int y, int weight, int height, const std::string& text, bool wrap = false);
    void createButton(
        float x, float y, float hight, float weight, const std::string& text, const std::function<void()> OnCLick);
    void removeSelection();
};