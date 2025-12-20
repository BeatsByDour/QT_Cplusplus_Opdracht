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
    int m_stage{1};


public:
    GameManager();

    // toegang tot player voor UI / MainWindow
    PlayerClass&       GetPlayer()       { return m_player; }
    const PlayerClass& GetPlayer() const { return m_player; }

    int  GetStage() const { return m_stage; }   // getter
    void NextStage()      { m_stage++; }        // stage++
    int  CalculateDamage(const Move &move,
                        const CharacterClass &attacker,
                        CharacterClass &defender);
    struct ActionEntry {
        QString text;
    };

    struct ActionLog {
        ActionEntry actions[3]; // max 3 aanvallen in een ronde
    };

    bool ResolveAction(CreatureClass &enemy,
                       int playerMoveIndex,
                       int beastMoveIndex,
                       ActionLog &log);


    CreatureClass GenerateRandomEnemy();

private:
    // init helpers
    void InitializePlayer();
};

#endif // GAMEMANAGER_H
