#ifndef CREATEWINDOW_H
#define CREATEWINDOW_H
#include "guiManager.h"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>

class CreateWindow
{
private:
    guiManager CreateElemets;
    sf::RenderWindow window;

public:
    CreateWindow();
    void run();

private:
    void render();
    void handleEvents();
};
#endif