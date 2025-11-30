#include "TotalMovesClass.h"
#include "iostream"

TotalMovesClass::TotalMovesClass()
{
    m_moves.push_back({1, "Earthquake", 100, 100, 10, MoveCategory::Physical, Type::Earth});
    m_moves.push_back({2, "Water Pulse", 60,  100, 20, MoveCategory::Special,  Type::Water});
    m_moves.push_back({3, "Fire Blast",  110, 85,  5,  MoveCategory::Special,  Type::Fire});
    m_moves.push_back({4, "Gust",        40,  100, 35, MoveCategory::Special,  Type::Flying});
    // etc...
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
