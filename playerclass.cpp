#include "PlayerClass.h"
#include <iostream>
#include <algorithm> // std::clamp

PlayerClass::PlayerClass(const std::string& name,
                         int maxHP,
                         int damage,
                         int speed,
                         const std::array<Move, 2>& playerMoves,
                         float scalingHP,
                         float scalingdamage,
                         float scalingspeed,
                         float scalingarmor)
    : CharacterClass(name, maxHP, damage,speed),
    m_playerMoves(playerMoves),
    playerHpScale(scalingHP),
    playerDamageScale(scalingdamage),
    playerSpeedScale(scalingspeed),
    playerArmorScale(scalingarmor)
{

}


void PlayerClass::PrintName() const
{
    std::cout << "Player: " << GetName() << "\n";
}

void PlayerClass::SwitchBeast(int index)
{
    if (index < 0 || index >= static_cast<int>(m_caughtBeasts.size()))
    {
        std::cout << "Ongeldige beast index!\n";
        return;
    }
    m_activeBeastIndex = index;
    std::cout << "Actieve beast is nu: ";
    m_caughtBeasts[m_activeBeastIndex].PrintName();
}

void PlayerClass::AttackEnemy(CreatureClass& enemy, int moveIndex)
{
    if (moveIndex < 0 || moveIndex >= static_cast<int>(m_playerMoves.size()))
    {
        std::cout << "Ongeldige move index!\n";
        return;
    }

    const Move& m = m_playerMoves[moveIndex];
    int damage = m.power; // Later type-effectiveness enz. toevoegen

    std::cout << GetName() << " gebruikt " << m.name
              << " tegen " << enemy.GetName()
              << " voor " << damage << " schade!\n";

    enemy.RecieveHit(damage, enemy.GetCurrentHP());
}
bool PlayerClass::TryRun() const
{
    // Heel simpele logica: 75% kans om te vluchten
    int chance = 75;
    // TODO: vervang door random generator
    return chance >= 50; // placeholder
}
bool PlayerClass::TryCatchBeast(CreatureClass& target)
{
    double chance = CalculateCatchChance(target);
    std::cout << "Catch kans: " << chance * 100.0 << "%\n";

    // TODO: echte random tussen 0.0 en 1.0
    double fakeRoll = 0.3; // placeholder

    if (fakeRoll <= chance)
    {
        std::cout << "Je hebt " << target.GetName() << " gevangen!\n";
        // Hier zou je target toevoegen aan je party als er plaats is
        return true;
    }
    else
    {
        std::cout << target.GetName() << " is ontsnapt!\n";
        return false;
    }
}

double PlayerClass::CalculateCatchChance(const CreatureClass& target) const
{
    // Basis: catchrate 0–255 -> 0.05–0.95
    double base = std::clamp(target.GetCatchRate() / 255.0, 0.05, 0.95);

    // HP factor: hoe lager HP, hoe hoger factor (0–1)
    double hpFactor = 1.0 - (static_cast<double>(target.GetCurrentHP()) /
                             static_cast<double>(target.GetMaxHP()));
    hpFactor = std::clamp(hpFactor, 0.0, 1.0);

    // Status bonus
    double statusBonus = 1.0;
    switch (target.GetStatus())
    {
    case Status::Sleep:
    case Status::Freeze:
        statusBonus = 1.5;
        break;
    case Status::Paralyze:
    case Status::Burn:
    case Status::Poison:
        statusBonus = 1.25;
        break;
    default:
        statusBonus = 1.0;
        break;
    }

    double chance = base * (0.5 + hpFactor) * statusBonus;

    // Clamp naar 0–0.95
    chance = std::clamp(chance, 0.01, 0.95);
    return chance;
}
void PlayerClass::EquipWeapon(const Equipment& weapon)
{
    // eventueel oude weapon-bonussen verwijderen als je die apart bijhoudt
    m_weapon = weapon;
}

void PlayerClass::EquipArmor(const Equipment& armor)
{
    m_armor = armor;
}

void PlayerClass::AddMaterial(int beastId, const std::string& name, int amount)
{
    for (auto& mat : m_materials)
    {
        if (mat.beastId == beastId)
        {
            mat.quantity += amount;
            return;
        }
    }
    m_materials.push_back({beastId, name, amount});
}

int PlayerClass::GetMaterialCount(int beastId) const
{
    for (const auto& mat : m_materials)
    {
        if (mat.beastId == beastId)
            return mat.quantity;
    }
    return 0;
}
void PlayerClass::RewardAfterBeastDefeat(CreatureClass& defeatedBeast,
                                         int xpForPlayer,
                                         int xpForBeast)
{
    // XP voor speler
    AddExperience(xpForPlayer);

    // XP voor actieve beast
    GetActiveBeast().AddExperience(xpForBeast);

    // Crafting materiaal: naam gebaseerd op beast
    std::string matName = defeatedBeast.GetName() + " Scale";
    AddMaterial(defeatedBeast.GetId(), matName, 1);

    std::cout << "Je hebt " << defeatedBeast.GetName()
              << " verslagen en " << matName << " gekregen!\n";
}
/*
CreatureClass& PlayerClass::GetActiveBeast()
{
    // Zoek eerste niet-lege beast
    for (int i = 0; i < 4; ++i)
    {
        if (!m_caughtBeasts[i].IsEmpty())
        {
            m_activeBeastIndex = i;
            return m_caughtBeasts[i];
        }
    }
    return m_caughtBeasts[0]; // fallback naar eerste (leeg)
}

void PlayerClass::SwitchBeast(int index)
{
    if (index < 0 || index >= 4 || m_caughtBeasts[index].IsEmpty())
    {
        std::cout << "Ongeldige of lege beast index!\n";
        return;
    }
    m_activeBeastIndex = index;
    std::cout << "Actieve beast gewisseld naar: ";
    m_caughtBeasts[index].PrintName();
}
*/
bool PlayerClass::AddToParty(const CreatureClass& beast)
{
    for (int i = 0; i < 4; ++i)
    {
        if (m_caughtBeasts[i].IsEmpty())
        {
            m_caughtBeasts[i] = beast;
            std::cout << beast.GetName() << " toegevoegd aan party (slot " << i << ")!\n";
            return true;
        }
    }
    std::cout << "Party vol!\n";
    return false;
}
QString PlayerClass::GetStatsString() const
{
    return QString("HP: %1 | DMG: %2 | SPD: %3 | ARM: %4")
    .arg(iMaxHP)
        .arg(iMDamage)
        .arg(iSpeed)
        .arg(iPArmor);
}

