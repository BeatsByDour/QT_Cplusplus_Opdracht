#pragma once
#ifndef PLAYERCLASS_H
#define PLAYERCLASS_H

#include "CharacterClass.h"
#include "Move.h"
#include "CreatureClass.h"
#include <array>
#include <vector>
#include "equipment.h"

class PlayerClass : public CharacterClass
{
private:
    std::array<Move, 2> m_playerMoves;           // 2 moves van de speler zelf
    std::array<CreatureClass, 4> m_caughtBeasts; // party van 4
    int m_activeBeastIndex{0};                   // welke beast is actief?
    float playerHpScale;
    float playerDamageScale;
    float playerSpeedScale;
    float playerArmorScale;

    Equipment m_weapon;
    Equipment m_armor;

    // crafting materials
    struct CraftMaterial
    {
        int beastId;
        std::string name;
        int quantity;
    };
    std::vector<CraftMaterial> m_materials;


public:
    PlayerClass(const std::string& name,
                int maxHP,
                int damage,
                int speed,
                const std::array<Move, 2>& playerMoves,
                float hpScale = 1.2f,
                float dmgScale = 1.2f,
                float spdScale = 1.0f,
                float ArmScale = 1.2f);
    // Interface uit CharacterClass
    void PrintName() const override;


    void ApplyPlayerScalingOnLevelUp();

    // Party
    const std::array<CreatureClass, 4>& GetParty() const { return m_caughtBeasts; }
    CreatureClass& GetActiveBeast() { return m_caughtBeasts.at(m_activeBeastIndex); }
    void SwitchBeast(int index);

    // Player moves
    const Move& GetPlayerMove(int index) const { return m_playerMoves.at(index); }

    // Battle actions
    void AttackEnemy(CreatureClass& enemy, int moveIndex);
    bool TryRun() const;
    bool TryCatchBeast(CreatureClass& target);
    // Battle reward
    void RewardAfterBeastDefeat(CreatureClass& defeatedBeast, int xpForPlayer, int xpForBeast);
    // PlayerClass.h

    void SetMoves(const std::array<Move, 2>& moves) { m_playerMoves = moves; }
    void SetParty(const std::array<CreatureClass, 4>& party) { m_caughtBeasts = party; }
    bool AddToParty(const CreatureClass& beast);




private:
    double CalculateCatchChance(const CreatureClass& target) const;
    // Equipment
    void EquipWeapon(const Equipment& weapon);
    void EquipArmor(const Equipment& armor);

    // Crafting materials
    void AddMaterial(int beastId, const std::string& name, int amount);
    int GetMaterialCount(int beastId)const;

    //void SwitchBeast(int index);
    //const CreatureClass & GetActiveBeast();



};

#endif // PLAYERCLASS_H
