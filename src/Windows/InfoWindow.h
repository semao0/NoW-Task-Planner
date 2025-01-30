#ifndef INFOWINDOW_H
#define INFOWINDOW_H
#include "guiManager.h"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>
#include "TaskManager.h"
#include "ScrollableList.h"

class InfoWindow
{
private:
    guiManager InfoElemets;
    sf::RenderWindow window;

public:
    InfoWindow(Task& task);
    void run();

private:
    void render();
    void handleEvents();
    Task &selectedTask;
};
#endif