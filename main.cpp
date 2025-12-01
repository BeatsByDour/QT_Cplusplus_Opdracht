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

    std::array<Move, 2> playerMoves = {
        Move{1001, "Punch", 30, 100, 999, MoveCategory::Physical, Type::Normal}, // eventueel eigen type
        Move{1002, "Throw Net", 0, 95,  50, MoveCategory::Status,   Type::Air}
    };

    std::array<CreatureClass, 4> party = {
        creatureDB.GetCreatureById(1).value(),
        creatureDB.GetCreatureById(2).value(),
        creatureDB.GetCreatureById(3).value(),
        creatureDB.GetCreatureById(4).value()
    };

    PlayerClass player("Hero", 100, 20,10, playerMoves, party);


    return 0;
}
