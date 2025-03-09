#pragma once
#include <SFML/Graphics/Font.hpp>
#include <stdexcept>

class FontManager
{
private:
    static sf::Font font;
    static bool isLoaded;

public:
    static const sf::Font& getFont()
    {
        if(!isLoaded)
        {
            if(!font.loadFromFile("assets/fonts/Arial.ttf"))
            {
                throw std::runtime_error("Failed to load font resources/Arial.ttf!");
            }
            isLoaded = true;
        }
        return font;
    }
};