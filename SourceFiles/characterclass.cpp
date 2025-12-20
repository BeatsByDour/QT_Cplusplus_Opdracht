#include "characterclass.h"


#include <random>


static int RandInt(int minInclusive, int maxInclusive)
{
    static std::mt19937 rng{std::random_device{}()};
    std::uniform_int_distribution<int> dist(minInclusive, maxInclusive);
    return dist(rng);
}


CharacterClass::CharacterClass(const std::string& name,
                               int maxHp,
                               int pDamage,
                               int mDamage,
                               int pArmor,
                               int mArmor,
                               int speed,
                               QString visualimage)
    : sName(name),
    iMaxHP(maxHp),
    iCurrentHP(maxHp),
    iPDamage(pDamage),
    iMDamage(mDamage),
    iPArmor(pArmor),
    iMArmor(mArmor),
    iLevel(1),
    iExperience(0),
    iSpeed(speed),
    VisualImage(visualimage)
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

}

void CharacterClass::LevelUp()
{
    ++iLevel;

    // HP: goed → 3–5, slecht/overig → 1–2
    if (bGoodHP)
        iMaxHP += RandInt(3, 5);
    else
        iMaxHP += RandInt(1, 2);

    // Physical Damage: goed → 1–3, slecht → 0–1
    if (bGoodPDamage)
        iPDamage += RandInt(1, 3);
    else
        iPDamage += RandInt(0, 1);

    // Magical Damage: goed → 1–3, slecht → 0–1
    if (bGoodMDamage)
        iMDamage += RandInt(1, 3);
    else
        iMDamage += RandInt(0, 1);

    // Physical Armor: goed → 1–3, slecht → 0–1
    if (bGoodPArmor)
        iPArmor += RandInt(1, 3);
    else
        iPArmor += RandInt(0, 1);

    // Magical Armor: goed → 1–3, slecht → 0–1
    if (bGoodMArmor)
        iMArmor += RandInt(1, 3);
    else
        iMArmor += RandInt(0, 1);

    // Speed: goed → 1–3, slecht → 0–1
    if (bGoodSpeed)
        iSpeed += RandInt(1, 3);
    else
        iSpeed += RandInt(0, 1);

    // HP bijvullen na level-up
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
    std::cout <<" hp bfore hit: " << iCurrentHP<< std::endl;
    iCurrentHP -= dealtDamage;
    if (iCurrentHP < 0)
        iCurrentHP = 0;
      std::cout <<" hp after hit: " << iCurrentHP<< std::endl;
}


void CharacterClass::PrintName() const {
    std::cout << "Character Name: " << sName << std::endl;
}

