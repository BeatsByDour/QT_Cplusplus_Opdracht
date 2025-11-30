#include "mainwindow.h"
#include "totalmovesclass.h"
#include "creaturedatabase.h"

#include <QApplication>

int main()
{
    TotalMovesClass movesDB;
    CreatureDatabase creatureDB(movesDB);

    // Creature ophalen via ID
    if (auto optCreature = creatureDB.GetCreatureById(4))
    {
        CreatureClass& charizard = *optCreature;
        charizard.PrintName();
        charizard.PrintMoves();
        charizard.PrintTypes();
    }

    // Alle creatures tonen
    for (const auto& creature : creatureDB.GetAllCreatures())
    {
        creature.PrintName();
    }

    return 0;
}
