#ifndef LABEL_H
#define LABEL_H

#include "guiElement.h"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
class Label : public guiElement
{
private:
    sf::RectangleShape box;
    sf::Font font;
    sf::Text text;

public:
    Label(float x, float y, float width, float height, std::string Text)
    {
        box.setPosition(x, y);
        box.setSize(sf::Vector2f(width, height));
        box.setFillColor(sf::Color::White);
        if (!font.loadFromFile("resources/Arial.ttf"))
        {
            throw std::runtime_error("Не удалось загрузить шрифт resources/Arial.ttf");
        }
        text.setFont(font);
        text.setFillColor(sf::Color::Black);
        text.setCharacterSize(24);
        text.setPosition(x + 5, y + 5);
        text.setString(Text);
    }
    void draw(sf::RenderWindow& window) override
    {
        window.draw(box);
        window.draw(text);
    }
    void handleEvent(const sf::Event& event) override {}
};
#endif