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
    virtual int getCombatPower() const override;
    virtual int getDamage() const override;
    virtual int getLoot() const override;
};


#endif //HW4_POTIONSMERCHANT_H
