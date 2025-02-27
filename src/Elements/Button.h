#ifndef BUTTON_H
#define BUTTON_H

#include <string>
#include <functional>
#include "guiElement.h"

class Button : public guiElement
{
private:
    sf::RectangleShape box;
    sf::Text label;
    sf::Font font;
    std::function<void()> onClick;

public:
    Button(float x,
           float y,
           float width,
           float height,
           const std::string& text,
           const std::function<void()> callback,
           int charsize)
        : onClick(callback)
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
        label.setFont(font);
        float textWidth = 0;
        for (char c : text)
        {
            textWidth += font.getGlyph(c, charsize, false).advance;
        }
        label.setString(text);
        label.setCharacterSize(charsize);
        label.setFillColor(sf::Color::Black);
        label.setPosition(x + (width - textWidth) / 2, y + 5);
    }
    void draw(sf::RenderWindow& window) override
    {
        window.draw(box);
        window.draw(label);
    }
    void handleEvent(const sf::Event& event) override
    {
        if (event.type == sf::Event::MouseButtonPressed)
        {
            sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);
            if (box.getGlobalBounds().contains(mousePos))
            {
                onClick();
            }
        }
    }
};
#endif