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
            getMove("Tackle"),
            getMove("Growl"),
            getMove("Vine Whip")
        };
        m_creatures.emplace_back("Terrakid", 50, 30, 1, 255, types, moves);
    }

    // ID 2: Water creature
    {
        std::array<Type, 2> types = {Type::Water, Type::Water};
        std::array<Move, 4> moves = {
            getMove("Water Pulse"),
            getMove("Water Gun"),
            getMove("Tackle"),
            getMove("Growl")
        };
        m_creatures.emplace_back("AquaPup", 55, 25, 2, 200, types, moves);
    }

    // ID 3: Fire creature
    {
        std::array<Type, 2> types = {Type::Fire, Type::Fire};
        std::array<Move, 4> moves = {
            getMove("Ember"),
            getMove("Fire Blast"),
            getMove("Tackle"),
            getMove("Growl")
        };
        m_creatures.emplace_back("FlameFox", 45, 40, 3, 190, types, moves);
    }

    // ID 4: Fire/Flying
    {
        std::array<Type, 2> types = {Type::Fire, Type::Flying};
        std::array<Move, 4> moves = {
            getMove("Fire Blast"),
            getMove("Gust"),
            getMove("Ember"),
            getMove("Air Slash")
        };
        m_creatures.emplace_back("PyroWing", 78, 84, 4, 45, types, moves);
    }

    // ID 5: Ice creature
    {
        std::array<Type, 2> types = {Type::Ice, Type::Water};
        std::array<Move, 4> moves = {
            getMove("Ice Beam"),
            getMove("Water Pulse"),
            getMove("Blizzard"),
            getMove("Aurora Beam")
        };
        m_creatures.emplace_back("FrostFish", 60, 35, 5, 120, types, moves);
    }

    // ID 6: Dark creature
    {
        std::array<Type, 2> types = {Type::Dark, Type::Dark};
        std::array<Move, 4> moves = {
            getMove("Shadow Claw"),
            getMove("Bite"),
            getMove("Crunch"),
            getMove("Dark Pulse")
        };
        m_creatures.emplace_back("NightCat", 65, 55, 6, 90, types, moves);
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
