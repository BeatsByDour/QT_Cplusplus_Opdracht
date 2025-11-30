#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H
#include "playerclass.h"
#include "Creatureclass.h"
#include <vector>
#include <memory>

class GameManager
{

private:
    // Punt 6: Useful and correct object composition - GameManager bevat een verzameling CharacterClass objecten die samen de spelwereld vormen.
    std::vector<std::shared_ptr<CharacterClass>> characters;
public:
    void AddCharacter(std::shared_ptr<CharacterClass> character);
    GameManager();
    void GetplayerChar(PlayerClass PLayer);
    void GetOppChars(CreatureClass Enemies);
    void createEnvironment();
    void SetupGame();
};

#endif // GAMEMANAGER_H
