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
    bool IsFrame;

public:
    Label(float x, float y, float width, float height, std::string Text, bool IsFrame = false) : IsFrame(IsFrame)
    {
        if (!font.loadFromFile("resources/Arial.ttf"))
        {
            throw std::runtime_error("Не удалось загрузить шрифт resources/Arial.ttf");
        }
        text.setFont(font);
        text.setFillColor(sf::Color::Black);
        text.setCharacterSize(24);
        text.setString(Text);
        box.setPosition(x, y);

        box.setSize(sf::Vector2f(text.getLocalBounds().width + 10, height));
        box.setFillColor(sf::Color::White);
        if (IsFrame && text.getString() != "")
        {
            box.setOutlineColor(sf::Color::Black);
            box.setOutlineThickness(2);
        }
        text.setPosition(x + 5, y + 5);
    }
    void draw(sf::RenderWindow& window) override
    {
        window.draw(box);
        window.draw(text);
    }
    void handleEvent(const sf::Event& event) override {}
};
#endif