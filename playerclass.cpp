#include "playerclass.h"
#include <iostream>

PlayerClass::PlayerClass(const std::string& name, int maxHP, int damage) : CharacterClass(name,maxHP,damage) {}

void PlayerClass::Print() const {
    std::cout << "Player Name: " << sName << std::endl;
}
