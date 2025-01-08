#ifndef TEXTINPUT_H
#define TEXTINPUT_H

#include "guiElement.h"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
class TextInput : public guiElement
{
private:
    sf::RectangleShape box;
    sf::Font font;
    sf::Text text;
    bool isActive;

public:
    TextInput(float x, float y, float width, float height) : isActive(false)
    {
        box.setPosition(x, y);
        box.setSize(sf::Vector2f(width, height));
        box.setFillColor(sf::Color::White);
        box.setOutlineColor(sf::Color::Black);
        box.setOutlineThickness(2);
        if (!font.loadFromFile("resources/Arial.ttf"))
        {
            throw std::runtime_error("Не удалось загрузить шрифт resources/Arial.ttf");
        }
        text.setFont(font);
        text.setFillColor(sf::Color::Black);
        text.setCharacterSize(24);
        text.setPosition(x + 5, y + 5);
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
            isActive = box.getGlobalBounds().contains(mousePos);
        }
        if (isActive && event.type == sf::Event::TextEntered)
        {
            if (event.text.unicode == '\b')
            {
                if (!text.getString().isEmpty())
                {
                    auto str = text.getString();
                    str.erase(str.getSize() - 1);
                    text.setString(str);
                }
            }
            else if (event.text.unicode < 128)
            {
                text.setString(text.getString() + static_cast<char>(event.text.unicode));
            }
        }
    }
    std::string getText() const
    {
        return text.getString();
    }
};
#endif