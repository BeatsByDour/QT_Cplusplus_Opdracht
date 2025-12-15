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

public:
    GameManager();

    // toegang tot player voor UI / MainWindow
    PlayerClass&       GetPlayer()       { return m_player; }
    const PlayerClass& GetPlayer() const { return m_player; }

    // eventueel helper om een willekeurige vijand te genereren,
    // als je dit later vanuit BattleScreen wilt gebruiken
    CreatureClass GenerateRandomEnemy();

private:
    // init helpers
    void InitializePlayer();
};

#endif // GAMEMANAGER_H
