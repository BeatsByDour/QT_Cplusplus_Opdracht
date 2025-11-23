#include "playerclass.h"


PlayerClass::PlayerClass(const std::string& name, int maxHP, int damage) : CharacterClass(name,maxHP,damage) {}

class PlayerClass : public CharacterClass // Punt 4: Useful and correct inheritance - PlayerClass hergebruikt alle basisfunctionaliteit van CharacterClass.

}

