#include "CreatureDatabase.h"
#include <iostream>

CreatureDatabase::CreatureDatabase(TotalMovesClass& movesDB) : m_movesDB(movesDB)
{
    // Voorbeeld creatures vullen (ID 1-6)
    InitializeCreatures();
}

void CreatureDatabase::InitializeCreatures()
{
    auto getMove = [&](const std::string& name) -> Move {
        auto optMove = m_movesDB.GetMoveByName(name);
        return optMove.value_or(Move{}); // Fallback naar lege move
    };

    // 1: Earth (single)
    {
        std::array<Type, 2> types = {Type::Earth, Type::Earth};
        std::array<Move, 4> moves = {
            getMove("Rock Smash"),
            getMove("Quake"),
            getMove("Guard Up"),
            getMove("Bite")
        };
        m_creatures.emplace_back("Terrakid",
                                 50,   // maxHP
                                 30,   // damage
                                 20,   // speed
                                 1,    // id
                                 200,  // catchRate
                                 types,
                                 moves,
                                 1.0f, 1.0f, 1.0f, 1.0f);
    }

    // 2: Water (single)
    {
        std::array<Type, 2> types = {Type::Water, Type::Water};
        std::array<Move, 4> moves = {
            getMove("Water Jet"),
            getMove("Aqua Blade"),
            getMove("Splash Heal"),
            getMove("Guard Up")
        };
        m_creatures.emplace_back("AquaPup",
                                 55, 25, 18,
                                 2, 180,
                                 types, moves,
                                 1.1f, 0.9f, 1.0f, 1.0f);
    }

    // 3: Fire (single)
    {
        std::array<Type, 2> types = {Type::Fire, Type::Fire};
        std::array<Move, 4> moves = {
            getMove("Flame Burst"),
            getMove("Fire Spin"),
            getMove("Guard Up"),
            getMove("Splash Heal")
        };
        m_creatures.emplace_back("FlameFox",
                                 45, 40, 25,
                                 3, 190,
                                 types, moves,
                                 0.9f, 1.2f, 0.9f, 1.1f);
    }

    // 4: Fire/Flying (duo)
    {
        std::array<Type, 2> types = {Type::Fire, Type::Flying};
        std::array<Move, 4> moves = {
            getMove("Wing Slash"),
            getMove("Flame Burst"),
            getMove("Quake"),
            getMove("Guard Up")
        };
        m_creatures.emplace_back("PyroWing",
                                 60, 35, 30,
                                 4, 120,
                                 types, moves,
                                 1.0f, 1.0f, 1.0f, 1.2f);
    }

    // 5: Ice/Water (duo)
    {
        std::array<Type, 2> types = {Type::Ice, Type::Water};
        std::array<Move, 4> moves = {
            getMove("Frost Bite"),
            getMove("Water Jet"),
            getMove("Splash Heal"),
            getMove("Guard Up")
        };
        m_creatures.emplace_back("FrostFish",
                                 70, 28, 15,
                                 5, 160,
                                 types, moves,
                                 1.3f, 0.9f, 1.1f, 0.9f);
    }
}
std::optional<CreatureClass> CreatureDatabase::GetCreatureById(int id) const
{
    for (const auto& creature : m_creatures)
    {
        if (creature.GetId() == id)
            return creature;
    }
    return std::nullopt;
}

