#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "guiManager.h"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>

class MainWindow
{
private:
    guiManager MainElemets;
    sf::RenderWindow window;

public:
    MainWindow();
    void run();

private:
    void render();
    void handleEvents();
};
#endif