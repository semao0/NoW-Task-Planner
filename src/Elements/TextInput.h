#pragma once

#include "FontManager.h"
#include "GUIElement.h"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Mouse.hpp>
#include <cctype>
#include <nlohmann/json.hpp>
#include <string>
#include "Label.h"
#include <iostream>
class TextInput : public GUIElement
{
private:
    sf::RectangleShape box;
    sf::Text text;
    bool isActive;
    float viewOffset;
    int maxLenghtText;
    Label labelError;

public:
    TextInput(float x, float y, float width, float height, int maxLenghtText = 20)
        : isActive(false), viewOffset(0), maxLenghtText(maxLenghtText), labelError(x, y + height + 5, 100, 20, "", 16)
    {
        box.setPosition(x, y);
        box.setSize(sf::Vector2f(width, height));
        box.setFillColor(sf::Color::White);
        box.setOutlineColor(sf::Color::Black);
        box.setOutlineThickness(2);

        text.setFont(FontManager::getFont());
        text.setFillColor(sf::Color::Black);
        text.setCharacterSize(20);
        text.setPosition(x + 5, y + 5);
        validate();
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
        labelError.draw(window);
    }
    void handleEvent(const sf::Event& event) override
    {
        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
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
                        viewOffset -= FontManager::getFont().getGlyph(str[str.getSize() - 1], text.getCharacterSize(), false).advance;
                    }
                }
            }
            else if (event.text.unicode < 128)
            {
                text.setString(text.getString() + static_cast<char>(event.text.unicode));
                auto str = text.getString();

                float textWight = text.getLocalBounds().width;

                if (textWight > box.getSize().x - 15)
                {
                    viewOffset += FontManager::getFont().getGlyph(str[str.getSize() - 1], text.getCharacterSize(), false).advance;
                }
            }
            validate();
        }
    }
    bool isTooLong(size_t maxLenght)
    {
        return text.getString().getSize() > maxLenght;
    }

    bool isValid()
    {
        std::string str = text.getString();
        for (char c : str)
        {
            if (!std::isalnum(c) && c != ' ')
            {
                return false;
            }
        }
        return true;
    }

    bool isEmpty()
    {
        return text.getString().isEmpty();
    }

    void validate()
    {
        if (isEmpty())
        {
            box.setOutlineColor(sf::Color::Red);
            labelError.setText("Empty");
            labelError.setTextColor(sf::Color::Red);
        }
        else if (!isValid())
        {
            box.setOutlineColor(sf::Color::Red);
            labelError.setText("Not valid symbol: A-z, 0-9");
            labelError.setTextColor(sf::Color::Red);
        }
        else if (isTooLong(maxLenghtText))
        {
            box.setOutlineColor(sf::Color(255, 165, 0));
            labelError.setText("Too long. Max:" + std::to_string(maxLenghtText));
            labelError.setTextColor(sf::Color(255, 165, 0));
        }
        else
        {
            box.setOutlineColor(sf::Color::Black);
            labelError.setText("");
        }
    }

    bool checkBeforeCreate()
    {
        if (isEmpty())
        {
            std::cout << "Ошибка: Пустое поле!" << std::endl;
            return 0;
        }
        if (!isValid())
        {
            std::cout << "Ошибка: Некорректные символы!" << std::endl;
            return 0;
        }
        if (isTooLong(maxLenghtText))
        {
            std::cout << "Ошибка: Текст слишком длинный!" << std::endl;
            return 0;
        }
        return 1;
    }

    std::string getText() const
    {
        return text.getString();
    }

    void setText(const std::string& str)
    {
        text.setString(str);
        float textWhight = text.getLocalBounds().width;
        viewOffset = std::max(0.0f, textWhight - (box.getSize().x - 10));
        validate();
    }
};