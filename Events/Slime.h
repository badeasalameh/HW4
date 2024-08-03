#ifndef HW4_SLIME_H
#define HW4_SLIME_H

#include "Encounter.h"

class Slime : public Encounter{
public:
    Slime();

private:
    static const int SLIME_COMBAT_POWER = 12;
    static const int SLIME_LOOT = 5;
    static const int SLIME_DAMAGE = 25;
};


#endif //HW4_SLIME_H
