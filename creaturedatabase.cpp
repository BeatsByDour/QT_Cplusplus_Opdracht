#include "CreatureDatabase.h"
#include <iostream>

CreatureDatabase::CreatureDatabase(TotalMovesClass& movesDB) : m_movesDB(movesDB)
{
    // Voorbeeld creatures vullen (ID 1-6)
    InitializeCreatures();
}

void CreatureDatabase::InitializeCreatures()
{
    // Voorbeeld moves ophalen uit database
    auto getMove = [&](const std::string& name) -> Move {
        auto optMove = m_movesDB.GetMoveByName(name);
        return optMove.value_or(Move{});  // Fallback naar lege move
    };

    // ID 1: Earth creature
    {
        std::array<Type, 2> types = {Type::Earth, Type::Earth};
        std::array<Move, 4> moves = {
            getMove("Earthquake"),
            getMove("Earthquake"),
            getMove("Earthquake"),
            getMove("Earthquake")
        };
        m_creatures.emplace_back("Terrakid", 50, 30, 1, 255,10, types, moves,1.0f,1.0f,1.0f);
    }

    // ID 2: Water creature
    {
        std::array<Type, 2> types = {Type::Water, Type::Water};
        std::array<Move, 4> moves = {
            getMove("Earthquake"),
            getMove("Earthquake"),
            getMove("Earthquake"),
            getMove("Earthquake")
        };
        m_creatures.emplace_back("AquaPup", 55, 25, 2, 200,10, types, moves,1.0f,1.0f,1.0f);
    }

    // ID 3: Fire creature
    {
        std::array<Type, 2> types = {Type::Fire, Type::Fire};
        std::array<Move, 4> moves = {
            getMove("Earthquake"),
            getMove("Earthquake"),
            getMove("Earthquake"),
            getMove("Earthquake")
        };
        m_creatures.emplace_back("FlameFox", 45, 40, 3, 190,10, types, moves,1.0f,1.0f,1.0f);
    }

    // ID 4: Fire/Flying
    {
        std::array<Type, 2> types = {Type::Fire, Type::Flying};
        std::array<Move, 4> moves = {
            getMove("Earthquake"),
            getMove("Earthquake"),
            getMove("Earthquake"),
            getMove("Earthquake")
        };
        m_creatures.emplace_back("PyroWing", 78, 84, 4, 45,10, types, moves,1.0f,1.0f,1.0f);
    }

    // ID 5: Ice creature
    {
        std::array<Type, 2> types = {Type::Ice, Type::Water};
        std::array<Move, 4> moves = {
            getMove("Earthquake"),
            getMove("Earthquake"),
            getMove("Earthquake"),
            getMove("Earthquake")
        };
        m_creatures.emplace_back("FrostFish", 60, 35, 5, 120,10, types, moves,1.0f,1.0f,1.0f);
    }

    // ID 6: Dark creature
    {
        std::array<Type, 2> types = {Type::Dark, Type::Dark};
        std::array<Move, 4> moves = {
            getMove("Earthquake"),
            getMove("Earthquake"),
            getMove("Earthquake"),
            getMove("Earthquake")
        };
        m_creatures.emplace_back("NightCat", 65, 55, 6, 90,10, types, moves,1.0f,1.0f,1.0f);
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
