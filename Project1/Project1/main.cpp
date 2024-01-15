#include <iostream>
#include <fstream>
#include <string>
#include "Menu.h"
#include "text/TextJ.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <nlohmann/json.hpp>
#include <Windows.h>

using namespace sf;



int main()
{

    RenderWindow window(VideoMode::getDesktopMode(), L"Риндор", Style::Default);
    window.setVerticalSyncEnabled(true);
   

   

    Music music;
    music.openFromFile("audio/Castle2.ogg");//загружаем файл
    music.setVolume(30);
    music.setLoop(true);
    music.play();//воспроизводим музыку
    
  



    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
               
            }

            Menu::handleEvents(window, event);
        }
        


       
    }
    return 0;


}