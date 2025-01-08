#ifndef GUIMANAGER_H
#define GUIMANAGER_H

#include "guiElement.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <vector>
#include <memory>
class guiManager : public guiElement
{
private:
    std::vector<std::shared_ptr<guiElement>> elements;

public:
    void addElement(const std::shared_ptr<guiElement>& element)
    {
        elements.push_back(element);
    }
    void handleEvent(const sf::Event& event) override
    {
        for (auto& element : elements)
        {
            element->handleEvent(event);
        }
    }
    void draw(sf::RenderWindow& window) override
    {
        for (auto& element : elements)
        {
            element->draw(window);
        }
    }
};

#endif