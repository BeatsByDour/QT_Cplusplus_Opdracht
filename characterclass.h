#pragma once
#ifndef CHARACTERCLASS_H
#define CHARACTERCLASS_H
#include <string>
#include "iostream"
#include "move.h"

    // Punt 2: Useful and correct abstraction - CharacterClass beschrijft wat elk karakter KAN (HP, damage, acties) zonder te weten of het een speler of vijand is.
    // Punt 7: Useful and correct base class - CharacterClass is de gemeenschappelijke basis voor alle soorten karakters.
class CharacterClass
{
    // Punt 1: Useful and correct class - deze klasse bundelt alle gemeenschappelijke data en functies voor elk karakter in het spel

protected:
    // Punt 3: Useful and correct encapsulation - interne variabelen zijn afgeschermd en alleen via functies aan te passen/uit te lezen.
    std::string sName;
    int iMaxHP, iCurrentHP;
    int iPDamage, iMDamage;
    int iPArmor, iMArmor;
    int iLevel, iExperience;

    int iSpeed;              // bepaalt beurtvolgorde

    // Scaling per level (basis-groei)
    int hpPerLevel;
    int pDamagePerLevel;
    int mDamagePerLevel;
    int PArmorPerLevel;
    int iMArmorPerLevel;
    int speedPerLevel;
    Status m_status{Status::None};
    float hpScalePerLevel{1.0f};
    float pDamageScalePerLevel{1.0f};
    float mDamageScalePerLevel{1.0f};
    float pArmorScalePerLevel{1.0f};
    float mArmorScalePerLevel{1.0f};
    float speedScalePerLevel{1.0f};
public:

    // constructor
    CharacterClass(const std::string& sName,
                   int iMaxHp,
                   int iDamage,
                   int speed);

    Status GetStatus() const { return m_status; }
    void SetStatus(Status s) { m_status = s; }

    //getters
    std::string GetName() const;
    int GetMaxHP()const;
    int GetCurrentHP()const;
    int GetSpeed() const { return iSpeed; }
    int GetLevel() const { return iLevel; }
    int GetExperience() const { return iExperience; }
    int GetPDamage() const { return iPDamage; }
    int GetMDamage() const {return iMDamage;}
    int GetPArmor()  const { return iPArmor;  }
    int GetMArmor()  const { return iMArmor;  }


    // level / XP
    void AddExperience(int amount);
    void LevelUp();

    //setters
    void SetName(const std::string& name);
    void SetMaxHP(int maxHP);
    void SetCurrentHP(int currentHP);

    // character function
    void RecieveHit(int dealtDamage, int currentHP);
    void Hit(int damageDealt,int enemyHP);
    void RecieveHealing(int HealthtoHeal,int currentHP);
    //print funciton
    virtual void PrintName() const = 0;
    // Punt 8: Useful and correct abstract base class - pure virtual functie maakt CharacterClass abstract zodat alleen specifieke subklassen instanties zijn.

    void PrintStats();




};

#endif // CHARACTERCLASS_H
