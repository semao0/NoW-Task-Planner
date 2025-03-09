#pragma once
#include "ErrorManager.h"
#include "ScrollableList.h"
#include "GUIManager.h"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>
#include <memory>
#include <nlohmann/detail/output/serializer.hpp>
#include "TaskManager.h"

class ArchiveWindow
{
private:
    GUIManager ArchiveElemets;
    sf::RenderWindow window;
    TaskManager& tasks;
    std::shared_ptr<ScrollableList> ScrollArchive;
    Task* selectedTaskArc;

public:
    ArchiveWindow(TaskManager& tasks, ScrollableList& Scroll);
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