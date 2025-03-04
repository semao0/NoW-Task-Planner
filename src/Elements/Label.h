#pragma once

#include "FontManager.h"
#include "GUIElement.h"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
class Label : public GUIElement
{
private:
    sf::RectangleShape box;
    sf::Text text;
    bool IsFrame;
    sf::Color textColor;
    int textSize;

public:
    Label(float x, float y, float width, float height, std::string Text, int textSize = 24, bool IsFrame = false)
        : IsFrame(IsFrame), textSize(textSize)
    {
        text.setFont(FontManager::getFont());
        text.setFillColor(sf::Color::Black);
        text.setCharacterSize(textSize);
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
    void setText(std::string str)
    {
        text.setString(str);
    }
    void setTextColor(sf::Color textColor)
    {
        text.setFillColor(textColor);
    }
    void wrapText()
    {
        std::string text = this->text.getString();
        std::string wrappedText;
        size_t lastSpace = std::string::npos;
        size_t lineLenght = 0;
        for (int i = 0; i < text.size(); i++)
        {
            char c = text[i];
            wrappedText += c;
            lineLenght++;
            if (c == ' ')
            {
                lastSpace = wrappedText.size() - 1;
            }
            if (lineLenght >= 40)
            {
                if (lastSpace != std::string::npos)
                {
                    wrappedText[lastSpace] = '\n';
                    lineLenght = wrappedText.size() - lastSpace - 1;
                    lastSpace = std::string::npos;
                }
                else
                {
                    wrappedText += '\n';
                    lineLenght = 0;
                }
            }
        }
        this->text.setString(wrappedText);
    }
};