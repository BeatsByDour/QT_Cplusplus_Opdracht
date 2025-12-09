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
    std::array<Type, 2> aTypes{};  // Dual typing
    std::array<Move, 4> aMoves{};

    // Extra scaling-multipliers
    float hpScale{1.0f};
    float damageScale{1.0f};
    float armorScale{1.0f};
    float speedScale{1.0f};

public:
    // ✅ DEFAULT CONSTRUCTOR TOEGEVOEGD (voor lege party slots)
    CreatureClass()
        : CharacterClass("Empty", 1, 0, 10),
        iId(-1),
        iCatchRate(0),
        aTypes{Type::Earth, Type::Earth},
        aMoves{},
        hpScale(1.0f),
        damageScale(1.0f),
        armorScale(1.0f),
        speedScale(1.0f)
    {}

    // ✅ GEFIXTE CONSTRUCTOR (scaling parameters toegevoegd)
    CreatureClass(const std::string& name,
                  int maxHp,
                  int damage,
                  int speed,
                  int id,
                  int catchRate,
                  const std::array<Type, 2>& types,
                  const std::array<Move, 4>& moves,
                  float hpScale = 1.0f,
                  float damageScale = 1.0f,
                  float armorScale = 1.0f,
                  float speedScale = 1.0f)
        : CharacterClass(name, maxHp, damage, speed),
        iId(id),
        iCatchRate(catchRate),
        aTypes(types),
        aMoves(moves),
        hpScale(hpScale),
        damageScale(damageScale),
        armorScale(armorScale),
        speedScale(speedScale)
    {
    }

    // ✅ HELPER VOOR LEGE SLOTS
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
    int GetPhysicalDamage() const { return iPDamage; }  // const toegevoegd
    int GetMagicalDamage() const { return iMDamage; }   // const toegevoegd
    const Move& GetMove(int index) const { return aMoves.at(index); }

    void PrintTypes() const;
    void PrintMoves() const;
    void PrintName() const override;
    bool TryCatch(int throwStrength) const;
};

#endif // CREATURECLASS_H
