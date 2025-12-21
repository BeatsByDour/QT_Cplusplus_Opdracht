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
          50,   // maxHP
          15,   // pDamage (fysiek)
          10,   // mDamage (magisch)
          5,    // pArmor
          3,    // mArmor
          15,   // speed
          std::array<Move, 2>{}, // moves worden in InitializePlayer gezet
          "C:\\Users\\BeatsByDour\\Documents\\CplusPlusTaak\\Afbeeldingen\\player.png"
          )
{
    // speler naar level 5 brengen
    for (int i = 1; i < 5; ++i) {
        m_player.LevelUp();
         CharacterDebugger::PrintDetailedStats(m_player);
    }
    InitializePlayer();
}

void GameManager::InitializePlayer()
{
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
        enemy.LevelUp();
    }
    CharacterDebugger::PrintDetailedStats(enemy);
    return enemy;
}

void GameManager::resetGame()
{
    // Reset player naar beginwaarden
    m_player = PlayerClass(
        "player",
        50,   // maxHP
        15,   // pDamage
        10,   // mDamage
        5,    // pArmor
        3,    // mArmor
        15,   // speed
        std::array<Move, 2>{}, // moves worden in InitializePlayer gezet
        "C:\\Users\\BeatsByDour\\Documents\\CplusPlusTaak\\Afbeeldingen\\player.png"
        );

    // Speler naar level 5 brengen
    for (int i = 1; i < 5; ++i) {
        m_player.LevelUp();
    }

    // Initialize moves
    InitializePlayer();

    // Reset stage
    m_stage = 1;

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

    double raw = static_cast<double>(move.power) + atk / armor;
    int dmg = static_cast<int>(std::max(1.0, raw));

    defender.RecieveHit(dmg, defender.GetCurrentHP());
    return dmg;
}

static const Move& GetRandomEnemyMove(const CreatureClass& enemy)
{
    int count = enemy.GetMoveCount();
    int idx = std::rand() % count;
    return enemy.GetMove(idx);
}


bool GameManager::ResolveAction(CreatureClass &enemy,
                                int playerMoveIndex,
                                int beastMoveIndex,
                                ActionLog &log)
{
    try {
        if (playerMoveIndex < 0 || playerMoveIndex >= 2) {
            throw std::out_of_range("Invalid player move index");
        }

    PlayerClass &player      = m_player;
    CreatureClass &playerBeast = player.GetActiveBeast();
    bool hasBeast = !playerBeast.IsEmpty();

    // 1. lijst maken
    std::vector<CharacterClass*> actors;
    actors.push_back(&player);  // player in lijst plaatsen
    if (hasBeast) actors.push_back(&playerBeast); // mogelijke player beast in lijst plaatsen
    actors.push_back(&enemy);  // enemy in lijst plaatsen

    // 2. sorteren op speed, snelste eerst
    std::sort(actors.begin(), actors.end(),
              [](CharacterClass* a, CharacterClass* b) {
                  return a->GetSpeed() > b->GetSpeed();
              });

    // 3. max 3 aanvallen in volgorde
    int logIndex = 0;
    for (CharacterClass* a : actors) {
        if (logIndex == 3) break;

        if (a == &player) {
            Move m = player.GetPlayerMove(playerMoveIndex);
            int dmg = CalculateDamage(m, player, enemy);
            log.actions[logIndex++].text =
                QString("Player used %1 and dealt %2 damage.")
                    .arg(QString::fromStdString(m.name)).arg(dmg);
        } else if (hasBeast && a == &playerBeast) {
             Move m = playerBeast.GetMove(beastMoveIndex);
            int dmg = CalculateDamage(m, playerBeast, enemy);
            log.actions[logIndex++].text =
                QString("Beast used %1 and dealt %2 damage.")
                    .arg(QString::fromStdString(m.name)).arg(dmg);
        } else { // enemy
          const  Move &m = GetRandomEnemyMove(enemy);
            CharacterClass &target =
                (hasBeast && (std::rand() % 2 == 0)) ? static_cast<CharacterClass&>(playerBeast)
                                                     : static_cast<CharacterClass&>(player);

            int dmg = CalculateDamage(m, enemy, target);
            log.actions[logIndex++].text =
                QString("Enemy used %1 and dealt %2 damage.")
                    .arg(QString::fromStdString(m.name)).arg(dmg);
        }

        // na elke hit checken of battle klaar is
        if (enemy.GetCurrentHP() == 0 || player.GetCurrentHP() == 0 ||
            (hasBeast && playerBeast.GetCurrentHP() <= 0)) {
            break;
        }
    }

    return enemy.GetCurrentHP() <= 0 ||
           (player.GetCurrentHP() <= 0 && (!hasBeast || playerBeast.GetCurrentHP() <= 0));
    } catch (const std::exception& e) {
        std::cerr << "Battle error: " << e.what() << std::endl;
        return false;
    }


}

