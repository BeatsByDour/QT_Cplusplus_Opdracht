#include "playerclass.h"


PlayerClass::PlayerClass(const std::string& name, int maxHP, int damage) : CharacterClass(name,maxHP,damage) {}

void PlayerClass::PrintName() const {
    std::cout << "Player: " << sName << std::endl;
}

