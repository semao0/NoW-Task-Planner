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
    TaskManager ArhiveTasks;
    std::shared_ptr<ScrollableList> Scroll;
    Task& selectedTask;

public:
ArchiveWindow();
    void run();

private:
    void render();
    void handleEvents();
    Task dummyTask;
};
#endif