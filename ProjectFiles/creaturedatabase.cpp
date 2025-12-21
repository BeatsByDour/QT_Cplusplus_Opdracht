// creaturedatabase.cpp
#include "creaturedatabase.h"

CreatureDatabase::CreatureDatabase(TotalMovesClass& movesDB)
    : m_movesDB(movesDB)
{
    InitializeCreatures();
}
void CreatureDatabase::InitializeCreatures()
{
    auto getMove = [&](const std::string& name) -> Move {
        auto optMove = m_movesDB.GetMoveByName(name);
        return optMove.value_or(Move{}); // fallback
    };

    // 1: Terrakid – tanky Earth, veel HP en armor, lage speed
    {
        std::array<Type, 2> types = {Type::Earth, Type::Earth};
        std::array<Move, 4> moves = {
            getMove("Rock Smash"),
            getMove("Quake"),
            getMove("Guard Up"),
            getMove("Bite")
        };

        m_creatures.emplace_back(
            "Terrakid",
            65,  // HP
            28,  // P dmg
            8,   // M dmg
            6,   // P armor
            4,   // M armor
            12,  // speed
            1,   // id
            200, // catchRate
            types, moves,
            "C:\\Users\\BeatsByDour\\Documents\\CplusPlusTaak\\Afbeeldingen\\Terrakid.png"
            );
    }

    // 2: AquaPup – Water, iets meer HP, meer M dmg, matige armor
    {
        std::array<Type, 2> types = {Type::Water, Type::Water};
        std::array<Move, 4> moves = {
            getMove("Water Jet"),
            getMove("Aqua Blade"),
            getMove("Splash Heal"),
            getMove("Guard Up")
        };

        m_creatures.emplace_back(
            "AquaPup",
            60,  // HP
            22,  // P dmg
            16,  // M dmg
            3,   // P armor
            5,   // M armor
            16,  // speed
            2,   // id
            190, // catchRate
            types, moves,
             "C:\\Users\\BeatsByDour\\Documents\\CplusPlusTaak\\Afbeeldingen\\Aquapup.png"
            );
    }

    // 3: FlameFox – Fire, weinig HP, hoge P/M dmg, lage armor, hoge speed
    {
        std::array<Type, 2> types = {Type::Fire, Type::Fire};
        std::array<Move, 4> moves = {
            getMove("Flame Burst"),
            getMove("Fire Spin"),
            getMove("Guard Up"),
            getMove("Splash Heal")
        };

        m_creatures.emplace_back(
            "FlameFox",
            45,  // HP
            34,  // P dmg
            22,  // M dmg
            2,   // P armor
            2,   // M armor
            24,  // speed
            3,   // id
            180, // catchRate
            types, moves,
            "C:\\Users\\BeatsByDour\\Documents\\CplusPlusTaak\\Afbeeldingen\\Flamefox.png"
            );
    }

    // 4: PyroWing – Fire/Flying, gebalanceerd, hoge speed
    {
        std::array<Type, 2> types = {Type::Fire, Type::Flying};
        std::array<Move, 4> moves = {
            getMove("Wing Slash"),
            getMove("Flame Burst"),
            getMove("Quake"),
            getMove("Guard Up")
        };

        m_creatures.emplace_back(
            "PyroWing",
            55,  // HP
            30,  // P dmg
            20,  // M dmg
            4,   // P armor
            3,   // M armor
            26,  // speed
            4,   // id
            160, // catchRate
            types, moves,
             "C:\\Users\\BeatsByDour\\Documents\\CplusPlusTaak\\Afbeeldingen\\Pyrowing.png"
            );
    }

    // 5: FrostFish – Ice/Water, veel HP en M armor, trager
    {
        std::array<Type, 2> types = {Type::Ice, Type::Water};
        std::array<Move, 4> moves = {
            getMove("Frost Bite"),
            getMove("Water Jet"),
            getMove("Splash Heal"),
            getMove("Guard Up")
        };

        m_creatures.emplace_back(
            "FrostFish",
            70,  // HP
            24,  // P dmg
            14,  // M dmg
            3,   // P armor
            6,   // M armor
            14,  // speed
            5,   // id
            170, // catchRate
            types, moves,
             "C:\\Users\\BeatsByDour\\Documents\\CplusPlusTaak\\Afbeeldingen\\Frostfish.png"
            );
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

