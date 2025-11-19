#pragma once
#ifndef CHARACTERCLASS_H
#define CHARACTERCLASS_H
#include <string>

class CharacterClass
{
protected:
    // variables
    std::string sName;
    int iMaxHP,iCurrentHP ;
    int iDamage;
    // armor slots
    // spell slots
public:

    // constructor
    CharacterClass(const std::string& sName, int iMaxHp,int iDamage );

    //getters
    std::string GetName() const;
    int GetMaxHP()const;
    int GetCurrentHP()const;

    //setters
    void SetName(const std::string& name);
    void SetMaxHP(int maxHP);
    void SetCurrentHP(int currentHP);

    //print funciton
    virtual void Print() const;


};

#endif // CHARACTERCLASS_H
