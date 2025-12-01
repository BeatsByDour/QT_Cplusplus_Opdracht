#include "gamemanager.h"

GameManager::GameManager() {

   // CharacterClass* pChar = new PlayerClass("Hero", 100, 20, 10);
    // Punt 5: Useful and correct polymorphism - pChar is een CharacterClass* maar verwijst naar een PlayerClass object.
   // pChar->PrintName();
    // Punt 5: De juiste PrintName() van PlayerClass wordt aangeroepen via de base pointer.
}

void GameManager::SetupGame()
{
   std::cout <<"Welcome to the game"<< std::endl;
}
void GameManager::AddCharacter(std::shared_ptr<CharacterClass> character)
{
    // Punt 6: GameManager COMPOSEERT het spel door characters in een container op te slaan.
    characters.push_back(character);
}
