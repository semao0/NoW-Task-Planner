#ifndef ARCHIVEWINDOW_H
#define ARCHIVEWINDOW_H
#include "ScrollableList.h"
#include "guiManager.h"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>
#include "TaskManager.h"

class ArchiveWindow
{
private:
    guiManager ArchiveElemets;
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
};
#endif