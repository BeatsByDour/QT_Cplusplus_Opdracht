#include "TotalMovesClass.h"
#include "iostream"

TotalMovesClass::TotalMovesClass()
{
    // Pseudocode in TotalMovesClass::InitializeMoves() o.i.d.
    m_moves.push_back({1001, "Rock Smash",   20, 100, 35, MoveCategory::Physical, Type::Earth});
    m_moves.push_back({1002, "Quake",        30, 90,  10, MoveCategory::Physical, Type::Earth});
    m_moves.push_back({1003, "Water Jet",    20, 100, 25, MoveCategory::Special,  Type::Water});
    m_moves.push_back({1004, "Aqua Blade",   40, 95,  15, MoveCategory::Physical, Type::Water});
    m_moves.push_back({1005, "Flame Burst",  20, 95,  15, MoveCategory::Special,  Type::Fire});
    m_moves.push_back({1006, "Fire Spin",    15, 85,  15, MoveCategory::Special,  Type::Fire});
    m_moves.push_back({1007, "Wing Slash",   25, 100, 20, MoveCategory::Physical, Type::Flying});
    m_moves.push_back({1008, "Frost Bite",   30, 100, 20, MoveCategory::Physical, Type::Ice});
    m_moves.push_back({1009, "Guard Up",      0, 100, 30, MoveCategory::Status,   Type::Normal});
    m_moves.push_back({1010, "Splash Heal",   0, 100, 20, MoveCategory::Status,   Type::Water});
    m_moves.push_back({1010, "Bite",         10, 100, 20, MoveCategory::Physical,   Type::Dark});

}

// const ref voor functie
std::optional<Move> TotalMovesClass::GetMoveById(int id) const
{
    for (const auto& m : m_moves)
    {
        if (m.id == id)
            return m;
    }
    return std::nullopt;
}
//const ref voor functie
std::optional<Move> TotalMovesClass::GetMoveByName(const std::string& name) const
{
    for (const auto& m : m_moves)
    {
        if (m.name == name)
            return m;
    }
    return std::nullopt;
}
