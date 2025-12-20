#include "CreatureClass.h"
#include <iostream>


bool CreatureClass::HasType(Type t) const
{
    return aTypes[0] == t || aTypes[1] == t;
}

void CreatureClass::PrintTypes() const
{
    std::cout << GetName() << " types: ";
    std::cout << static_cast<int>(aTypes[0]);
    if (aTypes[1] != Type::Count)  // Als secondary type gebruikt
        std::cout << "/" << static_cast<int>(aTypes[1]);
    std::cout << "\n";
}

void CreatureClass::PrintName() const
{
    std::cout << "Creature: " << GetName()
    << " (ID: " << iId
    << ", Catch: " << iCatchRate << ")";
    PrintTypes();
}

void CreatureClass::PrintMoves() const
{
    std::cout << "Moves van " << GetName() << ":\n";
    for (std::size_t i = 0; i < aMoves.size(); ++i)
    {
        const auto& m = aMoves[i];
        std::cout << " [" << i << "] " << m.name
                  << " (Type: " << static_cast<int>(m.type)
                  << ", Power: " << m.power
                  << ", Acc: " << m.accuracy << ")\n";
    }
}
// Creatureclass.cpp
CreatureClass::CreatureClass()
    : CharacterClass("Empty", 1, 0, 0, 0, 0, 10," "),
    iId(-1),
    iCatchRate(0),
    aTypes{Type::Earth, Type::Earth},
    aMoves{}
{
    // lege creature: geen sterke stats
    bGoodHP      = false;
    bGoodPDamage = false;
    bGoodMDamage = false;
    bGoodPArmor  = false;
    bGoodMArmor  = false;
    bGoodSpeed   = false;
}

CreatureClass::CreatureClass(const std::string& name,
                             int maxHp,
                             int pDamage,
                             int mDamage,
                             int pArmor,
                             int mArmor,
                             int speed,
                             int id,
                             int catchRate,
                             const std::array<Type, 2>& types,
                             const std::array<Move, 4>& moves,
                            QString creatureimage)
    : CharacterClass(name, maxHp, pDamage, mDamage, pArmor, mArmor, speed ,creatureimage),
    iId(id),
    iCatchRate(catchRate),
    aTypes(types),
    aMoves(moves)
{
    // Voorbeeld-profielen op basis van primary type:
    switch (aTypes[0]) {
    case Type::Earth:
        // tanky: veel HP en PArmor
        bGoodHP      = true;
        bGoodPArmor  = true;
        bGoodPDamage = true;
        bGoodMDamage = false;
        bGoodMArmor  = false;
        bGoodSpeed   = false;
        break;
    case Type::Water:
        // meer MArmor en MDamage, oké HP
        bGoodHP      = true;
        bGoodPDamage = false;
        bGoodMDamage = true;
        bGoodPArmor  = false;
        bGoodMArmor  = true;
        bGoodSpeed   = false;
        break;
    case Type::Fire:
        // glass cannon: damage + speed
        bGoodHP      = false;
        bGoodPDamage = true;
        bGoodMDamage = true;
        bGoodPArmor  = false;
        bGoodMArmor  = false;
        bGoodSpeed   = true;
        break;
    case Type::Ice:
        // veel MArmor, oké HP, minder speed
        bGoodHP      = true;
        bGoodPDamage = false;
        bGoodMDamage = true;
        bGoodPArmor  = false;
        bGoodMArmor  = true;
        bGoodSpeed   = false;
        break;
    case Type::Flying:
        // snelle, kwetsbare attacker
        bGoodHP      = false;
        bGoodPDamage = true;
        bGoodMDamage = true;
        bGoodPArmor  = false;
        bGoodMArmor  = false;
        bGoodSpeed   = true;
        break;
    default:
        // fallback: niets speciaals
        bGoodHP      = false;
        bGoodPDamage = false;
        bGoodMDamage = false;
        bGoodPArmor  = false;
        bGoodMArmor  = false;
        bGoodSpeed   = false;
        break;
    }
}
void CreatureClass::ApplyCreatureScalingOnLevelUp()
{
    LevelUp(); // alle logica zit in CharacterClass::LevelUp
}
