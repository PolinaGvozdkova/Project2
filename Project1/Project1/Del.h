#pragma once
#include <SFML/Graphics.hpp>

class Del
{
public:
    void init()
    {

    }

    void handleEvents(sf::RenderWindow& window, sf::Event& event)
    {
        if (event.type == sf::Event::KeyPressed)
        {
            if (event.key.code == sf::Keyboard::Space)
            {
                // �������� ��������� ��, �����, ����� ����� � 
                herosprite = nullptr;
                //textboxS.setColor(sf::Color::Transparent);
            }
        }
    }
private:
    std::unique_ptr<sf::Sprite> herosprite;
};