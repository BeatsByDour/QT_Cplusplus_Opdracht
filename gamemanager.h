#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H
#include "playerclass.h"
#include "enemyclass.h"
#include <vector>
#include <memory>

class GameManager
{
    std::vector<std::shared_ptr<CharacterClass>> characters;
public:
    void AddCharacter(std::shared_ptr<CharacterClass> character);
    GameManager();
    void GetplayerChar(PlayerClass PLayer);
    void GetOppChars(EnemyClass Enemies);
    void createEnvironment();
    void SetupGame();
};

#endif // GAMEMANAGER_H
