#include "TextJ.h"
#include <Windows.h>
#include <nlohmann/json.hpp>
#include <iostream>
#include <fstream>
#include <string>


using json = nlohmann::json;


Hero::Hero(std::string heroName, std::string heroImagePath, int heroHP, int heroForce, int heroPosX, int heroPosY, int heroSpeed) {
    name = heroName;
    imagePath = heroImagePath;
    hp = heroHP;
    force = heroForce;
    posX = heroPosX;
    posY = heroPosY;
    speed = heroSpeed;
};
Enemy::Enemy(std::string enemyName, std::string enemyImagePath, int enemyHP, int enemyForce, int enemyPosX, int enemyPosY,int enemySpeed) {
    name = enemyName;
    imagePath = enemyImagePath;
    hp = enemyHP;
    force = enemyForce;
    posX = enemyPosX;
    posY = enemyPosY;
    speed = enemySpeed;
};


std::string ConvertUTF8ToANSI(const std::string& utf8String) {
    int requiredSize = MultiByteToWideChar(CP_UTF8, 0, utf8String.c_str(), -1, NULL, 0);
    if (requiredSize == 0) {
        // Обработка ошибки
        return "";
    }

    std::wstring wideString(requiredSize, 0);
    MultiByteToWideChar(CP_UTF8, 0, utf8String.c_str(), -1, &wideString[0], requiredSize);

    int ansiSize = WideCharToMultiByte(CP_ACP, 0, wideString.c_str(), -1, NULL, 0, NULL, NULL);
    if (ansiSize == 0) {
        // Обработка ошибки
        return "";
    }

    std::string ansiString(ansiSize, 0);
    WideCharToMultiByte(CP_ACP, 0, wideString.c_str(), -1, &ansiString[0], ansiSize, NULL, NULL);

    return ansiString;
}

json dataJson() {
    std::ifstream input_file("text/Test.json");
    if (!input_file.is_open()) {
        std::cerr << "Unable to open file!" << std::endl;
    }

    json jsonData;
    input_file >> jsonData;
    return jsonData;
}

std::string Person::getName() {
    json data = dataJson();
    std::string outputData = data["person"]["name"].get<std::string>();
    return outputData;
}

std::string Person::getDialog(int index) {
    json data = dataJson();
    std::string outputData = data["person"]["dialog"][index].get<std::string>();
    return outputData;
}

int Person::getSizeDialog() {
    json data = dataJson();
    int outputData = data["person"]["dialog"].size();
    return outputData;
}

Hero getHero(int index){
    json data = dataJson();
    json outputData = data["heroes"][index];

    std::string name = outputData["name"].get<std::string>();
    std::string image = outputData["image"].get<std::string>();

    int hp = outputData["heroHP"].get<int>();
    int force = outputData["force"].get<int>();
    int posX = outputData["posX"].get<int>();
    int posY = outputData["posY"].get<int>();
    int speed = outputData["speed"].get<int>();

    return Hero(name, image, hp, force, posX, posY, speed); 
}

bool unitTestTest() {
    Hero hero1 = Hero("Deny", "image/hero/Actor2_6.png", 120, 80, 5, 700, 10);
    Hero hero2 = getHero(0);
    if (hero1.name == hero2.name) {}
    else { return false;}
    if (hero1.imagePath == hero2.imagePath) {}
    else { return false; }
    if (hero1.hp == hero2.hp) {}
    else { return false; }
    if (hero1.force == hero2.force) {}
    else { return false; }
    if (hero1.posX == hero2.posX) {}
    else { return false; }
    if (hero1.posY == hero2.posY) {}
    else { return false; }
    if (hero1.speed == hero2.speed) {}
    else { return false; }
    return true;
}

Enemy getEnemy() {
    json data = dataJson();
    json outputData = data["enemy"][0];

    std::string name = outputData["name"].get<std::string>();
    std::string image = outputData["image"].get<std::string>();

    int hp = outputData["enemyHP"].get<int>();
    int forse = outputData["force"].get<int>();
    int posX = outputData["posX"].get<int>();
    int posY = outputData["posY"].get<int>();
    int speed = outputData["speed"].get<int>();

    return Enemy(name, image, hp, forse, posX, posY, speed);
}
