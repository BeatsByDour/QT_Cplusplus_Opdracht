#include "characterclass.h"


CharacterClass::CharacterClass(const std::string& name,
                               int maxHp,
                               int damage,
                               int speed)
    : sName(name),
    iMaxHP(maxHp),
    iCurrentHP(maxHp),
    iPDamage(damage),
    iMDamage(0),
    iPArmor(0),
    iMarmor(0),
    iLevel(1),
    iExperience(0),
    iSpeed(speed),
    hpPerLevel(10),
    pDamagePerLevel(2),
    mDamagePerLevel(1),
    PArmorPerLevel(2),
    iMarmorPerLevel(1),
    speedPerLevel(1)
{
}

void CharacterClass::AddExperience(int amount)
{
    iExperience += amount;
    // simpele curve: level up bij 100 * current level
    while (iExperience >= iLevel * 100)
    {
        iExperience -= iLevel * 100;
        LevelUp();
    }
}

void CharacterClass::LevelUp()
{
    ++iLevel;
    iMaxHP     += hpPerLevel;
    iPDamage   += pDamagePerLevel;
    iMDamage   += mDamagePerLevel;
    iPArmor    += PArmorPerLevel;
    iMarmor     += iMarmorPerLevel;
    iSpeed     += speedPerLevel;
    iCurrentHP  = iMaxHP; // eventueel full heal
}


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
