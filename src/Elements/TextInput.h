#ifndef TEXTINPUT_H
#define TEXTINPUT_H

#include "guiElement.h"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/Window/Event.hpp>
#include <chrono>
class TextInput : public guiElement
{
private:
    sf::RectangleShape box;
    sf::Font font;
    sf::Text text;
    bool isActive;
    float viewOffset;

public:
    TextInput(float x, float y, float width, float height) : isActive(false), viewOffset(0)
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
        text.setCharacterSize(20);
        text.setPosition(x + 5, y + 5);
    }
    void draw(sf::RenderWindow& window) override
    {
        window.draw(box);

        sf::RenderTexture textureForText;
        textureForText.create(box.getSize().x, box.getSize().y);
        textureForText.clear(sf::Color::Transparent);

        sf::Text visibleText = text;
        visibleText.setPosition(5 - viewOffset, 5);
        textureForText.draw(visibleText);
        textureForText.display();

        sf::Sprite textSprite(textureForText.getTexture());
        textSprite.setPosition(box.getPosition());
        window.draw(textSprite);
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

                    if (viewOffset > 0)
                    {
                        viewOffset -= font.getGlyph(str[str.getSize() - 1], text.getCharacterSize(), false).advance;
                    }
                }
            }
            else if (event.text.unicode < 128)
            {
                text.setString(text.getString() + static_cast<char>(event.text.unicode));
                auto str = text.getString();

                float textWight = text.getLocalBounds().width;

                if (textWight > box.getSize().x - 10)
                {
                    viewOffset += font.getGlyph(str[str.getSize() - 1], text.getCharacterSize(), false).advance;
                }
            }
        }
    }
    std::string getText() const
    {
        return text.getString();
    }

    void setText(const std::string str)
    {
        text.setString(str);
        float textWhight = text.getLocalBounds().width;
        viewOffset = std::max(0.0f, textWhight -(box.getSize().x- 10));
    }
};
#endif