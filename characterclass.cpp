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
    iMArmor(0),
    iLevel(1),
    iExperience(0),
    iSpeed(speed),
    hpPerLevel(10),
    pDamagePerLevel(2),
    mDamagePerLevel(1),
    PArmorPerLevel(2),
    iMArmorPerLevel(1),
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

    // optioneel: bereken hoeveel XP nog nodig is voor het volgende level
    int neededForNext = iLevel * 100 - iExperience;
    if (neededForNext < 0)
        neededForNext = 0;

    // hier kun je eventueel debug-print doen
    // std::cout << "XP: " << iExperience
    //           << " | nodig voor level " << (iLevel + 1)
    //           << ": " << neededForNext << std::endl;
}

void CharacterClass::LevelUp()
{
    ++iLevel;

    iMaxHP   += static_cast<int>(hpPerLevel   * hpScalePerLevel);
    iPDamage += static_cast<int>(pDamagePerLevel * pDamageScalePerLevel);
    iMDamage += static_cast<int>(mDamagePerLevel * mDamageScalePerLevel);
    iPArmor  += static_cast<int>(PArmorPerLevel * pArmorScalePerLevel);
    iMArmor  += static_cast<int>(iMArmorPerLevel * mArmorScalePerLevel);
    iSpeed   += static_cast<int>(speedPerLevel * speedScalePerLevel);

    iCurrentHP = iMaxHP;
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
void CharacterClass::RecieveHit(int dealtDamage, int /*currentHP*/)
{
    iCurrentHP -= dealtDamage;
    if (iCurrentHP < 0)
        iCurrentHP = 0;
}


void CharacterClass::PrintName() const {
    std::cout << "Character Name: " << sName << std::endl;
}
