#include "enemyclass.h"


EnemyClass::EnemyClass(const std::string& name, int maxHP, int damage) : CharacterClass(name,maxHP,damage) {}

void EnemyClass::PrintName() const {
    std::cout << "Enemy: " << sName << std::endl;
}

