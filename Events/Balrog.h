#ifndef HW4_BALROG_H
#define HW4_BALROG_H

#include "Encounter.h"

class Balrog : public Encounter{
public:
    Balrog();
    void balrogCombatPowerIncrease();

private:
    static const int BALROG_COMBAT_POWER = 15;
    static const int BALROG_LOOT = 100;
    static const int BALROG_DAMAGE = 9001;

    static const int BALROG_COMBAT_POWER_INCREASE = 2;
};


#endif //HW4_BALROG_H
