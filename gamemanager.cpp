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
          std::array<Move, 2>{},
          1.2f,
          1.2f,
          1.2f,
          1.5f),
    m_isRunning(true)
{
    InitializePlayer();
}

void GameManager::Run()
{
    while (m_isRunning)
    {
      //  ShowMainMenu();
    }
}
void GameManager::InitializePlayer()
{
    std::array<Move, 2> startMoves{};
    startMoves[0] = Move{1001, "Punch", 30, 100, 999, MoveCategory::Physical, Type::Earth};
    startMoves[1] = Move{1002, "Kick",  25, 100, 999, MoveCategory::Physical, Type::Air};

    m_player.SetMoves(startMoves); // nu een geldige setter
    if (auto optC1 = m_creatureDB.GetCreatureById(1))
        m_player.AddToParty(optC1.value());
    else
        std::cout << "Starter beast 1 niet gevonden!\n";

    if (auto optC2 = m_creatureDB.GetCreatureById(2))
        m_player.AddToParty(optC2.value());
    else
        std::cout << "Starter beast 2 niet gevonden!\n";
}

void GameManager::ShowMainMenu()
{
    std::cout << "1. Wild encounter\n";
    std::cout << "2. Party bekijken\n";
    std::cout << "3. Stoppen\n";

    int choice{};
    std::cin >> choice;

    switch (choice)
    {
    case 1: StartWildEncounter(); break;
    case 2:
        // stats van player + beasts tonen
        m_player.PrintName();
        // etc.
        break;
    case 3:
        m_isRunning = false;
        break;
    default:
        std::cout << "Ongeldige keuze.\n";
        break;
    }
}
CreatureClass GameManager::GenerateRandomEnemy()
{
    // Heel simple: random ID tussen 1 en aantal creatures
    int maxId = static_cast<int>(m_creatureDB.GetAllCreatures().size());
    int randomId = 1 + (std::rand() % maxId);

    auto optEnemy = m_creatureDB.GetCreatureById(randomId);
    if (optEnemy)
        return *optEnemy;

    // fallback
    return m_creatureDB.GetAllCreatures().front();
}
void GameManager::StartWildEncounter()
{
    CreatureClass enemy = GenerateRandomEnemy();
    std::cout << "Een wilde " << enemy.GetName() << " verschijnt!\n";

    BattleLoop(enemy);
}

void GameManager::BattleLoop(CreatureClass enemy)
{
    bool battleOngoing = true;

    while (battleOngoing)
    {
        CreatureClass& playerBeast = m_player.GetActiveBeast();

        // Bepaal wie eerst gaat op basis van speed
        bool playerFirst = playerBeast.GetSpeed() >= enemy.GetSpeed();

        if (playerFirst)
        {
            PlayerTurn(enemy);
            if (enemy.GetCurrentHP() <= 0)
            {
                std::cout << "De vijand is verslagen!\n";
                m_player.RewardAfterBeastDefeat(enemy, 50, 50);
                battleOngoing = false;
                break;
            }

            EnemyTurn(enemy);
            if (playerBeast.GetCurrentHP() <= 0)
            {
                std::cout << "Je beast is ge-KO'd!\n";
                // TODO: andere beast kiezen of game over
                battleOngoing = false;
                break;
            }
        }
        else
        {
            EnemyTurn(enemy);
            if (playerBeast.GetCurrentHP() <= 0)
            {
                std::cout << "Je beast is ge-KO'd!\n";
                battleOngoing = false;
                break;
            }

            PlayerTurn(enemy);
            if (enemy.GetCurrentHP() <= 0)
            {
                std::cout << "De vijand is verslagen!\n";
                m_player.RewardAfterBeastDefeat(enemy, 50, 50);
                battleOngoing = false;
                break;
            }
        }
    }
}
void GameManager::PlayerTurn(CreatureClass& enemy)
{
    std::cout << "\nJouw beurt! Kies actie:\n";
    std::cout << "1. Attack\n";
    std::cout << "2. Catch\n";
    std::cout << "3. Run\n";
    std::cout << "4. Switch beast\n";

    int choice{};
    std::cin >> choice;

    switch (choice)
    {
    case 1:
    {
        int moveIndex{};
        std::cout << "Kies move (0 of 1): ";
        std::cin >> moveIndex;
        m_player.AttackEnemy(enemy, moveIndex);
        break;
    }
    case 2:
        if (m_player.TryCatchBeast(enemy))
        {
            // TODO: toevoegen aan party via een functie in PlayerClass
            std::cout << "Encounter eindigt, beast gevangen!\n";
        }
        break;
    case 3:
        if (m_player.TryRun())
        {
            std::cout << "Je bent succesvol gevlucht!\n";
        }
        else
        {
            std::cout << "Je kon niet ontsnappen!\n";
        }
        break;
    case 4:
    {
        int index{};
        std::cout << "Kies nieuwe beast index (0-3): ";
        std::cin >> index;
        m_player.SwitchBeast(index);
        break;
    }
    default:
        std::cout << "Ongeldige actie, beurt verloren.\n";
        break;
    }
}

void GameManager::EnemyTurn(CreatureClass& enemy)
{
    CreatureClass& playerBeast = m_player.GetActiveBeast();
    // Kies een simpele damage waarde, later vervangen door echte move-logic
    int damage = enemy.GetPhysicalDamage(); // maak zo'n getter
    std::cout << enemy.GetName() << " valt aan voor " << damage << " schade!\n";
    playerBeast.RecieveHit(damage, playerBeast.GetCurrentHP());
}
