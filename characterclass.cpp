#include "characterclass.h"


CharacterClass::CharacterClass(const std::string& name, int maxHP, int iDamage)
    : sName(name), iMaxHP(maxHP), iCurrentHP(maxHP), iDamage(iDamage) {}

std::string CharacterClass::GetName() const {
    return sName;
}

int CharacterClass::GetMaxHP() const {
    return iMaxHP;
}

int CharacterClass::GetCurrentHP() const {
    return iCurrentHP;
}

void CharacterClass::SetName(const std::string& name) {
    sName = name;
}

void CharacterClass::SetMaxHP(int maxHP) {
    iMaxHP = maxHP;
}

void CharacterClass::SetCurrentHP(int currentHP) {
    iCurrentHP = currentHP;
}

void CharacterClass::PrintName() const {
    std::cout << "Character Name: " << sName << std::endl;
}
