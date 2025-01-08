#ifndef GUIELEMENT_H
#define GUIELEMENT_H
#include <SFML/Graphics.hpp>

class guiElement
{
public:
    virtual void draw(sf::RenderWindow& window) = 0;
    virtual void handleEvent(const sf::Event& event) = 0;
    virtual ~guiElement() = default;
};
#endif