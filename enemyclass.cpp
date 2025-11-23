#include "enemyclass.h"


EnemyClass::EnemyClass(const std::string& name, int maxHP, int damage) : CharacterClass(name,maxHP,damage) {}

// Punt 9: Useful and correct virtual function - deze override levert vijand-specifieke output bij polymorfe aanroep van PrintName().
void EnemyClass::PrintName() const {
    std::cout << "Enemy: " << sName << std::endl;
}


