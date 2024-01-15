#pragma once

#include <nlohmann/json.hpp>
#include <string>
#include <array>
#include <SFML/Graphics.hpp> 
using json = nlohmann::json;

std::string ConvertUTF8ToANSI(const std::string& utf8String);
bool unitTestTest();

class Hero
{
public:
    std::string name;
    std::string imagePath;
    int hp;
    int force;
    int posX;
    int posY;
    int speed;
    Hero(std::string heroName, std::string heroImagePath, int heroHP, int heroForce, int heroPosX, int heroPosY, int heroSpeed);
};

Hero getHero(int index);

class Enemy
{
public:
    std::string name;
    std::string imagePath;
    int hp;
    int force;
    int posX;
    int posY;
    int speed;
    Enemy(std::string enemyName, std::string enemyImagePath, int enemyHP, int enemyForce, int enemyPosX, int enemyPosY, int enemySpeed);
};

Enemy getEnemy();

class Person {

public:
    std::string getName();
    std::string getDialog(int index);
    int getSizeDialog();
};