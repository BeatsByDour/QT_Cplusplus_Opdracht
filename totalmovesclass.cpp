#include "TotalMovesClass.h"
#include "iostream"

TotalMovesClass::TotalMovesClass()
{
    // Pseudocode in TotalMovesClass::InitializeMoves() o.i.d.
    m_moves.push_back({1001, "Rock Smash",   40, 100, 35, MoveCategory::Physical, Type::Earth});
    m_moves.push_back({1002, "Quake",        70, 90,  10, MoveCategory::Physical, Type::Earth});
    m_moves.push_back({1003, "Water Jet",    40, 100, 25, MoveCategory::Special,  Type::Water});
    m_moves.push_back({1004, "Aqua Blade",   60, 95,  15, MoveCategory::Physical, Type::Water});
    m_moves.push_back({1005, "Flame Burst",  60, 95,  15, MoveCategory::Special,  Type::Fire});
    m_moves.push_back({1006, "Fire Spin",    35, 85,  15, MoveCategory::Special,  Type::Fire});
    m_moves.push_back({1007, "Wing Slash",   55, 100, 20, MoveCategory::Physical, Type::Flying});
    m_moves.push_back({1008, "Frost Bite",   50, 100, 20, MoveCategory::Physical, Type::Ice});
    m_moves.push_back({1009, "Guard Up",      0, 100, 30, MoveCategory::Status,   Type::Normal});
    m_moves.push_back({1010, "Splash Heal",   0, 100, 20, MoveCategory::Status,   Type::Water});
    m_moves.push_back({1010, "Bite",         40, 100, 20, MoveCategory::Physical,   Type::Dark});

}


std::optional<Move> TotalMovesClass::GetMoveById(int id) const
{
    for (const auto& m : m_moves)
    {
        if (m.id == id)
            return m;
    }
    return std::nullopt;
}

std::optional<Move> TotalMovesClass::GetMoveByName(const std::string& name) const
{
    for (const auto& m : m_moves)
    {
        if (m.name == name)
            return m;
    }
    return std::nullopt;
}
