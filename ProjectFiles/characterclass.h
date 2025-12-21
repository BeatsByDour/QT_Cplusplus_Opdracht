#pragma once
#ifndef CHARACTERCLASS_H
#define CHARACTERCLASS_H

#include <string>
#include <iostream>
#include "move.h"
#include "qstring"
#include "QPixmap"
#include <fstream>
#include <sstream>

// Forward declaration voor friend class
class CharacterDebugger;
// Punt 2: Useful and correct abstraction - CharacterClass beschrijft wat elk karakter KAN (HP, damage, acties) zonder te weten of het een speler of vijand is.
// Punt 7: Useful and correct base class - CharacterClass is de gemeenschappelijke basis voor alle soorten karakters.
class CharacterClass
{
    // Punt 1: Useful and correct class - deze klasse bundelt alle gemeenschappelijke data en functies voor elk karakter in het spel

protected:
    // CharacterClass.h - alle variabelen zijn nuttig gedefinieerd
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
    // in CharacterClass.h, protected:
    bool bGoodHP{false};
    bool bGoodPDamage{false};
    bool bGoodMDamage{false};
    bool bGoodPArmor{false};
    bool bGoodMArmor{false};
    bool bGoodSpeed{false};
    QPixmap VisualImage;

public:
    // Friend class declaraties - Punt: Useful friend class
    friend class CharacterDebugger;
    friend class CharacterSerializer;
    friend std::ostream& operator<<(std::ostream& os, const CharacterClass& character);
    friend std::istream& operator>>(std::istream& is, CharacterClass& character);

    //destructor
    virtual ~CharacterClass() = default;
    //copy constructor
    CharacterClass(const CharacterClass& other) = default;
    //Copy assignment operators
    CharacterClass& operator=(const CharacterClass& other) = default;

    // CharacterClass.h - parameterized constructor
    CharacterClass(const std::string& sName,
                   int maxHp,
                   int pDamage,
                   int mDamage,
                   int pArmor,
                   int mArmor,
                   int speed,
                   QString VisualImage);

    // Default constructor
    CharacterClass() : sName("Unknown"), iMaxHP(10), iCurrentHP(10),
        iPDamage(5), iMDamage(5), iPArmor(2), iMArmor(2),
        iLevel(1), iExperience(0), iSpeed(10), VisualImage() {}

    //Correct usage of inline function:
    Status GetStatus() const { return m_status; }
    void SetStatus(Status s) { m_status = s; }

    // CharacterClass.h -  getters en setters
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
    //const ref voor var
    const QPixmap &GetVisualImage() const { return VisualImage; }

    // level / XP
    //Useful member functions:
    void AddExperience(int amount);
    void LevelUp();

    //setters
    void SetName(const std::string& name);
    void SetMaxHP(int maxHP);
    void SetCurrentHP(int currentHP);

    // character function - nu uitgebreid met friend class functionaliteit
    void RecieveHit(int dealtDamage, int currentHP);
    void Hit(int damageDealt,int enemyHP);
    void RecieveHealing(int HealthtoHeal,int currentHP);

    //print funciton
    virtual void PrintName() const = 0;
    // Punt 8: Useful and correct abstract base class - pure virtual functie maakt CharacterClass abstract zodat alleen specifieke subklassen instanties zijn.

    void PrintStats();

    // Operator overloading voor serialisatie
    bool SaveToFile(const std::string& filename) const;
    bool LoadFromFile(const std::string& filename);

private:
    // Helper voor damage calculation met friend access
    void InternalDamageCalculation(int damage, const std::string& attackerName);
};

#endif // CHARACTERCLASS_H
