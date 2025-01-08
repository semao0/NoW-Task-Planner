#ifndef CALENDAREWIDGET_H
#define CALENDAREWIDGET_H

#include "guiElement.h"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Window.hpp>
class CalendareWidget : public guiElement
{
private:
sf::Vector2f position, size;
int selectedDay;
sf::RectangleShape frame;
sf::Text title;
sf::Font font;
std::vector<std::string> nameMonth;
std::vector<std::string> nameDays;
std::vector<int> days;

public:
CalendareWidget(float x, float y, float width, float height);
void draw(sf::RenderWindow& window);
};
#endif