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
#include <regex>
class TextInput : public GUIElement
{
private:
    sf::RectangleShape box;
    sf::Text text;
    bool isActive;
    float viewOffset;
    int maxLengthText;
    Label labelError;
    const float PADDING = 5;
    const float SCROLL_THRESHOLD = 15;

public:
    TextInput(float x, float y, float width, float height, int maxLengthText = 20)
        : isActive(false), viewOffset(0), maxLengthText(maxLengthText), labelError(x, y + height + 5, 100, 20, "", 16)
    {
        box.setPosition(x, y);
        box.setSize(sf::Vector2f(width, height));
        box.setFillColor(sf::Color::White);
        box.setOutlineColor(sf::Color::Black);
        box.setOutlineThickness(2);

        text.setFont(FontManager::getFont());
        text.setFillColor(sf::Color::Black);
        text.setCharacterSize(20);
        text.setPosition(x + PADDING, y + PADDING);
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
                        viewOffset -= FontManager::getFont()
                                          .getGlyph(str[str.getSize() - 1], text.getCharacterSize(), false)
                                          .advance;
                    }
                }
            }
            else if (event.text.unicode < 128)
            {
                text.setString(text.getString() + static_cast<char>(event.text.unicode));
                auto str = text.getString();

                float textWight = text.getLocalBounds().width;

                if (textWight > box.getSize().x - SCROLL_THRESHOLD)
                {
                    viewOffset +=
                        FontManager::getFont().getGlyph(str[str.getSize() - 1], text.getCharacterSize(), false).advance;
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
        std::regex pattern("^[A-Za-z0-9_@., ]+$");
        std::string str = text.getString().toAnsiString();
        return std::regex_match(str, pattern);
    }

    bool isEmpty()
    {
        return text.getString().isEmpty();
    }

    void validate()
    {
        if (isEmpty())
        {
            applyValidateError("Error: The field is empty!", sf::Color::Red);
        }
        else if (!isValid())
        {
            applyValidateError("Error: Invalid characters used!", sf::Color::Red);
        }
        else if (isTooLong(maxLengthText))
        {
            applyValidateError("Error: Text is too long! Max length: " + std::to_string(maxLengthText) + "!", sf::Color(255, 165, 0));
        }
        else
        {
            applyValidateError("", sf::Color::Black);
        }
    }

    void applyValidateError(const std::string massage, sf::Color color)
    {
        box.setOutlineColor(color);
        labelError.setText(massage);
        labelError.setTextColor(color);
    }

    bool checkBeforeCreate()
    {
        if (isEmpty())
        {
            std::cerr << "Error: The field is empty!" << std::endl;
            return false;
        }
        if (!isValid())
        {
            std::cerr << "Error: Invalid characters used!" << std::endl;
            return false;
        }
        if (isTooLong(maxLengthText))
        {
            std::cerr << "Error: Text is too long! Max length: " << maxLengthText << "!" << std::endl;
            return false;
        }
        return true;
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