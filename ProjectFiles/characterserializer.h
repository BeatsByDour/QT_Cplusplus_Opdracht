#pragma once
#ifndef CHARACTERSERIALIZER_H
#define CHARACTERSERIALIZER_H

#include "characterclass.h"
#include <fstream>
#include <vector>
#include <memory>

// Friend class voor advanced serialization
class CharacterSerializer
{
public:
    // Save multiple characters to a file
    static bool SaveParty(const std::vector<std::shared_ptr<CharacterClass>>& party,
                          const std::string& filename)
    {
        std::ofstream file(filename);
        if (!file.is_open()) {
            std::cerr << "Failed to open file: " << filename << std::endl;
            return false;
        }

        file << party.size() << "\n";
        for (const auto& character : party) {
            file << *character;
        }

        file.close();
        std::cout << "Party saved to: " << filename << std::endl;
        return true;
    }

    // Load multiple characters from a file
    static std::vector<std::shared_ptr<CharacterClass>> LoadParty(const std::string& filename)
    {
        std::vector<std::shared_ptr<CharacterClass>> party;
        std::ifstream file(filename);

        if (!file.is_open()) {
            std::cerr << "Failed to open file: " << filename << std::endl;
            return party;
        }

        size_t partySize;
        file >> partySize;
        file.ignore(); // Skip newline

        for (size_t i = 0; i < partySize; ++i) {
            auto character = std::make_shared<CharacterClass>();
            file >> *character;
            party.push_back(character);
        }

        file.close();
        std::cout << "Party loaded from: " << filename << " (" << party.size() << " characters)" << std::endl;
        return party;
    }

    // Export character to CSV format
    static bool ExportToCSV(const CharacterClass& character, const std::string& filename)
    {
        std::ofstream file(filename);
        if (!file.is_open()) {
            return false;
        }

        // CSV header
        file << "Name,Level,HP,CurrentHP,PDamage,MDamage,PArmor,MArmor,Speed,Experience,Status\n";

        // CSV data
        file << character.sName << ","
             << character.iLevel << ","
             << character.iMaxHP << ","
             << character.iCurrentHP << ","
             << character.iPDamage << ","
             << character.iMDamage << ","
             << character.iPArmor << ","
             << character.iMArmor << ","
             << character.iSpeed << ","
             << character.iExperience << ","
             << static_cast<int>(character.m_status) << "\n";

        file.close();
        return true;
    }

    // Create a character from a string representation
    static std::shared_ptr<CharacterClass> FromString(const std::string& data)
    {
        std::istringstream iss(data);
        auto character = std::make_shared<CharacterClass>();
        iss >> *character;
        return character;
    }

    // Convert character to string representation
    static std::string ToString(const CharacterClass& character)
    {
        std::ostringstream oss;
        oss << character;
        return oss.str();
    }
};

#endif // CHARACTERSERIALIZER_H
