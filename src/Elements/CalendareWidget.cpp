#include "CalendareWidget.h"
#include "guiElement.h"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Window.hpp>

CalendareWidget::CalendareWidget(float x, float y, float width, float height) : position (x, y), size(width, height), selectedDay(0) 
{
    frame.setPosition(position);
    frame.setFillColor(sf::Color::White);
    frame.setOutlineColor(sf::Color::Black);
    frame.setOutlineThickness(2);

    if (!font.loadFromFile("resources/Arial.ttf"))
    {
        throw std::runtime_error("Не удалось загрузить шрифт resources/Arial.ttf");
    }

    title.setFont(font);
    title.setString()
};

void CalendareWidget::draw(sf::RenderWindow& window)
{
    window.draw(frame);
}
