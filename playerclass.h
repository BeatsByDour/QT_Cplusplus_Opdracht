#ifndef PLAYERCLASS_H
#define PLAYERCLASS_H
#include "characterclass.h"

class PlayerClass : public CharacterClass  // Punt 4: Useful and correct inheritance - PlayerClass hergebruikt alle basisfunctionaliteit van CharacterClass.

{
public:
    PlayerClass(const std::string& name, int maxHP,int damage);
    // Override Print function
    void PrintName() const override;
};

#endif // PLAYERCLASS_H
