#ifndef SCROLLABLELIST_H
#define SCROLLABLELIST_H

#include "guiElement.h"
#include "TaskManager.h"
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Window.hpp>
#include <vector>
class ScrollableList : public guiElement
{
private:
    sf::RectangleShape backgraund;
    sf::Font font;
    TaskManager tasks;
    std::vector<sf::Text> renderedTasks;
    int visibleItemCount;
    int scrollOffset;
    int itemHeight;
    sf::Vector2f position;
    int selectedIndex;

    void updateRenderedTasks();

public:
    std::function<void(int)> onClickCallback;

    ScrollableList(float x, float y, float width, float height, int itemHeight);
    void setTasks(TaskManager& tasks);
    void setTasks(std::vector<Task>);

    void draw(sf::RenderWindow& window) override;
    void handleEvent(const sf::Event& event) override;
    int getIndex();
};
#endif