#pragma once
#include "GUIElement.h"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Clock.hpp>

class ErrorManager : GUIElement
{
private:
    sf::Text errorMessage;
    sf::Clock errorTimer;
    bool showErrorFlag;

public:
ErrorManager();
void showError(const std::string& massage);
void draw(sf::RenderWindow& window) override;
void handleEvent(const sf::Event& event) override;
void update();
};