#pragma once

#include <SFML/Graphics.hpp>

namespace Menu {
    void init(sf::RenderWindow& window);
    void cleanup();
    void handleEvents(sf::RenderWindow& window, sf::Event& event);
    void draw(sf::RenderWindow& window);
}