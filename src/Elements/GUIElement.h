#pragma once
#include <SFML/Graphics.hpp>

class GUIElement
{
public:
    virtual void draw(sf::RenderWindow& window) = 0;
    virtual void handleEvent(const sf::Event& event) = 0;
    virtual ~GUIElement() = default;
    GUIElement& operator=(const GUIElement&) = delete;
};