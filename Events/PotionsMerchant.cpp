#include "PotionsMerchant.h"
PotionsMerchant :: PotionsMerchant() : SpecialEvent("PotionsMerchant")
{}

int PotionsMerchant :: getPotionCost()
{
    return COST;
}

int PotionsMerchant :: getPotionEffect()
{
    return EFFECT;
}

int PotionsMerchant::getCombatPower() const {
    return 0;
}
int PotionsMerchant::getDamage() const {
    return 0 ;
}
int PotionsMerchant::getLoot() const{
    return 0;
}