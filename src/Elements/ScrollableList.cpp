#include "ScrollableList.h"
#include "Task.h"
#include "TaskManager.h"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/PrimitiveType.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Mouse.hpp>

ScrollableList::ScrollableList(float x, float y, float width, float height, int itemHeight)
    : scrollOffset(0), itemHeight(itemHeight), position(x, y)
{
    backgraund.setPosition(position);
    backgraund.setSize(sf::Vector2f(width, height));
    backgraund.setFillColor(sf::Color::White);
    backgraund.setOutlineThickness(2);
    backgraund.setOutlineColor(sf::Color::Black);

    visibleItemCount = height / itemHeight;

    updateRenderedTasks();
    if (!font.loadFromFile("resources/Arial.ttf"))
    {
        throw std::runtime_error("Не удалось загрузить шрифт resources/Arial.ttf");
    }
}

void ScrollableList::setTasks(TaskManager& tasks)
{
    this->tasks = tasks;
    updateRenderedTasks();
}

void ScrollableList::setTasks(std::vector<Task> tasks)
{
    TaskManager subtasks;
    for(auto task : tasks)
    {
        subtasks.addTask(task);
    }
    this->tasks = subtasks;
    updateRenderedTasks();
}


void ScrollableList::updateRenderedTasks()
{
    renderedTasks.clear();
    for (int i = 0; i < visibleItemCount && (i + scrollOffset) < tasks.getCountTasks(); i++)
    {
        std::string name = tasks.getTasks()[i + scrollOffset].getName();

        if (font.getGlyph(name[0], 20, false).advance * name.size() > backgraund.getSize().x)
        {
            name = name.substr(0, backgraund.getSize().x / font.getGlyph('A', 20, false).advance) + "...";
        }

        sf::Text text(name, font, 20);
        text.setPosition(position.x + 10, position.y + i * itemHeight + 10);
        text.setFillColor(sf::Color::Black);
        renderedTasks.push_back(text);
    }
}

void ScrollableList::draw(sf::RenderWindow& window)
{

    window.draw(backgraund);
    for (const auto& text : renderedTasks)
    {
        window.draw(text);
    }

    for (size_t i = 0; i < renderedTasks.size() + 1; i++)
    {
        sf::RectangleShape line;
        line.setSize((sf::Vector2f(backgraund.getSize().x, 2)));
        line.setPosition(position.x, position.y + i * itemHeight);
        line.setFillColor(sf::Color::Black);
        if (i == 0)
        {
            line.setSize((sf::Vector2f(backgraund.getSize().x, 0)));
        }
        if (i == 0 && (selectedIndex == i + scrollOffset || selectedIndex + 1 == i + scrollOffset))
        {
            line.setSize((sf::Vector2f(backgraund.getSize().x, 1)));
        }
        else if (selectedIndex == i + scrollOffset || selectedIndex + 1 == i + scrollOffset)
        {
            line.setSize((sf::Vector2f(backgraund.getSize().x, 3)));
        }
        window.draw(line);
    }
}

void ScrollableList::handleEvent(const sf::Event& event)
{
    if (event.type == sf::Event::MouseWheelScrolled)
    {
        if (event.mouseWheelScroll.delta > 0 && scrollOffset > 0)
        {
            --scrollOffset;
        }
        else if (event.mouseWheelScroll.delta < 0 && (scrollOffset + visibleItemCount) < tasks.getCountTasks())
        {
            ++scrollOffset;
        }
        updateRenderedTasks();
    }
    else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
    {
        sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);
        if (backgraund.getGlobalBounds().contains(mousePos))
        {
            int index = (mousePos.y - position.y) / itemHeight + scrollOffset;
            if (index >= 0 && index < tasks.getCountTasks() && onClickCallback)
            {
                selectedIndex = index;
                onClickCallback(index);
            }
        }
    }
}
int ScrollableList::getIndex()
{
    return selectedIndex;
}
