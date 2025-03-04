#pragma once

#include <string>
#include <vector>
#include <memory>
#include <SFML/Graphics/RenderWindow.hpp>
#include "GUIElement.h"
class GUIManager : public GUIElement
{
private:
    std::vector<std::shared_ptr<GUIElement>> elements;

public:
    void addElement(std::shared_ptr<GUIElement> element)
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
    void clear ()
    {
        elements.clear();
    }
    ~GUIManager() override = default;
};