#include "CalendarWidget.h"
#include "Button.h"
#include "FontManager.h"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Window/Window.hpp>
#include <bits/chrono.h>
#include <chrono>
#include <ctime>
#include <memory>
#include <sstream>
#include <string>
#include <iostream>

CalendarWidget::CalendarWidget(float x, float y, float width, float height)
    : position(x, y), size(width, height), selectedDay(0)
{
    currentDate = getCurrentDate();
    updateCalendar();

    frame.setPosition(position);
    frame.setFillColor(sf::Color::White);
    frame.setOutlineColor(sf::Color::Black);
    frame.setOutlineThickness(2);

    title.setFont(FontManager::getFont());
    title.setString(monthNames[static_cast<unsigned>(currentDate.month()) - 1] + " " +
                    std::to_string(static_cast<int>(currentDate.year())));
    title.setCharacterSize(20);
    title.setPosition(position.x + width / 3.5, position.y + 5);
    title.setFillColor(sf::Color::Black);

    auto buttonnext =
        std::make_unique<Button>(position.x + 5, position.y + 5, 30, 30, "<", [this]() { changeDate(-1); }, 18);
    elements.addElement(std::move(buttonnext));
    auto buttonprev =
        std::make_unique<Button>(position.x + width - 35, position.y + 5, 30, 30, ">", [this]() { changeDate(1); }, 18);
    elements.addElement(std::move(buttonprev));
}

void CalendarWidget::drawWeekDays(sf::RenderWindow& window)
{
    for (int i = 0; i < dayNames.size(); i++)
    {
        sf::Text DayText;
        setupText(DayText, dayNames[i], position.x + 10 + i * 40, position.y + 40);
        window.draw(DayText);
    }
}

void CalendarWidget::setupText(sf::Text& text, const std::string& str, float x, float y)
{
    text.setFont(FontManager::getFont());
    text.setFillColor(sf::Color::Black);
    text.setCharacterSize(16);
    text.setString(str);
    text.setPosition(x, y);
}

void CalendarWidget::draw(sf::RenderWindow& window)
{
    selectedDay = static_cast<unsigned>(currentDate.day());
    window.draw(frame);
    window.draw(title);
    drawWeekDays(window);

    for (int i = 0; i < days.size(); i++)
    {
        if (days[i] == 0)
        {
            continue;
        }
        sf::Text dayMonth;
        dayMonth.setFont(FontManager::getFont());
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

void CalendarWidget::handleEvent(const sf::Event& event)
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
                currentDate = std::chrono::year_month_day{
                    currentDate.year(), currentDate.month(), std::chrono::day{unsigned(days[i])}};
                std::cout << days[i] << "-" << static_cast<unsigned>(currentDate.month()) << "-"
                          << static_cast<int>(currentDate.year()) << std::endl;
            }
        }
    }
    elements.handleEvent(event);
}

void CalendarWidget::updateCalendar()
{
    std::vector<int> daysInMonth{31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if ((static_cast<int>(currentDate.year()) % 4 == 0 && (static_cast<int>(currentDate.year()) % 100 != 0) ||
         (static_cast<int>(currentDate.year())) % 400 == 0))
    {
        daysInMonth[1] = 29;
    }

    std::chrono::year_month_day firstDay{currentDate.year(), currentDate.month(), std::chrono::day{1}};
    std::chrono::sys_days sysDay = std::chrono::sys_days{firstDay};
    int startday = (std::chrono::weekday{sysDay}.c_encoding() + 6) % 7 + 1;

    days.clear();
    days.resize(startday - 1, 0);

    for (int i = 1; i <= daysInMonth[static_cast<unsigned>(currentDate.month()) - 1]; i++)
    {
        days.push_back(i);
    }
    std::ostringstream oss;
    oss << monthNames[static_cast<unsigned>(currentDate.month()) - 1] << " " << static_cast<int>(currentDate.year());
    title.setString(oss.str());
}

std::chrono::year_month_day CalendarWidget::getCurrentDate()
{
    auto now = std::chrono::system_clock::now();

    std::time_t now_sec = std::chrono::system_clock::to_time_t(now);
    std::tm* time = std::localtime(&now_sec);
    return std::chrono::year_month_day{
        std::chrono::year(time->tm_year + 1900), std::chrono::month(time->tm_mon + 1), std::chrono::day(time->tm_mday)};
}

void CalendarWidget::changeDate(const int count)
{
    auto newdate = std::chrono::year_month_day{currentDate} + std::chrono::months{count};
    if (newdate.ok())
    {
        currentDate = newdate;
    }
    else
    {
        currentDate = std::chrono::year_month_day{newdate.year(), newdate.month(), std::chrono::day{1}};
    }
    updateCalendar();
}

std::chrono::year_month_day CalendarWidget::getSelectedDate() const
{
    return currentDate;
}

void CalendarWidget::setDate(const std::chrono::year_month_day Date)
{
    currentDate = std::chrono::year_month_day{Date};
    updateCalendar();
}