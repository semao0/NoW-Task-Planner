#include "CalendareWidget.h"
#include "Button.h"
#include "guiElement.h"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Window/Window.hpp>
#include <chrono>
#include <cstddef>
#include <ctime>
#include <memory>
#include <string>
#include <iostream>

CalendareWidget::CalendareWidget(float x, float y, float width, float height)
    : position(x, y), size(width, height), selectedDay(0)
{
    currentDate = getCurrentDate();
    updateCalendare();

    frame.setPosition(position);
    frame.setFillColor(sf::Color::White);
    frame.setOutlineColor(sf::Color::Black);
    frame.setOutlineThickness(2);

    if (!font.loadFromFile("resources/Arial.ttf"))
    {
        throw std::runtime_error("Не удалось загрузить шрифт resources/Arial.ttf");
    }

    title.setFont(font);
    title.setString(monthNames[currentDate.month - 1] + " " + std::to_string(currentDate.year));
    title.setCharacterSize(20);
    title.setPosition(position.x + width / 3, position.y + 5);
    title.setFillColor(sf::Color::Black);

    auto buttonnext =
        std::make_shared<Button>(position.x + 5, position.y + 5, 30, 30, "<", [this]() { changeDate(-1); }, 18);
    elements.addElement(buttonnext);
    auto buttonprev =
        std::make_shared<Button>(position.x + width - 35, position.y + 5, 30, 30, ">", [this]() { changeDate(1); }, 18);
    elements.addElement(buttonprev);
}

void CalendareWidget::draw(sf::RenderWindow& window)
{
    window.draw(frame);
    window.draw(title);
    for (int i = 0; i < dayNames.size(); i++)
    {
        sf::Text dayText;
        dayText.setFont(font);
        dayText.setFillColor(sf::Color::Black);
        dayText.setCharacterSize(16);
        dayText.setString(dayNames[i]);
        dayText.setPosition(position.x + 10 + i * 40, position.y + 40);
        window.draw(dayText);
    }

    for (int i = 0; i < days.size(); i++)
    {
        if (days[i] == 0)
        {
            continue;
        }
        sf::Text dayMonth;
        dayMonth.setFont(font);
        dayMonth.setString(std::to_string(days[i]));
        dayMonth.setFillColor(sf::Color::Black);
        dayMonth.setCharacterSize(16);

        float x = position.x + (i % 7) * 40 + 10;
        float y = position.y + 40 + (i / 7) * 30 + 30;

        dayMonth.setPosition(x, y);

        if (days[i] == selectedDay)
        {
            sf::RectangleShape highlight(sf::Vector2f(30, 30));
            highlight.setOutlineColor(sf::Color::Black);
            highlight.setOutlineThickness(2);
            highlight.setPosition(x - 5, y - 5);
            window.draw(highlight);
        }
        window.draw(dayMonth);
    }
    elements.draw(window);
}

void CalendareWidget::handleEvent(const sf::Event& event)
{
    if (event.type == sf::Event::MouseButtonPressed)
    {
        sf::Vector2f MousePos(event.mouseButton.x, event.mouseButton.y);
        for (int i = 0; i < days.size(); i++)
        {
            float x = position.x + (i % 7) * 40 + 10;
            float y = position.y + 40 + (i / 7) * 30 + 30;
            if (MousePos.x > x && MousePos.x < x + 30 && MousePos.y > y && MousePos.y < y + 30 && days[i] != 0)
            {
                selectedDay = days[i];
                std::cout << days[i] << "-" << currentDate.month << "-" << currentDate.year << std::endl;
            }
        }
    }
    elements.handleEvent(event);
}

void CalendareWidget::updateCalendare()
{
    std::vector<int> daysInMonth{31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if ((currentDate.year % 4 == 0 && currentDate.year % 100 != 0) || currentDate.year % 400 == 0)
    {
        daysInMonth[1] = 29;
    }

    std::tm firstday = {};
    firstday.tm_mday = 1;
    firstday.tm_year = currentDate.year - 1900;
    firstday.tm_mon = currentDate.month - 1;
    std::mktime(&firstday);

    int startday = firstday.tm_wday;

    if (startday == 0)
    {
        startday = 7;
    }

    days.clear();
    days.resize(startday - 1, 0);

    for (int i = 1; i <= daysInMonth[currentDate.month - 1]; i++)
    {
        days.push_back(i);
    }
    title.setString(monthNames[currentDate.month - 1] + " " + std::to_string(currentDate.year));
}

CalendareWidget::Date CalendareWidget::getCurrentDate()
{
    auto now = std::chrono::system_clock::now();

    std::time_t now_sec = std::chrono::system_clock::to_time_t(now);
    std::tm* time = std::localtime(&now_sec);
    return {time->tm_mday, time->tm_mon + 1, time->tm_year + 1900};
}

void CalendareWidget::changeDate(const int count)
{
    currentDate.month += count;

    if (currentDate.month > 12)
    {
        currentDate.month = 1;
        currentDate.year++;
    }

    if (currentDate.month <= 0)
    {
        currentDate.month = 11;
        currentDate.year--;
    }

    updateCalendare();
}