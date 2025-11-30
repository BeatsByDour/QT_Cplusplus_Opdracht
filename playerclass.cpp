#include "playerclass.h"


PlayerClass::PlayerClass(const std::string& name, int maxHP, int damage) : CharacterClass(name,maxHP,damage) {}

// Punt 9: Useful and correct virtual function - deze override levert spelersspecifieke output als PrintName() polymorf wordt aangeroepen.
void PlayerClass::PrintName() const {
    std::cout << "Player: " << sName << std::endl;
}


