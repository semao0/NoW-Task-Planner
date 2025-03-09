#include "ErrorManager.h"
#include "FontManager.h"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

ErrorManager::ErrorManager()
{
    errorMessage.setFont(FontManager::getFont());
    errorMessage.setCharacterSize(20);
    errorMessage.setFillColor(sf::Color::Red);
    errorMessage.setPosition(20, 650);
}

void ErrorManager::showError(const std::string& message)
{
    errorMessage.setString(message);
    showErrorFlag = true;
    errorTimer.restart();
}

void ErrorManager::draw(sf::RenderWindow& window)
{
    if(showErrorFlag)
    {
        window.draw(errorMessage);
    }
}

void ErrorManager::update()
{
    if(showErrorFlag && errorTimer.getElapsedTime().asSeconds() > 3)
    {
        showErrorFlag = false;
    }
}
void ErrorManager::handleEvent(const sf::Event& event) {};