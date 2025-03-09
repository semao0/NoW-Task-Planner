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

ScrollableList::ScrollableList(
    float x, float y, float width, float height, int itemHeight, bool isCheckBox, bool isArchive)
    : scrollOffset(0), itemHeight(itemHeight), position(x, y), selectedIndex(-1), isCheckBox(isCheckBox),
      isArchive(isArchive), needupdate(false)
{
    background.setPosition(position);
    background.setSize(sf::Vector2f(width, height));
    background.setFillColor(sf::Color::White);
    background.setOutlineThickness(2);
    background.setOutlineColor(sf::Color::Black);

    visibleItemCount = height / itemHeight;

    markForUpdate();
}

void ScrollableList::setTasks(TaskManager& tasks)
{
    this->tasks = tasks;
    markForUpdate();
}

void ScrollableList::setTasks(std::vector<Task>& tasks)
{
    TaskManager subtasks;
    for (auto& task : tasks)
    {
        subtasks.addTaskRev(task);
    }
    this->tasks = subtasks;
    markForUpdate();
}

void ScrollableList::updateRenderedTasks()
{
    renderedTasks.clear();
    checkBoxes.clear();
    for (int i = 0; i < visibleItemCount && (i + scrollOffset) < tasks.getCountTasks(isArchive); i++)
    {
        int index = i + scrollOffset;

        auto& taskList = tasks.getTasks(isArchive);
        auto& task = taskList[index];
        std::string name = task.getName();

        std::string dateString = std::format("{:02}-{:02}-{}", 
            static_cast<unsigned>(task.getDeadline().day()),
            static_cast<unsigned>(task.getDeadline().month()), 
            static_cast<int>(task.getDeadline().year()));

        if (isCheckBox)
        {
            auto checkbox = std::make_unique<CheckBox>(position.x + background.getSize().x - 40,
                                                       position.y + i * itemHeight + (itemHeight / 1.7),
                                                       30,
                                                       30,
                                                       task.isCompleted(),
                                                       [this, task, &taskList]()
                                                       {
                                                           for (auto& t : taskList)
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
        if (FontManager::getFont().getGlyph(name[0], 20, false).advance * name.size() > background.getSize().x - 200)
        {
            name = name.substr(
                       0, (background.getSize().x - 200) / FontManager::getFont().getGlyph('A', 20, false).advance) +
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
    window.draw(background);
    for (const auto& text : renderedTasks)
    {
        window.draw(text);
    }

    for (size_t i = 1; i < (renderedTasks.size()) / 2 + 1; i++)
    {
        sf::RectangleShape line;
        line.setSize((sf::Vector2f(background.getSize().x, 2)));
        line.setPosition(position.x, position.y + i * itemHeight);
        line.setFillColor(sf::Color::Black);
        window.draw(line);
    }

    checkBoxes.draw(window);

    if (selectedIndex >= 0 && selectedIndex - scrollOffset < visibleItemCount)
    {

        float yOffset = position.y + (selectedIndex - scrollOffset) * itemHeight;
        float highlightHeight = itemHeight - 2;
        if (selectedIndex == 0)
        {
            highlightHeight = itemHeight;
        }
        else
        {
            yOffset += 2;
        }
        sf::RectangleShape highlight(sf::Vector2f(background.getSize().x, highlightHeight));
        highlight.setPosition(position.x, yOffset);
        highlight.setFillColor(sf::Color(1, 1, 1, 50));
        highlight.setOutlineThickness(2);
        highlight.setOutlineColor(sf::Color::Black);
        window.draw(highlight);
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
        markForUpdate();
    }
    else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
    {
        sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);
        if (background.getGlobalBounds().contains(mousePos))
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

void ScrollableList::markForUpdate()
{
    needupdate = true;
}

void ScrollableList::setSelectedIndex(const int index)
{
    selectedIndex = index;
}