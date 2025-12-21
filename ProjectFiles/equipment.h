#pragma once
#include <string>

struct Equipment
{
    std::string name;
    int bonusHP{0};
    int bonusPDamage{0};
    int bonusMDamage{0};
    int bonusPArmor{0};
    int bonusMArmor{0};
    int bonusSpeed{0};
};
