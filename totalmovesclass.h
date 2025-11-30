#pragma once
#ifndef TOTALMOVESCLASS_H
#define TOTALMOVESCLASS_H

#include "Move.h"
#include <vector>
#include <optional>

class TotalMovesClass
{
private:
    std::vector<Move> m_moves;

public:
    TotalMovesClass();

    // Move opzoeken via id
    std::optional<Move> GetMoveById(int id) const;

    // Eventueel: move opzoeken via naam
    std::optional<Move> GetMoveByName(const std::string& name) const;

    const std::vector<Move>& GetAllMoves() const { return m_moves; }
};

#endif // TOTALMOVESCLASS_H
