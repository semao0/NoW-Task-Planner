#ifndef CALENDAREWIDGET_H
#define CALENDAREWIDGET_H

#include "guiElement.h"
#include "guiManager.h"
#include <chrono>
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
    std::vector<std::string> dayNames{"Mon", "Tue", "Wed", "Thu", "Fri", "Sat", "Sun"};
    std::vector<std::string> monthNames{"January",
                                        "February",
                                        "March",
                                        "April",
                                        "May",
                                        "June",
                                        "July",
                                        "August",
                                        "September",
                                        "October",
                                        "November",
                                        "December"};
    std::vector<int> days;
    std::chrono::year_month_day currentDate;
    void updateCalendare();
    std::chrono::year_month_day getCurrentDate();
    void changeDate(const int count);
    guiManager elements;

public:
    void setDate(std::chrono::year_month_day Date);
    CalendareWidget(float x, float y, float width, float height);
    void draw(sf::RenderWindow& window) override;
    void handleEvent(const sf::Event& event) override;
    std::chrono::year_month_day getSelectedDate() const;
};
#endif