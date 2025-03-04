#include "ScrollableList.h"
#include "FontManager.h"
#include "Task.h"
#include "TaskManager.h"
#include "CheckBox.h"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/PrimitiveType.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Mouse.hpp>
#include <string>
#include <iostream>

ScrollableList::ScrollableList(
    float x, float y, float width, float height, int itemHeight, bool isCheckBox, bool isArchive)
    : scrollOffset(0), itemHeight(itemHeight), position(x, y), selectedIndex(-1), isCheckBox(isCheckBox),
      isArchive(isArchive), needupdate(false)
{
    backgraund.setPosition(position);
    backgraund.setSize(sf::Vector2f(width, height));
    backgraund.setFillColor(sf::Color::White);
    backgraund.setOutlineThickness(2);
    backgraund.setOutlineColor(sf::Color::Black);

    visibleItemCount = height / itemHeight;

    updateRenderedTasks();
}

void ScrollableList::setTasks(TaskManager& tasks)
{
    this->tasks = tasks;
    updateRenderedTasks();
}

void ScrollableList::setTasks(std::vector<Task> tasks)
{
    TaskManager subtasks;
    for (auto& task : tasks)
    {
        subtasks.addTaskRev(task);
    }
    this->tasks = subtasks;
    updateRenderedTasks();
}

void ScrollableList::updateRenderedTasks()
{
    renderedTasks.clear();
    checkBoxes.clear();

    for (int i = 0; i < visibleItemCount && (i + scrollOffset) < tasks.getCountTasks(isArchive); i++)
    {
        int index = i + scrollOffset;

        const auto& task = tasks.getTasks(isArchive)[index];
        std::string name = task.getName();

        int year = static_cast<int>(task.getDeadline().year());
        unsigned month = static_cast<unsigned>(task.getDeadline().month());
        unsigned day = static_cast<unsigned>(task.getDeadline().day());
        std::ostringstream oss;
        oss << year << "-" << (month < 10 ? "0" : "") << month << "-" << (day < 10 ? "0" : "") << day;
        std::string dateString = oss.str();

        if (isCheckBox)
        {
            auto checkbox = std::make_unique<CheckBox>(position.x + backgraund.getSize().x - 40,
                                                       position.y + i * itemHeight + (itemHeight / 1.7),
                                                       30,
                                                       30,
                                                       tasks.getTasks(isArchive)[index].isCompleted(),
                                                       [this, &task]()
                                                       {
                                                           for (auto& t : tasks.getTasks(isArchive))
                                                           {

                                                               if (t == task)
                                                               {
                                                                   if (onCheckBoxToggle)
                                                                   {
                                                                       onCheckBoxToggle(t);
                                                                   }
                                                                   needupdate = true;
                                                                   tasks.loadTasks();
                                                                   break;
                                                               }
                                                           }
                                                       });
            checkBoxes.addElement(std::move(checkbox));
        }
        if (FontManager::getFont().getGlyph(name[0], 20, false).advance * name.size() > backgraund.getSize().x - 200)
        {
            name = name.substr(
                       0, (backgraund.getSize().x - 200) / FontManager::getFont().getGlyph('A', 20, false).advance) +
                   "...";
        }

        sf::Text text(name, FontManager::getFont(), 20);
        text.setPosition(position.x + 10, position.y + i * itemHeight + 10);
        text.setFillColor(sf::Color::Black);

        sf::Text date(dateString, FontManager::getFont(), 20);
        date.setPosition(position.x + 450, position.y + i * itemHeight + 10);
        if (!tasks.getTasks(isArchive)[i + scrollOffset].isDeadLineActive())
        {
            date.setFillColor(sf::Color::Red);
            text.setFillColor(sf::Color::Red);
        }
        else
        {
            date.setFillColor(sf::Color::Black);
            text.setFillColor(sf::Color::Black);
        }

        renderedTasks.push_back(date);
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

    for (size_t i = 0; i < (renderedTasks.size()) / 2 + 1; i++)
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
    checkBoxes.draw(window);
    if (needupdate)
    {
        updateRenderedTasks();
        needupdate = !needupdate;
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
        else if (event.mouseWheelScroll.delta < 0 && (scrollOffset + visibleItemCount) < tasks.getCountTasks(isArchive))
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
            if (index >= 0 && index < tasks.getCountTasks(isArchive) && onClickCallback)
            {
                selectedIndex = index;
                onClickCallback(index);
            }
        }
    }
    checkBoxes.handleEvent(event);
    if (needupdate)
    {
        updateRenderedTasks();
    }
}
int ScrollableList::getIndex()
{
    return selectedIndex;
}
