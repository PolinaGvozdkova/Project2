#pragma once

#include <SFML/Graphics.hpp>

namespace Game {
    void init(sf::RenderWindow& window);
    void handleEvents(sf::RenderWindow& window, sf::Event& event);
}

