#pragma once
#ifndef CREATUREDATABASE_H
#define CREATUREDATABASE_H

#include "CreatureClass.h"
#include "TotalMovesClass.h"

#include <vector>
#include <optional>
#include <array>

class CreatureDatabase
{
private:
    std::vector<CreatureClass> m_creatures;
    TotalMovesClass& m_movesDB; // Referentie naar moves database

public:
    CreatureDatabase(TotalMovesClass& movesDB);

    void InitializeCreatures();

    // Creature ophalen via ID
    std::optional<CreatureClass> GetCreatureById(int id) const;

    // Alle creatures ophalen
    const std::vector<CreatureClass>& GetAllCreatures() const { return m_creatures; }
};

#endif // CREATUREDATABASE_H
