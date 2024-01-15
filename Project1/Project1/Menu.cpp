#include "Menu.h"
#include <iostream>
#include "Game.h"
#include "text/TextJ.h"
#include <Windows.h>
#include <string>
#include <SFML/Audio.hpp>

sf::Texture backgroundTexture, newGameT, settingsT, exitT, svT;
sf::Sprite background, newGameS, settingsS, exitS, svS;
sf::Font font;

sf::Sprite newGame(){
    newGameT.loadFromFile("image/button/play.png");
    newGameS.setTexture(newGameT);
    newGameS.setPosition(100, 200);
    newGameS.setScale(sf::Vector2f(0.4f, 0.4f));
    return newGameS;
}


sf::Sprite setting() {
    settingsT.loadFromFile("image/button/setting.png");
    settingsS.setTexture(settingsT);
    settingsS.setPosition(100, 400);
    settingsS.setScale(sf::Vector2f(0.4f, 0.4f));
    return settingsS;
}

sf::Sprite exit() {
    exitT.loadFromFile("image/button/exit.png");
    exitS.setTexture(exitT);
    exitS.setPosition(100, 600);
    exitS.setScale(sf::Vector2f(0.4f, 0.4f));
    return exitS;
}

sf::Sprite sv(sf::RenderWindow& window) {
    svT.loadFromFile("image/button/Svitok.png");
    svT.setSmooth(true);
    svS.setTexture(svT);
    svS.setPosition(850, 30);
    svS.setScale(sf::Vector2f(0.7f, 0.7f));
    window.draw(svS);
    window.display();
    return svS;
}

namespace Menu {
    
    void init(sf::RenderWindow& window) {

        int fontSize = 90;

        if (!backgroundTexture.loadFromFile("image/background/Menu.png")) {
        }
        background.setTexture(backgroundTexture);

        if (!font.loadFromFile("arial.ttf")) {
            std::cerr << "Failed to load font" << std::endl;
        }

        sf::Vector2u windowSize = window.getSize();

      

        
        window.draw(background);
        window.draw(newGame());
        window.draw(setting());
        window.draw(exit());
        window.display();
        
    }


    bool status = true;
    bool statusInit = true;
    bool statusSetting = true;
    std::string statusStr = "";
    sf::Sprite svS;
    void handleEvents(sf::RenderWindow& window, sf::Event& event) {
        while (status) {
            sf::Event event;
            while (window.pollEvent(event)) {

                if (statusInit) {
                    init(window);
                    statusInit = false;
                }

                if (!statusSetting) {
                    svS = sv(window);
                    statusSetting = true;
                }



                if (event.type == sf::Event::MouseButtonReleased) {
                    sf::Vector2f mousePos(sf::Mouse::getPosition(window));
                    if (newGameS.getGlobalBounds().contains(mousePos)) {
                        window.clear();
                        status = false;
                        statusSetting = false;

                    }
                    else if (settingsS.getGlobalBounds().contains(mousePos)) {
                        statusSetting = false;
                        statusInit = true;
                    }
                    else if (exitS.getGlobalBounds().contains(mousePos)) {
                        window.close();
                    }
                    if (svS.getGlobalBounds().contains(mousePos)) {
                        statusInit = true;
                    }


                }
            }
        }

        if (!status) {
            Game::init(window);
        }
        
    }


}