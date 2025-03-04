#pragma once

#include "FontManager.h"
#include "GUIElement.h"
#include <SFML/Graphics/Font.hpp>
#include <functional>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
class CheckBox : public GUIElement
{
private:
    sf::RectangleShape box;
    bool Active;
    sf::Text text;
    std::function<void()> onClick;

public:
    CheckBox(float x, float y, float width, float height, bool Active, const std::function<void()> callback)
        : Active(Active), onClick(callback)
    {
        text.setFont(FontManager::getFont());
        text.setCharacterSize(24);
        box.setPosition(x, y);
        box.setSize(sf::Vector2f(width, height));
        box.setFillColor(sf::Color::White);
        box.setOutlineColor(sf::Color::Black);
        box.setOutlineThickness(2);
        updateText();
    }
    void draw(sf::RenderWindow& window) override
    {
        window.draw(box);
        window.draw(text);
    }
    void handleEvent(const sf::Event& event) override
    {
        if (event.type == sf::Event::MouseButtonPressed)
        {
            sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);
            if (box.getGlobalBounds().contains(mousePos))
            {
                onClick();
                Active = !Active;
                updateText();
            }
        }
    }
    void updateText()
    {
        if (Active)
        {
            text.setString("+");
            text.setFillColor(sf::Color::Green);
            float textWidth = FontManager::getFont().getGlyph('+', 24, false).advance;
            text.setPosition(box.getPosition().x + (box.getSize().x - textWidth) / 2, box.getPosition().y);
        }
        else
        {
            text.setString("-");
            text.setFillColor(sf::Color::Red);
            float textWidth = FontManager::getFont().getGlyph('-', 24, false).advance;
            text.setPosition(box.getPosition().x + (box.getSize().x - textWidth) / 2, box.getPosition().y);
        }
    }
};