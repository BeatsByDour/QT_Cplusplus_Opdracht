#ifndef ENEMYCLASS_H
#define ENEMYCLASS_H
#include "characterclass.h"


class EnemyClass : public CharacterClass  // Punt 4: Useful and correct inheritance - PlayerClass hergebruikt alle basisfunctionaliteit van CharacterClass.

{
public:
    EnemyClass(const std::string& name, int maxHP,int damage);
    // Override Print function
    void PrintName() const override;
};

#endif // ENEMYCLASS_H
