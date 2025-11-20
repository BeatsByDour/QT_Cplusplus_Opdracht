#pragma once
#ifndef CHARACTERCLASS_H
#define CHARACTERCLASS_H
#include <string>
#include "iostream"

class CharacterClass
{

    // encapsulation
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

    // character function
    void RecieveHit(int dealtDamage, int currentHP);
    void Hit(int damageDealt,int enemyHP);
    void RecieveHealing(int HealthtoHeal,int currentHP);
    //print funciton
    virtual void PrintName() const = 0; // Abstracte functie
    void PrintStats();




};

#endif // CHARACTERCLASS_H
