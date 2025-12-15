#include "GameManager.h"
#include <iostream>
#include <cstdlib>
#include <thread>
#include <chrono>

GameManager::GameManager()
    : m_movesDB(),
    m_creatureDB(m_movesDB),
    m_player(
        "player",
        50,
        15,
        15,
        std::array<Move, 2>{},
        1.2f,
        1.2f,
        1.2f,
        1.5f)
{
    // speler naar level 5 brengen
    for (int i = 1; i < 5; ++i) {
        m_player.LevelUp();
    }
    InitializePlayer();
}

void GameManager::InitializePlayer()
{
    // voorbeeld: startmoves voor de speler zelf
    std::array<Move, 2> startMoves{};
    startMoves[0] = Move{1001, "Punch", 30, 100, 999, MoveCategory::Physical, Type::Earth};
    startMoves[1] = Move{1002, "Kick", 25, 100, 999, MoveCategory::Physical, Type::Air};
    m_player.SetMoves(startMoves);
}

CreatureClass GameManager::GenerateRandomEnemy()
{
    int maxId = static_cast<int>(m_creatureDB.GetAllCreatures().size());
    int randomId = 1 + (std::rand() % maxId);

    auto optEnemy = m_creatureDB.GetCreatureById(randomId);
    CreatureClass enemy = optEnemy ? *optEnemy
                                   : m_creatureDB.GetAllCreatures().front();

    // random level dat verhoogd met de stage
    int targetLevel = GetStage()+  1 + (std::rand() % 3);
    while (enemy.GetLevel() < targetLevel) {
        enemy.LevelUp();     // gebruikt CharacterClass::LevelUp()
    }
    return enemy;
}


int GameManager::CalculateDamage(const Move &move,
                                 const CharacterClass &attacker,
                                 CharacterClass &defender)
{
    // kies attack/armor type
    double atk  = (move.category == MoveCategory::Physical)
                     ? attacker.GetPDamage()
                     : attacker.GetMDamage();
    double armor = (move.category == MoveCategory::Physical)
                       ? defender.GetPArmor()
                       : defender.GetMArmor();

    if (armor < 1.0) armor = 1.0; // deling door 0 voorkomen

    double raw = static_cast<double>(move.power) * atk / armor;
    int dmg = static_cast<int>(std::max(1.0, raw)); // min. 1 dmg

    defender.RecieveHit(dmg, defender.GetCurrentHP());
    return dmg;
}

bool GameManager::ResolveTurn(CreatureClass &enemy,
                              int playerMoveIndex,
                              bool /*useBeastMove*/)
{
    PlayerClass &player = m_player;
    CreatureClass &playerBeast = player.GetActiveBeast();

    // wie is sneller?
    CharacterClass *first  = &player;
    CharacterClass *second = &enemy;
    bool playerFirst = player.GetSpeed() >= enemy.GetSpeed();

    if (!playerFirst) {
        first  = &enemy;
        second = &player;
    }


    auto getPlayerMove = [&](int idx) -> Move {
        return player.GetPlayerMove(idx);
    };

    // 1) eerste aanval
    if (first == &player) {
        Move m = getPlayerMove(playerMoveIndex);
        int dmg = CalculateDamage(m, player, enemy);
        // hier kun je tekst doorgeven aan UI via return-waarden of aparte struct
    } else {
        // enemy valt eerst aan – kies simpelweg fysieke attack‑move
        Move m{0, "Enemy Attack", 10, 100, 999,
               MoveCategory::Physical, enemy.GetPrimaryType()};
        int dmg = CalculateDamage(m, enemy, player);
    }

    // check of iemand dood is
    if (enemy.GetCurrentHP() <= 0 || player.GetCurrentHP() <= 0)
        return true; // battle klaar

    // 2) tweede aanval
    if (second == &player) {
        Move m = getPlayerMove(playerMoveIndex);
        int dmg = CalculateDamage(m, player, enemy);
    } else {
        Move m{0, "Enemy Attack", 10, 100, 999,
               MoveCategory::Physical, enemy.GetPrimaryType()};
        int dmg = CalculateDamage(m, enemy, player);
    }

    // resultaat
    return enemy.GetCurrentHP() <= 0 || player.GetCurrentHP() <= 0;
}

