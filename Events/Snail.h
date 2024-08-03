#ifndef HW4_SNAIL_H
#define HW4_SNAIL_H

#include "Encounter.h"

class Snail : public Encounter{
public:
    Snail();

private:
    static const int SNAIL_COMBAT_POWER = 5;
    static const int SNAIL_LOOT = 2;
    static const int SNAIL_DAMAGE = 10;
};


#endif //HW4_SNAIL_H
