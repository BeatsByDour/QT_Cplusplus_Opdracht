#ifndef ENEMYCLASS_H
#define ENEMYCLASS_H
#include "characterclass.h"


class EnemyClass : public CharacterClass
{
public:
    EnemyClass(const std::string& name, int maxHP,int damage);
    // Override Print function
    void PrintName() const override;
};

#endif // ENEMYCLASS_H
