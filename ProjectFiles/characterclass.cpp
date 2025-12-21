#include "characterclass.h"
#include <random>
#include <iomanip>

static int RandInt(int minInclusive, int maxInclusive)
{
    static std::mt19937 rng{std::random_device{}()};
    std::uniform_int_distribution<int> dist(minInclusive, maxInclusive);
    return dist(rng);
}

CharacterClass::CharacterClass(const std::string& name,
                               int maxHp,
                               int pDamage,
                               int mDamage,
                               int pArmor,
                               int mArmor,
                               int speed,
                               QString visualimage)
    : sName(name),
    iMaxHP(maxHp),
    iCurrentHP(maxHp),
    iPDamage(pDamage),
    iMDamage(mDamage),
    iPArmor(pArmor),
    iMArmor(mArmor),
    iLevel(1),
    iExperience(0),
    iSpeed(speed),
    VisualImage(visualimage)
{
}

// Uitgebreide ReceiveHit functie met friend class ondersteuning
void CharacterClass::RecieveHit(int dealtDamage, int /*currentHP*/)
{

    // Bereken gereduceerde damage gebaseerd op armor
    int effectiveDamage = dealtDamage;

    // Verminder damage gebaseerd op armor (voorbeeld)
    if (dealtDamage > 0) {
        // Als we weten of het physical of magical damage is, kunnen we de juiste armor gebruiken
        // Voor nu gebruiken we gemiddelde armor
        int avgArmor = (iPArmor + iMArmor) / 2;
        effectiveDamage = std::max(1, dealtDamage - avgArmor / 2);
    }

    iCurrentHP -= effectiveDamage;
    if (iCurrentHP < 0)
        iCurrentHP = 0;

    std::cout << sName << " received " << effectiveDamage << " damage (" << dealtDamage << " base)" << std::endl;

    // Intern damage log bijhouden voor debugging
    InternalDamageCalculation(effectiveDamage, "Unknown");
}

// Interne damage calculation helper
void CharacterClass::InternalDamageCalculation(int damage, const std::string& attackerName)
{
    if (damage > 0) {
        std::cout << "[DEBUG] " << attackerName << " dealt " << damage
                  << " to " << sName << ". Remaining HP: " << iCurrentHP
                  << "/" << iMaxHP << std::endl;
    }
}

void CharacterClass::AddExperience(int amount)
{
    iExperience += amount;
    // simpele curve: level up bij 100 * current level
    while (iExperience >= iLevel * 100)
    {
        iExperience -= iLevel * 100;
        LevelUp();
    }

    // optioneel: bereken hoeveel XP nog nodig is voor het volgende level
    int neededForNext = iLevel * 100 - iExperience;
    if (neededForNext < 0)
        neededForNext = 0;
}

void CharacterClass::LevelUp()
{
    ++iLevel;

    // HP: goed → 3–5, slecht/overig → 1–2
    if (bGoodHP)
        iMaxHP += RandInt(3, 5);
    else
        iMaxHP += RandInt(1, 2);

    // Physical Damage: goed → 1–3, slecht → 0–1
    if (bGoodPDamage)
        iPDamage += RandInt(1, 3);
    else
        iPDamage += RandInt(0, 1);

    // Magical Damage: goed → 1–3, slecht → 0–1
    if (bGoodMDamage)
        iMDamage += RandInt(1, 3);
    else
        iMDamage += RandInt(0, 1);

    // Physical Armor: goed → 1–3, slecht → 0–1
    if (bGoodPArmor)
        iPArmor += RandInt(1, 3);
    else
        iPArmor += RandInt(0, 1);

    // Magical Armor: goed → 1–3, slecht → 0–1
    if (bGoodMArmor)
        iMArmor += RandInt(1, 3);
    else
        iMArmor += RandInt(0, 1);

    // Speed: goed → 1–3, slecht → 0–1
    if (bGoodSpeed)
        iSpeed += RandInt(1, 3);
    else
        iSpeed += RandInt(0, 1);

    // HP bijvullen na level-up
    iCurrentHP = iMaxHP;
}

std::string CharacterClass::GetName() const {
    return sName;
}

int CharacterClass::GetMaxHP() const {
    return iMaxHP;
}

int CharacterClass::GetCurrentHP() const {
    return iCurrentHP;
}

void CharacterClass::SetName(const std::string& name) {
    sName = name;
}

void CharacterClass::SetMaxHP(int maxHP) {
    iMaxHP = maxHP;
}

void CharacterClass::SetCurrentHP(int currentHP) {
    iCurrentHP = currentHP;
}

void CharacterClass::PrintName() const {
    std::cout << "Character Name: " << sName << std::endl;
}

// Friend operator implementations
std::ostream& operator<<(std::ostream& os, const CharacterClass& character)
{
    // Serialize character data to stream
    os << character.sName << "\n";
    os << character.iMaxHP << " " << character.iCurrentHP << "\n";
    os << character.iPDamage << " " << character.iMDamage << "\n";
    os << character.iPArmor << " " << character.iMArmor << "\n";
    os << character.iSpeed << "\n";
    os << character.iLevel << " " << character.iExperience << "\n";
    os << static_cast<int>(character.m_status) << "\n";

    // Save stat scaling flags
    os << character.bGoodHP << " "
       << character.bGoodPDamage << " "
       << character.bGoodMDamage << " "
       << character.bGoodPArmor << " "
       << character.bGoodMArmor << " "
       << character.bGoodSpeed << "\n";

    // Image path (als QString, we slaan op als std::string)
    // os << character.VisualImage.isNull() << "\n"; // placeholder

    return os;
}

std::istream& operator>>(std::istream& is, CharacterClass& character)
{
    // Deserialize character data from stream
    std::getline(is, character.sName);
    is >> character.iMaxHP >> character.iCurrentHP;
    is >> character.iPDamage >> character.iMDamage;
    is >> character.iPArmor >> character.iMArmor;
    is >> character.iSpeed;
    is >> character.iLevel >> character.iExperience;

    int statusInt;
    is >> statusInt;
    character.m_status = static_cast<Status>(statusInt);

    // Load stat scaling flags
    is >> character.bGoodHP
        >> character.bGoodPDamage
        >> character.bGoodMDamage
        >> character.bGoodPArmor
        >> character.bGoodMArmor
        >> character.bGoodSpeed;

    // Skip newline
    is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    // Image loading zou hier komen
    // character.VisualImage = QPixmap(imagePath);

    return is;
}

bool CharacterClass::SaveToFile(const std::string& filename) const
{
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open file for writing: " << filename << std::endl;
        return false;
    }

    // Use friend operator<<
    file << *this;
    file.close();

    std::cout << "Character saved to: " << filename << std::endl;
    return true;
}

bool CharacterClass::LoadFromFile(const std::string& filename)
{
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open file for reading: " << filename << std::endl;
        return false;
    }

    // Use friend operator>>
    file >> *this;
    file.close();

    std::cout << "Character loaded from: " << filename << std::endl;
    return true;
}
