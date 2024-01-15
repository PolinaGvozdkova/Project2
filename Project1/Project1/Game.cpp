#include "Game.h"
#include <iostream>
#include <fstream>
#include <string>
#include "Menu.h"
#include <ctime>
#include "text/TextJ.h"
#include <Windows.h>
#include <codecvt>
#include <locale>
#include <vector>
#include "Del.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>


std::u32string ConvertUTF8ToUTF32(const std::string& utf8String) {
    std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> converter;
    return converter.from_bytes(utf8String);
}


std::vector<sf::RectangleShape> scrollLine(sf::RenderWindow& window) {
    std::vector<sf::RectangleShape> rectangleVector;
    for (int i = 0; i < 7; i++) {
        sf::RectangleShape rectangle;
        rectangle.setPosition(200 + i * 45, 300);
        rectangle.setSize(sf::Vector2f(40.0f, 100.0f));
        rectangle.setFillColor(sf::Color(0, 0, 0, 0));
        rectangle.setOutlineThickness(5.0f);
        rectangle.setOutlineColor(sf::Color(0, 0, 0));
        rectangleVector.push_back(rectangle);
    }
    return rectangleVector;
}

void AnimationHero(sf::RenderWindow& window, int index) {
    sf::Texture tilesetTexture, tilesetTexture1, tilesetTexture2;
    tilesetTexture.loadFromFile("image/animations/Slash.png");
    tilesetTexture1.loadFromFile("image/animations/Claw.png");
    tilesetTexture2.loadFromFile("image/animations/Recovery2.png");
    tilesetTexture.setSmooth(true);
    tilesetTexture1.setSmooth(true);
    tilesetTexture2.setSmooth(true);
    std::vector<sf::Sprite> tilesetVector = { sf::Sprite(tilesetTexture), sf::Sprite(tilesetTexture1), sf::Sprite(tilesetTexture2) };

    const int tileSize = 192; // Размер каждого тайла
    const int numFrames = 5; // Общее количество кадров анимации
    int currentFrame = 0;    // Текущий кадр
    bool status = true;
    int numRows = 5;
    int numFramesPerRow = 4;
    sf::Sprite tilesetSprite = tilesetVector[index];

    sf::Clock clock;
    sf::Time frameTime = sf::milliseconds(100); // Время между кадрами

    while (status) {
        sf::Time elapsed = clock.restart();

        tilesetSprite.setTextureRect(sf::IntRect(currentFrame * tileSize, 0, tileSize, tileSize));
        tilesetSprite.setPosition(1340, 450);
        tilesetSprite.setScale(sf::Vector2f(1.5f, 1.5f));
        window.draw(tilesetSprite);
        window.display();
        sf::sleep(sf::milliseconds(100));
        // Обновление анимации по прошествии времени
        if (elapsed >= frameTime) {
            currentFrame = (currentFrame + 1) % (5 + numRows * numFramesPerRow);
        }
       

        if (currentFrame >= 6) {
            return;
        }

       
    }
}


class drawHero {
    private:
        std::vector<sf::Sprite> vH;
        sf::Font font;
        sf::Texture boxT;
        std::vector<Hero> heroVector;
        std::vector<int> maxHpHeroesVector;
        int maxSpeedHeroes = 0;
        int speedHeroes;
        int totalHp = 0;
    public:
        drawHero() {
            if (!font.loadFromFile("arial.ttf")) {}
            for (int i = 0; i < 3; i++) {
                Hero hero = getHero(i);
                heroVector.push_back(hero);
                maxHpHeroesVector.push_back(hero.hp);
                maxSpeedHeroes = maxSpeedHeroes + hero.speed;
                totalHp = totalHp + hero.hp;
            }
            speedHeroes = maxSpeedHeroes;
        }

        void draw(sf::RenderWindow& window){
            drawHeroes(window);
            drawHeroesName(window);
            drawHeroesHp(window);
            drawHeroesForce(window);
            drawHeroesSpeed(window);
        }

        int AtackHeroes(int index, sf::RenderWindow& window) {
            std::vector<sf::RectangleShape> rectangleVector = scrollLine(window);
            int SCROLL_INCREMENT = 0;
            bool status = true;

            sf::Clock clock;
            float frameRate = 1.0f / 1.0f;
            while (status) {
                sf::Event event;

                while (window.pollEvent(event)) {
                    if (event.type == sf::Event::Closed) {
                        window.close();
                    }

                    if (event.type == sf::Event::KeyPressed) {
                        if (event.key.code == sf::Keyboard::Space) {
                            status = false;
                        }
                    }
                }

                for (int i = 0; i < rectangleVector.size(); i++) {
                    rectangleVector[i].setFillColor(sf::Color(255, 255, 255, 255));
                    window.draw(rectangleVector[i]);
                }

                if (SCROLL_INCREMENT > rectangleVector.size() - 1) {
                    SCROLL_INCREMENT = 0;
                }

                sf::RectangleShape rect = rectangleVector[SCROLL_INCREMENT];
                rect.setFillColor(sf::Color(200, 0, 200));

                window.draw(rect);
                window.display();

                sf::Time elapsed = clock.restart();

                if (elapsed.asSeconds() < frameRate) {
                    sf::sleep(sf::Time(sf::seconds(0.2)));
                }

                std::string s = heroVector[index].name;
                SCROLL_INCREMENT++;
            }

            OutputDebugStringA(std::to_string(SCROLL_INCREMENT).c_str());
            return SCROLL_INCREMENT;
        }

        void drawHeroes(sf::RenderWindow& window) {
            for (int i = 0; i < 3; i++) {
                Hero hero = heroVector[i];
                if (hero.hp <= 0) {
                    break;
                }

                boxT.loadFromFile(hero.imagePath);
                boxT.setSmooth(true);
                sf::Sprite boxS;
                boxS.setTexture(boxT);
                boxS.setPosition(hero.posX * 10.0f, hero.posY - 120.0f);
                boxS.setScale(sf::Vector2f(1.5f, 1.5f));
                vH.push_back(boxS);
                window.draw(boxS);
            }
        }

        void drawHeroesName(sf::RenderWindow& window) {
            for (int i = 0; i < 3; i++) {
                Hero hero = heroVector[i];

                if (hero.hp <= 0) {
                    break;
                }

                sf::Text text(hero.name, font, 30);
                text.setPosition(hero.posX * 15.0f, hero.posY - 240.0f);
                text.setFillColor(sf::Color::Blue);
                window.draw(text);
            }
        }

        void drawHeroesHp(sf::RenderWindow& window) {
            for (int i = 0; i < heroVector.size(); i++) {
                Hero hero = heroVector[i];
                int maxHp = maxHpHeroesVector[i];

                if (hero.hp <= 0) {
                    heroVector[i] = Hero("", "", 0, 0, 0, 0, 0);
                    break;
                }

                int distance = 25;
                sf::Text hp, hpd;
                hp.setString(std::to_string(maxHp));
                hp.setFont(font);
                hp.setScale(sf::Vector2f(1.0f, 1.0f));
                hp.setPosition(hero.posX * 15.0f, hero.posY - 200.0f);
                hp.setFillColor(sf::Color::Red);
                window.draw(hp);
                
                if (maxHp >= 10) {
                    distance = 40;
                }
                if (maxHp >= 100) {
                    distance = 60;
                }
                hpd.setString("/ " + std::to_string(hero.hp));
                hpd.setFont(font);
                hpd.setScale(sf::Vector2f(1.0f, 1.0f));
                hpd.setPosition(hero.posX * 15 + distance, hero.posY - 200.0f);
                hpd.setFillColor(sf::Color::Red);
                window.draw(hpd);
            }
        }

        void restartSpeed() {
            speedHeroes = maxSpeedHeroes;
        }

        void setHpHeroOne(int damage) {
            heroVector[0].hp = heroVector[0].hp - damage;
        }

        void setHpHeroTwo(int damage) {
            heroVector[1].hp = heroVector[1].hp - damage;
        }

        void setHpHeroTree(int damage) {
            heroVector[2].hp = heroVector[2].hp - damage;
        }

        void setHpHero(int index, int damage) {
            heroVector[index].hp = heroVector[index].hp - damage;
            totalHp = totalHp - damage;
        }

        void setSpeedHero(int speed) {
            speedHeroes = speedHeroes - speed;
        }

        int getTotalHp() {
            return totalHp;
        }

        int getSpeedHero() {
            return speedHeroes;
        }

        int getMaxSpeedHero() {
            return maxSpeedHeroes;
        }

        sf::Sprite getHpHero(int index) {
            return vH[index];
        }

        int getHeroDamage(int index) {
            return heroVector[index].force;
        }


        void drawHeroesForce(sf::RenderWindow& window) {
            for (int i = 0; i < 3; i++) {
                Hero hero = heroVector[i];
                if (hero.hp <= 0) {
                    break;
                }
                sf::Text force;
                force.setString(std::to_string(hero.force));
                force.setFont(font);
                force.setScale(sf::Vector2f(1.0f, 1.0f));
                force.setPosition(hero.posX * 15.0f, hero.posY - 160.0f);
                force.setFillColor(sf::Color::Green);
                window.draw(force);
            }
        }

        void drawHeroesSpeed(sf::RenderWindow& window) {
            for (int i = 0; i < 3; i++) {
                Hero hero = heroVector[i];

                if (hero.hp <= 0) {
                    break;
                }
                sf::Text speed;
                speed.setString(std::to_string(hero.speed));
                speed.setFont(font);
                speed.setScale(sf::Vector2f(1.0f, 1.0f));
                speed.setPosition(hero.posX * 15.0f, hero.posY - 130.0f);
                speed.setFillColor(sf::Color::Yellow);
                window.draw(speed);
            }
        }
};
    class drawEnemy{
    private:
        std::vector<sf::Sprite> vH;
        sf::Font font;
        sf::Texture T;
        Enemy enemy = Enemy("", "", 0, 0, 0, 0, 0);
        int maxHP;
    public:
        drawEnemy(){
            if (!font.loadFromFile("arial.ttf")) {};
            enemy = getEnemy();
            maxHP = enemy.hp;
        }

        void draw(sf::RenderWindow& window) {
            drawEnemys(window);
            drawEnemysName(window);
            drawEnemysHp(window);
            drawEnemysForce(window);
            drawEnemysSpeed(window);
        }

        void setEnemyHp(float damage) {
            enemy.hp = enemy.hp - damage;
        }

        int getEnemyHp() {
            return enemy.hp;
        }

        int getEnemySpeed() {
            return enemy.speed;
        }

        int getEnemyDamage() {
            return enemy.force;
        }

        void drawEnemys(sf::RenderWindow& window) {
            T.loadFromFile(enemy.imagePath);
            T.setSmooth(true);
            sf::Sprite S;
            S.setTexture(T);
            S.setPosition(enemy.posX, enemy.posY);
            S.setScale(sf::Vector2f(1.5f, 1.5f));
            window.draw(S);
        }

        void drawEnemysName(sf::RenderWindow& window) {
            sf::Text text(enemy.name, font, 30);
            text.setPosition(enemy.posX, enemy.posY - 100);
            text.setFillColor(sf::Color::Black);
            window.draw(text);
        }

        void drawEnemysHp(sf::RenderWindow& window) {
            sf::Text hp;
            hp.setString("/ " + std::to_string(enemy.hp));
            hp.setFont(font);
            hp.setScale(sf::Vector2f(1.0f, 1.0f));
            hp.setPosition(enemy.posX + 180, enemy.posY - 60);
            hp.setFillColor(sf::Color::Red);
            window.draw(hp);

            sf::Text hpd;
            hpd.setString(std::to_string(maxHP));
            hpd.setFont(font);
            hpd.setScale(sf::Vector2f(1.0f, 1.0f));
            hpd.setPosition(enemy.posX, enemy.posY - 60);
            hpd.setFillColor(sf::Color::Red);
            window.draw(hpd);
        }
        
        void drawEnemysForce(sf::RenderWindow& window) {
            sf::Text force;
            force.setString(std::to_string(enemy.force));
            force.setFont(font);
            force.setScale(sf::Vector2f(1.0f, 1.0f));
            force.setPosition(enemy.posX, enemy.posY - 30);
            force.setFillColor(sf::Color::Green);
            window.draw(force);
        }

        void drawEnemysSpeed(sf::RenderWindow& window) {
            sf::Text speed;
            speed.setString(std::to_string(enemy.speed));
            speed.setFont(font);
            speed.setScale(sf::Vector2f(1.0f, 1.0f));
            speed.setPosition(enemy.posX, enemy.posY);
            speed.setFillColor(sf::Color::Yellow);
            window.draw(speed);
        }

       
       
};
    void audioEnemy() {
        // Создаем звуковой буфер и загружаем в него звуковой файл
        sf::SoundBuffer buffer;
        buffer.loadFromFile("audio/Growl.ogg");

        // Создаем объект звука и устанавливаем для него буфер
        sf::Sound sound;
        sound.setBuffer(buffer);

        // Воспроизводим звук
        sound.play();
    }

    


namespace Game {
    sf::Texture backgroundTexture, herotexture, textboxT, healthBarT;
    sf::Sprite backgroundSprite, herosprite, textboxS, healthBarSprite;
    sf::Font font;
    int INCREMENT = 0;




    void init(sf::RenderWindow& window) {



        if (!backgroundTexture.loadFromFile("image/background/fons.png")) {
            // Обработка ошибки загрузки текстуры

        }
   

        backgroundSprite.setTexture(backgroundTexture);

        textboxT.loadFromFile("image/button/textbox.png");
        textboxS.setTexture(textboxT);
        textboxS.setPosition(70, 500);
        textboxS.setScale(sf::Vector2f(0.7f, 0.7f));

        herotexture.loadFromFile("image/hero/Actor3_6.png");//загружаем картинку
        herotexture.setSmooth(true);
        herosprite.setTexture(herotexture);//передаём в него объект Texture (текстуры)
        herosprite.setPosition(660, 90);//задаем начальные координаты появления спрайта
        herosprite.setScale(sf::Vector2f(1.6f, 1.6f));


        // Получаем размер окна
        sf::Vector2u windowSize = window.getSize();
        // Устанавливаем масштаб для спрайта так, чтобы он занимал всю площадь окна
        backgroundSprite.setScale(static_cast<float>(windowSize.x) / backgroundTexture.getSize().x,
            static_cast<float>(windowSize.y) / backgroundTexture.getSize().y);



        Person person;
        person.getName();

        if (!font.loadFromFile("arial.ttf")) {

        }
           
        std::string utf8String = person.getName();
        sf::String utf32String = sf::String::fromUtf8(utf8String.begin(), utf8String.end());
        sf::Text text(utf32String, font, 30);
        text.setPosition(500, 650);
        text.setFillColor(sf::Color::Red);
        

        std::string utf8StringDialog = person.getDialog(0);
        sf::String utf32StringDialog = sf::String::fromUtf8(utf8StringDialog.begin(), utf8StringDialog.end());
        sf::Text textDialog(utf32StringDialog, font, 30);
        textDialog.setPosition(500, 700);
        textDialog.setFillColor(sf::Color::Black);

   
        OutputDebugStringA("\n\n\n");
        OutputDebugStringA(std::to_string(unitTestTest()).c_str());
        OutputDebugStringA("\n\n\n");
        OutputDebugStringA("\n\n\n");
        OutputDebugStringA("\n\n\n");


        std::vector<sf::RectangleShape> rectangleVecor = scrollLine(window);
        int sizeDialog = person.getSizeDialog();
        drawHero drawHeroes = drawHero();
        drawEnemy drawEnemes = drawEnemy();
        int SCROLL_INCREMENT = 0;
        int typeHeroAnimated = -1;
        bool typeHeroAnimatedBool = false;
        bool statusLifeHero = true;
        bool statusEmenyAtack = false;

        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                }
                if (event.type == sf::Event::KeyPressed)
                {
                    if (event.key.code == sf::Keyboard::Space)
                    {
                        INCREMENT++;
                        if (INCREMENT < sizeDialog) {
                            std::string utf8StringDialog = person.getDialog(INCREMENT);
                            sf::String utf32StringDialog = sf::String::fromUtf8(utf8StringDialog.begin(), utf8StringDialog.end());
                            textDialog.setString(utf32StringDialog);
                            sf::sleep(sf::Time(sf::seconds(0.1f)));
                        }
                        
                    }
                }

                if (event.type == sf::Event::MouseButtonReleased and drawHeroes.getSpeedHero() > 0) {
                    sf::Vector2f mousePos(sf::Mouse::getPosition(window));
                    if (drawHeroes.getHpHero(0).getGlobalBounds().contains(mousePos)) {
                        int idsad = drawHeroes.AtackHeroes(0, window) + 1;
                        float damage = idsad * 0.2 * drawHeroes.getHeroDamage(0);
                        drawEnemes.setEnemyHp(damage);
                        drawHeroes.setSpeedHero(drawEnemes.getEnemySpeed());
                        typeHeroAnimated = 0;
                        typeHeroAnimatedBool = false;
                        statusEmenyAtack = true;
                    }
                    if (drawHeroes.getHpHero(1).getGlobalBounds().contains(mousePos)) {
                        int idsad = drawHeroes.AtackHeroes(1, window) + 1;
                        float damage = idsad * 0.2 * drawHeroes.getHeroDamage(1);
                        drawEnemes.setEnemyHp(damage);  
                        drawHeroes.setSpeedHero(drawEnemes.getEnemySpeed());
                        typeHeroAnimated = 1;
                        typeHeroAnimatedBool = false;
                        statusEmenyAtack = true;
                    }
                    if (drawHeroes.getHpHero(2).getGlobalBounds().contains(mousePos)) {
                        int idsad = drawHeroes.AtackHeroes(2, window) + 1;
                        float damage = idsad * 0.2 * drawHeroes.getHeroDamage(2);
                        drawEnemes.setEnemyHp(damage);
                        drawHeroes.setSpeedHero(drawEnemes.getEnemySpeed());
                        typeHeroAnimated = 2;
                        typeHeroAnimatedBool = false;
                        statusEmenyAtack = true;
                    }
                }

                if (drawHeroes.getSpeedHero() < 0 and statusEmenyAtack) {
                    int random = std::rand() % 3;
                    drawHeroes.setHpHero(random, drawEnemes.getEnemyDamage());
                    drawHeroes.restartSpeed();
                    statusEmenyAtack = false;
                    OutputDebugStringA("Atack \n");
                }

                if (statusLifeHero) {
                    if (drawHeroes.getTotalHp() <= 0) {
                        window.clear();
                        sf::Texture goT;
                        sf::Sprite goS;
                        goT.loadFromFile("image/background/GO.jpg");
                        goT.setSmooth(true);
                        goS.setTexture(goT);
                        goS.setPosition(300, 50);
                        goS.setScale(sf::Vector2f(1.0f, 1.0f));
                        window.draw(goS);
                        window.display();
                        
                    }
                    else {
                        window.clear();
                        window.draw(backgroundSprite);
                        if (INCREMENT < sizeDialog) {
                            window.draw(herosprite);
                            window.draw(textboxS);
                            window.draw(textDialog);
                            window.draw(text);

                        }
                        else {
                            drawEnemes.draw(window);
                            drawHeroes.draw(window);
                            if (typeHeroAnimated != -1 and typeHeroAnimatedBool) {

                                AnimationHero(window, typeHeroAnimated);
                                typeHeroAnimated = -1;
                            }
                            typeHeroAnimatedBool = true;
                        }




                        window.display();
                    }
                }
            }

            
        }
     
    }
}