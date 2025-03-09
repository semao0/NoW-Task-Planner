#pragma once

#include "GUIElement.h"
#include "TaskManager.h"
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Window.hpp>
#include <vector>
#include "GUIManager.h"
class ScrollableList : public GUIElement
{
private:
    sf::RectangleShape background;
    TaskManager tasks;
    std::vector<sf::Text> renderedTasks;
    int visibleItemCount;
    int scrollOffset;
    int itemHeight;
    sf::Vector2f position;
    int selectedIndex;
    bool isCheckBox;
    bool isArchive;
    GUIManager checkBoxes;
    bool needupdate;
    void markForUpdate();

    void updateRenderedTasks();

public:
    std::function<void(int)> onClickCallback;
    std::function<void(Task&)> onCheckBoxToggle;

    ScrollableList(
        float x, float y, float width, float height, int itemHeight, bool isCheckBox = false, bool isArchive = false);
    void setTasks(TaskManager& tasks);
    void setTasks(std::vector<Task>& tasks);

    void draw(sf::RenderWindow& window) override;
    void handleEvent(const sf::Event& event) override;
    int getIndex();
    void setSelectedIndex(const int index);
};