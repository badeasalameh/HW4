#ifndef HW4_POTIONSMERCHANT_H
#define HW4_POTIONSMERCHANT_H

#include "SpecialEvent.h"

class PotionsMerchant : public SpecialEvent{
public:
    PotionsMerchant();
    static int getPotionCost();
    static int getPotionEffect();

private:
    static const int COST = 5;
    static const int EFFECT = 10;
};


#endif //HW4_POTIONSMERCHANT_H
