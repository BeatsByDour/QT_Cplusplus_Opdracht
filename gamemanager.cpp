#include "gamemanager.h"

GameManager::GameManager() {


    CharacterClass* pChar = new PlayerClass("Hero", 100, 20); // polymorfisme
    pChar->PrintName();  // virtaul finctie


}
void GameManager::SetupGame()
{
   std::cout <<"Welcome to the game"<< std::endl;
}
