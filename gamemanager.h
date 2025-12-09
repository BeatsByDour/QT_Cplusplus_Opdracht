#pragma once
#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include "TotalMovesClass.h"
#include "CreatureDatabase.h"
#include "PlayerClass.h"

class GameManager
{
private:
    TotalMovesClass   m_movesDB;
    CreatureDatabase  m_creatureDB;
    PlayerClass       m_player;
    bool              m_isRunning;

public:
    GameManager();

    // hoofd-game-loop
    void Run();

private:
    // init helpers
    void InitializePlayer();
    void ShowMainMenu();
    void StartWildEncounter();
    void initializePlayer();
    CreatureClass GenerateRandomEnemy();


    // battle helpers
    void BattleLoop(CreatureClass enemy);
    void PlayerTurn(CreatureClass& enemy);
    void EnemyTurn(CreatureClass& enemy);
};

#endif // GAMEMANAGER_H
