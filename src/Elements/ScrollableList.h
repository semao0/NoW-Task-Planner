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
#include "CheckBox.h"
#include "guiManager.h"
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
    bool isCheckBox;
    bool isArchive;
    guiManager checkBoxes;

    void updateRenderedTasks();

public:
    std::function<void(int)> onClickCallback;

    ScrollableList(float x, float y, float width, float height, int itemHeight, bool isCheckBox = false, bool isArchive = false);
    void setTasks(TaskManager& tasks);
    void setTasks(std::vector<Task>);

    void draw(sf::RenderWindow& window) override;
    void handleEvent(const sf::Event& event) override;
    int getIndex();
};
#endif