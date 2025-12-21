#pragma once
#ifndef CHARACTERDEBUGGER_H
#define CHARACTERDEBUGGER_H

#include "characterclass.h"
#include <iostream>
#include <string>
#include <vector>

// Friend class voor CharacterClass
// Punt: Useful friend class - heeft directe toegang tot private members
class CharacterDebugger
{
public:
    // Print gedetailleerde stats (friend functie)
    static void PrintDetailedStats(const CharacterClass& character)
    {
        std::cout << "=== Character Debug Info ===" << std::endl;
        std::cout << "Name: " << character.sName << std::endl;
        std::cout << "Level: " << character.iLevel << " (XP: " << character.iExperience << ")" << std::endl;
        std::cout << "HP: " << character.iCurrentHP << "/" << character.iMaxHP
                  << " (" << (character.iCurrentHP * 100.0 / character.iMaxHP) << "%)" << std::endl;
        std::cout << "Damage - Physical: " << character.iPDamage
                  << " | Magical: " << character.iMDamage << std::endl;
        std::cout << "Armor - Physical: " << character.iPArmor
                  << " | Magical: " << character.iMArmor << std::endl;
        std::cout << "Speed: " << character.iSpeed << std::endl;
        std::cout << "Status: " << static_cast<int>(character.m_status) << std::endl;
        std::cout << "Stat Scaling Flags:" << std::endl;
        std::cout << "  Good HP: " << character.bGoodHP << std::endl;
        std::cout << "  Good P Damage: " << character.bGoodPDamage << std::endl;
        std::cout << "  Good M Damage: " << character.bGoodMDamage << std::endl;
        std::cout << "  Good P Armor: " << character.bGoodPArmor << std::endl;
        std::cout << "  Good M Armor: " << character.bGoodMArmor << std::endl;
        std::cout << "  Good Speed: " << character.bGoodSpeed << std::endl;
        std::cout << "==========================" << std::endl;
    }

    // Compare two characters (friend functie)
    static void CompareCharacters(const CharacterClass& a, const CharacterClass& b)
    {
        std::cout << "=== Character Comparison ===" << std::endl;
        std::cout << a.sName << " vs " << b.sName << std::endl;
        std::cout << "Level: " << a.iLevel << " vs " << b.iLevel << std::endl;
        std::cout << "HP: " << a.iCurrentHP << "/" << a.iMaxHP
                  << " vs " << b.iCurrentHP << "/" << b.iMaxHP << std::endl;
        std::cout << "Physical Damage: " << a.iPDamage << " vs " << b.iPDamage << std::endl;
        std::cout << "Magical Damage: " << a.iMDamage << " vs " << b.iMDamage << std::endl;
        std::cout << "Speed: " << a.iSpeed << " vs " << b.iSpeed << std::endl;

        // Wie zou winnen? (simpele voorspelling)
        double aScore = (a.iCurrentHP + a.iPDamage + a.iMDamage + a.iSpeed) / 4.0;
        double bScore = (b.iCurrentHP + b.iPDamage + b.iMDamage + b.iSpeed) / 4.0;

        std::cout << "Power Score: " << a.sName << ": " << aScore
                  << " | " << b.sName << ": " << bScore << std::endl;

        if (aScore > bScore) {
            std::cout << "Predicted Winner: " << a.sName << std::endl;
        } else if (bScore > aScore) {
            std::cout << "Predicted Winner: " << b.sName << std::endl;
        } else {
            std::cout << "Predicted: Tie" << std::endl;
        }
        std::cout << "==========================" << std::endl;
    }

    // Calculate damage between characters (friend functie)
    static int CalculateDamage(const CharacterClass& attacker, const CharacterClass& defender,
                               bool isPhysical = true)
    {
        int attackStat = isPhysical ? attacker.iPDamage : attacker.iMDamage;
        int defenseStat = isPhysical ? defender.iPArmor : defender.iMArmor;

        // Eenvoudige damage formule
        int baseDamage = attackStat * 2;
        int reducedDamage = std::max(1, baseDamage - defenseStat);

        std::cout << "[DEBUG] Damage Calculation:" << std::endl;
        std::cout << "  Attacker: " << attacker.sName
                  << " (" << (isPhysical ? "Physical" : "Magical")
                  << " Attack: " << attackStat << ")" << std::endl;
        std::cout << "  Defender: " << defender.sName
                  << " (" << (isPhysical ? "Physical" : "Magical")
                  << " Armor: " << defenseStat << ")" << std::endl;
        std::cout << "  Base Damage: " << baseDamage << std::endl;
        std::cout << "  Reduced Damage: " << reducedDamage << std::endl;

        return reducedDamage;
    }

    // Analyze character's strengths/weaknesses (friend functie)
    static void AnalyzeCharacter(const CharacterClass& character)
    {
        std::cout << "=== Character Analysis: " << character.sName << " ===" << std::endl;

        // Bepaal rol gebaseerd op stats
        std::string role = "Balanced";
        if (character.bGoodHP && character.bGoodPArmor && character.bGoodMArmor) {
            role = "Tank";
        } else if (character.bGoodPDamage && character.bGoodMDamage && character.bGoodSpeed) {
            role = "Damage Dealer";
        } else if (character.bGoodSpeed && !character.bGoodHP) {
            role = "Glass Cannon";
        } else if (character.bGoodHP && !character.bGoodSpeed) {
            role = "Bruiser";
        }

        std::cout << "Role: " << role << std::endl;

        // Stat ratings
        std::cout << "Stat Ratings (out of 10):" << std::endl;
        std::cout << "  HP: " << std::min(10, character.iMaxHP / 10) << "/10" << std::endl;
        std::cout << "  Physical Damage: " << std::min(10, character.iPDamage / 5) << "/10" << std::endl;
        std::cout << "  Magical Damage: " << std::min(10, character.iMDamage / 5) << "/10" << std::endl;
        std::cout << "  Speed: " << std::min(10, character.iSpeed / 3) << "/10" << std::endl;

        // Recommendations
        std::cout << "Recommendations:" << std::endl;
        if (character.bGoodHP) {
            std::cout << "  - Good HP scaling, focus on survivability" << std::endl;
        }
        if (character.bGoodPDamage || character.bGoodMDamage) {
            std::cout << "  - Good damage scaling, focus on offensive items" << std::endl;
        }
        if (character.bGoodSpeed) {
            std::cout << "  - High speed, can attack first in battles" << std::endl;
        }

        std::cout << "==========================" << std::endl;
    }
};

#endif // CHARACTERDEBUGGER_H
