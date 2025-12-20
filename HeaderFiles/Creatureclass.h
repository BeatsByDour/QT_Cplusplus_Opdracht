// Creatureclass.h
#pragma once
#ifndef CREATURECLASS_H
#define CREATURECLASS_H

#include "CharacterClass.h"
#include "Move.h"
#include <array>

class CreatureClass : public CharacterClass
{
private:
    int iId{};
    int iCatchRate{};
    std::array<Type, 2> aTypes{};   // Dual typing
    std::array<Move, 4> aMoves{};

public:

    CreatureClass();
    CreatureClass(const std::string& name,
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
                  QString CreatureImage
                  );


    bool IsEmpty() const { return iId == -1; }

    void ApplyCreatureScalingOnLevelUp();

    // Type getters
    const std::array<Type, 2>& GetTypes() const { return aTypes; }
    Type GetPrimaryType() const { return aTypes[0]; }
    Type GetSecondaryType() const { return aTypes[1]; }
    bool HasType(Type t) const;

    // Rest getters
    int GetId() const { return iId; }
    int GetCatchRate() const { return iCatchRate; }
    int GetPhysicalDamage() const { return iPDamage; }
    int GetMagicalDamage() const { return iMDamage; }

    const Move& GetMove(int index) const { return aMoves.at(index); }
    int GetMoveCount() const { return static_cast<int>(aMoves.size()); }

    void PrintTypes() const;
    void PrintMoves() const;
    void PrintName() const override;
    bool TryCatch(int throwStrength) const;
};

#endif // CREATURECLASS_H
