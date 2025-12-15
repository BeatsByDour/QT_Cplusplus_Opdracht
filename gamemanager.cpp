#include "GameManager.h"
#include <iostream>
#include <cstdlib>

GameManager::GameManager()
    : m_movesDB(),
    m_creatureDB(m_movesDB),
    m_player(
        "player",
        50,
        15,
        15,
        std::array<Move, 2>{},  // of juiste grootte/type
        1.2f,
        1.2f,
        1.2f,
        1.5f)
{
    InitializePlayer();
}

void GameManager::InitializePlayer()
{
    // voorbeeld: startmoves voor de speler zelf
    std::array<Move, 2> startMoves{};
    startMoves[0] = Move{1001, "Punch", 30, 100, 999, MoveCategory::Physical, Type::Earth};
    startMoves[1] = Move{1002, "Kick", 25, 100, 999, MoveCategory::Physical, Type::Air};
    m_player.SetMoves(startMoves);

    // als je GEEN starter beasts wilt, haal deze blokken weg;
    // anders kun je ze laten staan (mits GetCreatureById juist werkt)
    /*
    if (auto optC1 = m_creatureDB.GetCreatureById(1))
        m_player.AddToParty(optC1.value());
    if (auto optC2 = m_creatureDB.GetCreatureById(2))
        m_player.AddToParty(optC2.value());
    */
}

CreatureClass GameManager::GenerateRandomEnemy()
{
    int maxId = static_cast<int>(m_creatureDB.GetAllCreatures().size());
    int randomId = 1 + (std::rand() % maxId);

    auto optEnemy = m_creatureDB.GetCreatureById(randomId);
    if (optEnemy)
        return *optEnemy;

    // fallback
    return m_creatureDB.GetAllCreatures().front();
}
