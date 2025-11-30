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
